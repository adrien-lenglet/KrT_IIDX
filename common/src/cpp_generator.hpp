#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include "util.hpp"
#include "util/sstream.hpp"

namespace CppGenerator {
	template <typename ...Args>
	decltype(auto) Bind(Args &&...args)
	{
		return std::make_tuple(std::forward<Args>(args)...);
	}

	template <typename ...Args>
	decltype(auto) S(Args &&...args)
	{
		return Bind(std::forward<Args>(args)...);
	}

	namespace Util
	{
		class File
		{
		public:
			File(const std::string &path) :
				m_stream(path, std::ios::binary | std::ios::trunc),
				m_indent(0)
			{
			}
			~File(void)
			{
			}

			File& new_line(void)
			{
				for (size_t i = 0; i < m_indent; i++)
					*this << "\t";
				return *this;
			}

			auto end_line(void)
			{
				return "\n";
			}

			void indent(void)
			{
				m_indent++;
			}

			void unindent(void)
			{
				if (m_indent == 0)
					throw std::runtime_error("Can't unindent void");
				m_indent--;
			}

			template <typename T>
			File& operator <<(T &&val)
			{
				static_cast<std::ostream&>(*this) << val;
				return *this;
			}

		private:
			std::ofstream m_stream;
			size_t m_indent;

			operator std::ostream&(void)
			{
				return m_stream;
			}
		};

		template <typename T>
		class RefHolder
		{
		public:
			virtual ~RefHolder(void) = default;

			virtual operator bool(void) const = 0;
			virtual T& get(void) = 0;

			class Unique : public RefHolder
			{
			public:
				template <typename W, class = std::enable_if_t<std::is_rvalue_reference_v<W&&>>>
				Unique(W &&other) :
					m_ref(new W(std::move(other)))
				{
				}

				operator bool(void) const override
				{
					return static_cast<bool>(m_ref);
				}

				T& get(void) override
				{
					return *m_ref;
				}

			private:
				std::unique_ptr<T> m_ref;
			};

			class Ref : public RefHolder
			{
			public:
				Ref(T &other) :
					m_ref(other)
				{
				}

				operator bool(void) const override
				{
					return true;
				}

				T& get(void) override
				{
					return m_ref;
				}

			private:
				T &m_ref;
			};
		};

		class Primitive
		{
		public:
			virtual ~Primitive(void) = default;

			virtual void write(Util::File &o) const = 0;

			class Named;
		};

		class Collection;

		template <typename OType>
		class GenWritable
		{
			using HolderType = RefHolder<GenWritable>;

			template <typename W>
			static inline constexpr bool is_w_ok_v = !std::is_same_v<std::remove_reference_t<W>, GenWritable>;

		public:
			GenWritable(void)
			{
			}

			GenWritable(GenWritable&&) = default;

			template <typename W, class = std::enable_if_t<is_w_ok_v<W> && std::is_rvalue_reference_v<W&&>>>
			GenWritable(W &&sub) :
				m_sub(new typename HolderType::Unique(std::move(sub)))
			{
			}
			template <typename W, class = std::enable_if_t<is_w_ok_v<W>>>
			GenWritable(W &sub) :
				m_sub(new typename HolderType::Ref(sub))
			{
			}

			virtual ~GenWritable(void)
			{
			}

			virtual void write(OType &o) const = 0;

		protected:
			void write_sub(OType &o) const
			{
				if (m_sub)
					m_sub->get().write(o);
			}

		private:
			std::unique_ptr<HolderType> m_sub;
		};

		using Writable = GenWritable<std::ostream>;
		using FileWritable = GenWritable<File>;

		class PrependKeyword;
		template <typename IdType>
		class VariableDecl;
		template <typename IdType>
		class VariableDeclWithValue;
	}

	std::ostream& operator<<(std::ostream &o, const Util::Writable &value)
	{
		value.write(o);
		return o;
	}

	class Namespace;

	class Util::Primitive::Named : public Util::Primitive
	{
	public:
		Named(const std::string &name) :
			m_name(name),
			m_parent(getStack().top()),
			m_base_name(m_parent ? m_parent->getBaseName() + std::string("::") + m_name : m_name)
		{
		}
		virtual ~Named(void)
		{
		}

		const std::string& getName(void) const
		{
			return m_name;
		}

		const std::string& getBaseName(void) const
		{
			return m_base_name;
		}

	private:
		const std::string m_name;
		Util::Primitive::Named *m_parent;
		const std::string m_base_name;

		friend Util::Collection;
		friend Namespace;
		static std::stack<Util::Primitive::Named*>& getStack(void)
		{
			static thread_local std::stack<Util::Primitive::Named*> res;

			return res;
		}
	};

	class Function;

	class Util::Collection : public Util::Primitive::Named
	{
	public:
		Collection(const std::string &name) :
			Util::Primitive::Named(name)
		{
		}
		~Collection(void) override
		{
		}

		template <typename PrimitiveType, typename ...Args>
		decltype(auto) add(Args &&...args)
		{
			auto &s = Util::Primitive::Named::getStack();
			s.emplace(this);
			decltype(auto) res = addActual<PrimitiveType>(std::forward<Args>(args)...);
			s.pop();
			return res;
		}

	protected:
		const util::unique_vector<Util::Primitive>& getPrimitives(void) const
		{
			return m_primitives;
		}

	private:
		util::unique_vector<Util::Primitive> m_primitives;

		template <typename PrimitiveType, typename ...Args>
		decltype(auto) addActual(Args &&...args)
		{
			if constexpr (std::is_base_of_v<Function, PrimitiveType>)
				return addFunction(std::forward<Args>(args)...);
			else
				return m_primitives.emplace<PrimitiveType>(std::forward<Args>(args)...);
		}

		template <typename T, typename ...Args>
		decltype(auto) addFunction(T &&type, const std::string &name, Args &&...args)
		{
			auto &func = m_primitives.emplace<Function>(std::forward<T>(type), name);

			auto res = std::tie(func);
			if constexpr (!util::are_args_empty_v<Args...>)
				return func.popArg(res, std::forward<Args>(args)...);
			else
				return func;
		}
	};

	class Out;

	class Namespace : public Util::Collection
	{
	public:
		Namespace(const std::string &name) :
			Util::Collection(name)
		{
			if (name == "")
				Util::Primitive::Named::getStack().pop();
		}
		~Namespace(void) override
		{
		}

		void write(Util::File &o) const override
		{
			auto isMain = getName() == "";

			if (!isMain) {
				o.new_line() << "namespace " << getName() << o.end_line();
				o.new_line() << "{" << o.end_line();
				o.indent();
			}
			auto is_first = true;
			for (auto &p : getPrimitives()) {
				if (!is_first)
					o << o.end_line();
				is_first = false;
				p.write(o);
			}
			if (!isMain) {
				o.unindent();
				o.new_line() << "}" << o.end_line();
			}
		}

	private:
		friend Out;

		class NullPlacer
		{
		public:
			NullPlacer(void)
			{
				auto &s = Util::Primitive::Named::getStack();
				s.emplace(nullptr);
			}
		};
	};

	class Out : Namespace::NullPlacer, public Namespace
	{
	public:
		Out(const std::string &path) :
			Namespace(""),
			m_path(path)
		{
		}

		~Out(void)
		{
			flush();
		}

		void flush(void)
		{
			if (m_flushed)
				return;

			Util::File f(m_path);

			Namespace::write(f);
			m_flushed = true;
		}

		const std::string& getPath(void) const
		{
			return m_path;
		}

	private:
		const std::string m_path;
		bool m_flushed = false;
	};

	class Value;

	class Type : public Util::Writable
	{
		class String;

		template <typename W>
		static inline constexpr bool is_w_ok_v = std::is_base_of_v<Type, std::remove_reference_t<W>> && !std::is_same_v<std::remove_reference_t<W>, Type>;

	public:
		Type(void)
		{
		}

		Type(Type &other) :
			Util::Writable(other)
		{
		}
		Type(Type&&) = default;

		template <typename W, class = std::enable_if_t<is_w_ok_v<W> && std::is_rvalue_reference_v<W&&>>>
		Type(W &&sub) :
			Util::Writable(std::move(sub))
		{
		}

		template <typename W, class = std::enable_if_t<is_w_ok_v<W>>>
		Type(W &sub) :
			Util::Writable(sub)
		{
		}

		Type(const std::string &str);
		Type(const Util::Primitive::Named &prim) :
			Type(prim.getBaseName())
		{
		}

		~Type(void) override
		{
		}

		void write(std::ostream &o) const override
		{
			write_sub(o);
		}

		struct Modifiers
		{
			class LRef;
			class RRef;
			class Ptr;
			class RConst;
			class Array;
		};

		Modifiers::LRef LRef(void);
		Modifiers::RRef RRef(void);
		template <typename ...Args>
		Modifiers::Ptr Ptr(Args &&...args);
		Modifiers::RConst RConst(void);
		template <typename ...Args>
		Modifiers::Array Array(Args &&...args);

		template <typename ...Args>
		Modifiers::Array operator[](Args &&...args);
		Modifiers::Ptr operator*(void);
		Modifiers::LRef operator&(void);

		auto operator-(const char *name);
		template <typename BindType>
		auto operator-(const BindType &bind);

		template <typename V, class = std::enable_if_t<!util::is_instance_of_template<V, std::tuple>{} && !std::is_same_v<std::decay_t<V>, const char*>>>
		Value operator-(V &&val);
		template <typename ...Values>
		Value operator()(Values &&...val);

	protected:
		String toString(void) const;
	};

	class Type::String : public Type
	{
	public:
		String(const std::string &str) :
			m_str(str)
		{
		}

		void write(std::ostream &o) const override
		{
			o << m_str;
		}
	
	private:
		std::string m_str;
	};

	inline Type::Type(const std::string &str) :
		Type(static_cast<String&&>(String(str)))
	{
	}

	inline Type::String Type::toString(void) const
	{
		return String(util::sstream_str(*this));
	}

	static Type Auto("auto");
	static Type Void("void");
	static Type Char("char");
	static Type Short("short");
	static Type Int("int");
	static Type Long_t("long");	// declare Long_t to not conflict with Long modifier
	static Type Float("float");
	static Type Double("double");
	static Type Bool("bool");
	static Type Nullptr_t("nullptr_t");
	static Type Size_t("size_t");
	static Type Int8_t("int8_t");
	static Type Int16_t("int16_t");
	static Type Int32_t("int32_t");
	static Type Int64_t("int64_t");
	static Type Uint8_t("uint8_t");
	static Type Uint16_t("uint16_t");
	static Type Uint32_t("uint32_t");
	static Type Uint64_t("uint64_t");

	class Util::PrependKeyword : public Type
	{
	public:
		template <typename T>
		PrependKeyword(const char *str, T &&type) :
			m_str(str),
			m_type(std::forward<T>(type))
		{
		}

		void write(std::ostream &o) const override
		{
			o << m_str << " ";
			m_type.write(o);
		}

	private:
		const char *m_str;
		Type m_type;
	};

	class Const : public Util::PrependKeyword
	{
	public:
		template <typename T>
		Const(T &&type) :
			Util::PrependKeyword("const", std::forward<T>(type)) {}
	};

	class Volatile : public Util::PrependKeyword
	{
	public:
		template <typename T>
		Volatile(T &&type) :
			Util::PrependKeyword("volatile", std::forward<T>(type)) {}
	};

	class Typename : public Util::PrependKeyword
	{
	public:
		template <typename T>
		Typename(T &&type) :
			Util::PrependKeyword("typename", std::forward<T>(type)) {}
	};

	class Long : public Util::PrependKeyword
	{
	public:
		template <typename T>
		Long(T &&type) :
			Util::PrependKeyword("long", std::forward<T>(type)) {}
	};

	class Signed : public Util::PrependKeyword
	{
	public:
		template <typename T>
		Signed(T &&type) :
			Util::PrependKeyword("signed", std::forward<T>(type)) {}
	};

	class Unsigned : public Util::PrependKeyword
	{
	public:
		template <typename T>
		Unsigned(T &&type) :
			Util::PrependKeyword("unsigned", std::forward<T>(type)) {}
	};

	class Type::Modifiers::LRef : public Type
	{
	public:
		template <typename T>
		LRef(T &&type) :
			Type(std::forward<T>(type))
		{
		}

		void write(std::ostream &o) const override
		{
			write_sub(o);
			o << "&";
		}
	};

	class Type::Modifiers::RRef : public Type
	{
	public:
		template <typename T>
		RRef(T &&type) :
			Type(std::forward<T>(type))
		{
		}

		void write(std::ostream &o) const override
		{
			write_sub(o);
			o << "&&";
		}
	};

	class Type::Modifiers::Ptr : public Type
	{
	public:
		template <typename T>
		Ptr(T &&type, size_t level = 1) :
			Type(std::forward<T>(type)),
			m_level(level)
		{
		}

		void write(std::ostream &o) const override
		{
			write_sub(o);
			for (size_t i = 0; i < m_level; i++)
				o << "*";
		}

	private:
		size_t m_level;
	};

	class Type::Modifiers::RConst : public Type
	{
	public:
		template <typename T>
		RConst(T &&type) :
			Type(std::forward<T>(type))
		{
		}

		void write(std::ostream &o) const override
		{
			write_sub(o);
			o << " const";
		}
	};

	inline Type::Modifiers::LRef Type::LRef(void)
	{
		return Modifiers::LRef(util::sstream_str(*this));
	}

	inline Type::Modifiers::RRef Type::RRef(void)
	{
		return Modifiers::RRef(util::sstream_str(*this));
	}

	template <typename ...Args>
	Type::Modifiers::Ptr Type::Ptr(Args &&...args)
	{
		return Modifiers::Ptr(util::sstream_str(*this), std::forward<Args>(args)...);
	}

	inline Type::Modifiers::RConst Type::RConst(void)
	{
		return Modifiers::RConst(util::sstream_str(*this));
	}

	namespace Op {
		class Inc;
		class Dec;
		class Plus;
		class Minus;
		class Not;
		class NotBin;
		class Deref;
		class Address;

		class Add;
		class Sub;
		class Mul;
		class Div;
		class Rem;
		class LShift;
		class RShift;
		class Less;
		class LessEq;
		class Greater;
		class GreaterEq;
		class Eq;
		class Dif;
		class AndBin;
		class XorBin;
		class OrBin;
		class And;
		class Or;
		class Assign;
		class AssignAdd;
		class AssignSub;
		class AssignMul;
		class AssignDiv;
		class AssignRem;
		class AssignLShift;
		class AssignRShift;
		class AssignAndBin;
		class AssignXorBin;
		class AssignOrBin;
	}

	class Value : public Util::Writable
	{
		template <typename W>
		static inline constexpr bool is_w_ok_v = std::is_base_of_v<Value, std::remove_reference_t<W>> && !std::is_same_v<std::remove_reference_t<W>, Value>;

	public:
		Value(void)
		{
		}

		Value(Value &other) :
			Util::Writable(other)
		{
		}
		Value(Value&&) = default;

		template <typename W, class = std::enable_if_t<is_w_ok_v<W> && std::is_rvalue_reference_v<W&&>>>
		Value(W &&sub) :
			Util::Writable(std::move(sub))
		{
		}

		template <typename W, class = std::enable_if_t<is_w_ok_v<W>>>
		Value(W &sub) :
			Util::Writable(sub)
		{
		}

		Value(const std::string &str);
		Value(const char str[]);
		Value(std::nullptr_t null);
		Value(bool b);
		Value(float f);
		Value(double f);
		Value(long double f);
		Value(unsigned char u);
		Value(unsigned short u);
		Value(unsigned int u);
		Value(unsigned long u);
		Value(unsigned long long u);
		Value(char i);
		Value(int i);
		Value(short s);
		Value(long i);
		Value(long long i);

		~Value(void) override
		{
		}

		void write(std::ostream &o) const override
		{
			write_sub(o);
		}

		struct Modifiers
		{
			class Inc;
			class Dec;
			class Call;
			class Array;
			class Member;
			class MemberPtr;
		};

		Modifiers::Inc Inc(void);
		Modifiers::Dec Dec(void);
		template <typename ...Args>
		Modifiers::Call Call(Args &&...args);
		template <typename ...Args>
		Modifiers::Array Array(Args &&...args);
		template <typename ...Args>
		Modifiers::Member Member(Args &&...args);
		template <typename ...Args>
		Modifiers::MemberPtr MemberPtr(Args &&...args);

		Modifiers::Inc operator ++(int);
		Modifiers::Dec operator --(int);
		template <typename ...Args>
		Modifiers::Call operator ()(Args &&...args);
		template <typename T>
		Modifiers::Array operator[](T &&val);

		CppGenerator::Op::Inc operator++(void);
		CppGenerator::Op::Dec operator--(void);
		CppGenerator::Op::Plus operator+(void);
		CppGenerator::Op::Minus operator-(void);
		CppGenerator::Op::Not operator!(void);
		CppGenerator::Op::NotBin operator~(void);
		CppGenerator::Op::Deref operator*(void);
		CppGenerator::Op::Address operator&(void);

		template <typename S>
		CppGenerator::Op::Add operator+(S &&val);
		template <typename S>
		CppGenerator::Op::Sub operator-(S &&val);
		template <typename S>
		CppGenerator::Op::Mul operator*(S &&val);
		template <typename S>
		CppGenerator::Op::Div operator/(S &&val);
		template <typename S>
		CppGenerator::Op::Rem operator%(S &&val);
		template <typename S>
		CppGenerator::Op::LShift operator<<(S &&val);
		template <typename S>
		CppGenerator::Op::RShift operator>>(S &&val);
		template <typename S>
		CppGenerator::Op::Less operator<(S &&val);
		template <typename S>
		CppGenerator::Op::LessEq operator<=(S &&val);
		template <typename S>
		CppGenerator::Op::Greater operator>(S &&val);
		template <typename S>
		CppGenerator::Op::GreaterEq operator>=(S &&val);
		template <typename S>
		CppGenerator::Op::Eq operator==(S &&val);
		template <typename S>
		CppGenerator::Op::Dif operator!=(S &&val);
		template <typename S>
		CppGenerator::Op::AndBin operator&(S &&val);
		template <typename S>
		CppGenerator::Op::XorBin operator^(S &&val);
		template <typename S>
		CppGenerator::Op::OrBin operator|(S &&val);
		template <typename S>
		CppGenerator::Op::And operator&&(S &&val);
		template <typename S>
		CppGenerator::Op::Or operator||(S &&val);
		template <typename S>
		CppGenerator::Op::Assign operator=(S &&val);
		template <typename S>
		CppGenerator::Op::AssignAdd operator+=(S &&val);
		template <typename S>
		CppGenerator::Op::AssignSub operator-=(S &&val);
		template <typename S>
		CppGenerator::Op::AssignMul operator*=(S &&val);
		template <typename S>
		CppGenerator::Op::AssignDiv operator/=(S &&val);
		template <typename S>
		CppGenerator::Op::AssignRem operator%=(S &&val);
		template <typename S>
		CppGenerator::Op::AssignLShift operator<<=(S &&val);
		template <typename S>
		CppGenerator::Op::AssignRShift operator>>=(S &&val);
		template <typename S>
		CppGenerator::Op::AssignAndBin operator&=(S &&val);
		template <typename S>
		CppGenerator::Op::AssignXorBin operator^=(S &&val);
		template <typename S>
		CppGenerator::Op::AssignOrBin operator|=(S &&val);

	protected:
		friend Type;
		friend Function;
		class String;

		String toString(void) const;

	private:
		void writeChar(std::ostream &o, char c)
		{
			if (c >= 32 && c < 127)
				o << c;
			else
				o << "\\x" << std::hex << static_cast<size_t>(static_cast<uint8_t>(c));
		}

		std::string stringLiteral(const std::string &src)
		{
			std::stringstream ss;

			ss << "\"";
			for (auto &c : src)
				writeChar(ss, c);
			ss << "\"";
			return ss.str();
		}

		std::string boolLiteral(bool b)
		{
			std::stringstream ss;

			ss << std::boolalpha << b;
			return ss.str();
		}

		template <typename T>
		std::string convertFloat(T f)
		{
			std::stringstream ss;

			ss << std::fixed << std::setprecision(512) << f;
			std::string raw = ss.str();

			size_t z = 0;
			for (auto it = raw.crbegin(); it != raw.crend(); it++) {
				if (*it != '0')
					break;
				z++;
			}
			return raw.substr(0, raw.size() - z);
		}

		std::string floatLiteral(float f)
		{
			std::stringstream ss;

			ss << convertFloat(f) << "f";
			return ss.str();
		}

		std::string doubleLiteral(double f)
		{
			std::stringstream ss;

			ss << convertFloat(f);
			return ss.str();
		}

		std::string longDoubleLiteral(long double f)
		{
			std::stringstream ss;

			ss << convertFloat(f) << "L";
			return ss.str();
		}

		template <typename T>
		std::string dummyConv(T val, const char *suffix = "")
		{
			std::stringstream ss;

			ss << val << suffix;
			return ss.str();
		}

		using max_unsigned = unsigned long long;
		using max_signed = long long;

		std::string convSingleChar(unsigned char u)
		{
			std::stringstream ss;

			ss << "'";
			writeChar(ss, u);
			ss << "'";
			return ss.str();
		}

		std::string unsignedCharLiteral(unsigned char u)
		{
			return convSingleChar(u);
		}

		std::string unsignedShortLiteral(unsigned short u)
		{
			return dummyConv(static_cast<max_unsigned>(u));
		}

		std::string unsignedIntLiteral(unsigned int u)
		{
			return dummyConv(static_cast<max_unsigned>(u), "U");
		}

		std::string unsignedLongLiteral(unsigned long u)
		{
			return dummyConv(static_cast<max_unsigned>(u), "UL");
		}

		std::string unsignedLongLongLiteral(unsigned long long u)
		{
			return dummyConv(static_cast<max_unsigned>(u), "ULL");
		}

		std::string charLiteral(char i)
		{
			return convSingleChar(i);
		}

		std::string shortLiteral(short i)
		{
			return dummyConv(static_cast<max_signed>(i));
		}

		std::string intLiteral(int i)
		{
			return dummyConv(static_cast<max_signed>(i));
		}

		std::string longLiteral(long i)
		{
			return dummyConv(static_cast<max_signed>(i), "L");
		}

		std::string longLongLiteral(long long i)
		{
			return dummyConv(static_cast<max_signed>(i), "LL");
		}
	};

	using Value = Value;

	class Value::String : public Value
	{
	public:
		String(const std::string &str) :
			m_str(str)
		{
		}

		void write(std::ostream &o) const override
		{
			o << m_str;
		}

	private:
		std::string m_str;
	};

	static Value Nil;

	inline Value::Value(const std::string &str) :
		Value(String(stringLiteral(str)))
	{
	}

	inline Value::Value(const char str[]) :
		Value(String(stringLiteral(str)))
	{
	}

	inline Value::Value(std::nullptr_t) :
		Value(String("nullptr"))
	{
	}

	inline Value::Value(bool b) :
		Value(String(boolLiteral(b)))
	{
	}

	inline Value::Value(float f) :
		Value(String(floatLiteral(f)))
	{
	}

	inline Value::Value(double f) :
		Value(String(doubleLiteral(f)))
	{
	}

	inline Value::Value(long double f) :
		Value(String(longDoubleLiteral(f)))
	{
	}

	inline Value::Value(unsigned char u) :
		Value(String(unsignedCharLiteral(u)))
	{
	}

	inline Value::Value(unsigned short u) :
		Value(String(unsignedShortLiteral(u)))
	{
	}

	inline Value::Value(unsigned int u) :
		Value(String(unsignedIntLiteral(u)))
	{
	}

	inline Value::Value(unsigned long u) :
		Value(String(unsignedLongLiteral(u)))
	{
	}


	inline Value::Value(unsigned long long u) :
		Value(String(unsignedLongLongLiteral(u)))
	{
	}

	inline Value::Value(char i) :
		Value(String(charLiteral(i)))
	{
	}

	inline Value::Value(short i) :
		Value(String(shortLiteral(i)))
	{
	}

	inline Value::Value(int i) :
		Value(String(intLiteral(i)))
	{
	}

	inline Value::Value(long i) :
		Value(String(longLiteral(i)))
	{
	}

	inline Value::Value(long long i) :
		Value(String(longLongLiteral(i)))
	{
	}

	inline Value::String Value::toString(void) const
	{
		return Value::String(util::sstream_str(*this));
	}

	namespace Op {
		class Unary : public Value
		{
		public:
			template <typename T>
			Unary(T &&val, const char *op) :
				m_smt(std::forward<T>(val)),
				m_op(op)
			{
			}

			void write(std::ostream &o) const override
			{
				o << "(";
				o << m_op;
				m_smt.write(o);
				o << ")";
			}

		private:
			Value m_smt;
			const char *m_op;
		};

		class PostfixUnary : public Value
		{
		public:
			template <typename T>
			PostfixUnary(T &&val, const char *op) :
				m_smt(std::forward<T>(val)),
				m_op(op)
			{
			}

			void write(std::ostream &o) const override
			{
				o << "(";
				m_smt.write(o);
				o << m_op;
				o << ")";
			}

		private:
			Value m_smt;
			const char *m_op;
		};

		class Inc : public Unary
		{
		public:
			template <typename T>
			Inc(T &&val) :
				Unary(std::forward<T>(val), "++") {}
		};

		class Dec : public Unary
		{
		public:
			template <typename T>
			Dec(T &&val) :
				Unary(std::forward<T>(val), "--") {}
		};

		class Plus : public Unary
		{
		public:
			template <typename T>
			Plus(T &&val) :
				Unary(std::forward<T>(val), "+") {}
		};

		class Minus : public Unary
		{
		public:
			template <typename T>
			Minus(T &&val) :
				Unary(std::forward<T>(val), "-") {}
		};

		class Not : public Unary
		{
		public:
			template <typename T>
			Not(T &&val) :
				Unary(std::forward<T>(val), "!") {}
		};

		class NotBin : public Unary
		{
		public:
			template <typename T>
			NotBin(T &&val) :
				Unary(std::forward<T>(val), "~") {}
		};

		class Deref : public Unary
		{
		public:
			template <typename T>
			Deref(T &&val) :
				Unary(std::forward<T>(val), "*") {}
		};

		class Address : public Unary
		{
		public:
			template <typename T>
			Address(T &&val) :
				Unary(std::forward<T>(val), "&") {}
		};
	}

	CppGenerator::Op::Inc Value::operator++(void)
	{
		return CppGenerator::Op::Inc(toString());
	}

	CppGenerator::Op::Dec Value::operator--(void)
	{
		return CppGenerator::Op::Dec(toString());
	}

	CppGenerator::Op::Plus Value::operator+(void)
	{
		return CppGenerator::Op::Plus(toString());
	}

	CppGenerator::Op::Minus Value::operator-(void)
	{
		return CppGenerator::Op::Minus(toString());
	}

	CppGenerator::Op::Not Value::operator!(void)
	{
		return CppGenerator::Op::Not(toString());
	}

	CppGenerator::Op::NotBin Value::operator~(void)
	{
		return CppGenerator::Op::NotBin(toString());
	}

	CppGenerator::Op::Deref Value::operator*(void)
	{
		return CppGenerator::Op::Deref(toString());
	}

	CppGenerator::Op::Address Value::operator&(void)
	{
		return CppGenerator::Op::Address(toString());
	}

	class Cast : public Value
	{
		class Cpp : public Value
		{
		public:
			template <typename T, typename S>
			Cpp(const char *cast_type, T &&type, S &&val) :
				m_cast_type(cast_type),
				m_type(std::forward<T>(type)),
				m_smt(std::forward<S>(val))
			{
			}

			void write(std::ostream &o) const override
			{
				o << m_cast_type;
				o << "<";
				m_type.write(o);
				o << ">(";
				m_smt.write(o);
				o << ")";
			}

		private:
			const char *m_cast_type;
			Type m_type;
			Value m_smt;
		};

	public:
		template <typename T, typename S>
		Cast(T &&type, S &&val) :
			m_type(std::forward<T>(type)),
			m_smt(std::forward<S>(val))
		{
		}

		void write(std::ostream &o) const override
		{
			o << "(";
			o << "(";
			m_type.write(o);
			o << ")";
			m_smt.write(o);
			o << ")";
		}

		class Static : public Cpp
		{
		public:
			template <typename ...Args>
			Static(Args &&...args) :
				Cpp("static_cast", std::forward<Args>(args)...) {}
		};

		class Dynamic : public Cpp
		{
		public:
			template <typename ...Args>
			Dynamic(Args &&...args) :
				Cpp("dynamic_cast", std::forward<Args>(args)...) {}
		};

		class Const : public Cpp
		{
		public:
			template <typename ...Args>
			Const(Args &&...args) :
				Cpp("const_cast", std::forward<Args>(args)...) {}
		};

		class Reinterpret : public Cpp
		{
		public:
			template <typename ...Args>
			Reinterpret(Args &&...args) :
				Cpp("reinterpret_cast", std::forward<Args>(args)...) {}
		};

	private:
		Type m_type;
		Value m_smt;
	};

	class Ternary : public Value
	{
	public:
		template <typename B, typename T, typename F>
		Ternary(B &&predicate, T &&true_smt, F &&false_smt) :
			m_predicate(std::forward<B>(predicate)),
			m_true_smt(std::forward<T>(true_smt)),
			m_false_smt(std::forward<F>(false_smt))
		{
		}

		void write(std::ostream &o) const override
		{
			o << "(";
			m_predicate.write(o);
			o << " ? ";
			m_true_smt.write(o);
			o << " : ";
			m_false_smt.write(o);
			o << ")";
		}

	private:
		Value m_predicate;
		Value m_true_smt;
		Value m_false_smt;
	};

	namespace Op {
		class Associative : public Value
		{
		public:
			template <typename Ta, typename Tb, typename ...Supp>
			Associative(const char *op, Ta &&a, Tb &&b, Supp &&...supp) :
				m_op(op),
				m_args(util::vectorize_args<Value>(std::forward<Ta>(a), std::forward<Tb>(b), std::forward<Supp>(supp)...))
			{
			}

			void write(std::ostream &o) const override
			{
				o << "(";
				auto first = true;
				for (auto &a : m_args) {
					if (!first)
						o << " " << m_op << " ";
					first = false;
					a.write(o);
				}
				o << ")";
			}

		private:
			const char *m_op;
			std::vector<Value> m_args;
		};

		class Add : public Associative
		{
		public:
			template <typename ...Args>
			Add(Args &&...args) :
				Associative("+", std::forward<Args>(args)...) {}
		};

		class Sub : public Associative
		{
		public:
			template <typename ...Args>
			Sub(Args &&...args) :
				Associative("-", std::forward<Args>(args)...) {}
		};

		class Mul : public Associative
		{
		public:
			template <typename ...Args>
			Mul(Args &&...args) :
				Associative("*", std::forward<Args>(args)...) {}
		};

		class Div : public Associative
		{
		public:
			template <typename ...Args>
			Div(Args &&...args) :
				Associative("/", std::forward<Args>(args)...) {}
		};

		class Rem : public Associative
		{
		public:
			template <typename ...Args>
			Rem(Args &&...args) :
				Associative("%", std::forward<Args>(args)...) {}
		};

		class LShift : public Associative
		{
		public:
			template <typename ...Args>
			LShift(Args &&...args) :
				Associative("<<", std::forward<Args>(args)...) {}
		};

		class RShift : public Associative
		{
		public:
			template <typename ...Args>
			RShift(Args &&...args) :
				Associative(">>", std::forward<Args>(args)...) {}
		};

		class Less : public Associative
		{
		public:
			template <typename ...Args>
			Less(Args &&...args) :
				Associative("<", std::forward<Args>(args)...) {}
		};

		class LessEq : public Associative
		{
		public:
			template <typename ...Args>
			LessEq(Args &&...args) :
				Associative("<=", std::forward<Args>(args)...) {}
		};

		class Greater : public Associative
		{
		public:
			template <typename ...Args>
			Greater(Args &&...args) :
				Associative(">", std::forward<Args>(args)...) {}
		};

		class GreaterEq : public Associative
		{
		public:
			template <typename ...Args>
			GreaterEq(Args &&...args) :
				Associative(">=", std::forward<Args>(args)...) {}
		};

		class Eq : public Associative
		{
		public:
			template <typename ...Args>
			Eq(Args &&...args) :
				Associative("==", std::forward<Args>(args)...) {}
		};

		class Dif : public Associative
		{
		public:
			template <typename ...Args>
			Dif(Args &&...args) :
				Associative("!=", std::forward<Args>(args)...) {}
		};

		class AndBin : public Associative
		{
		public:
			template <typename ...Args>
			AndBin(Args &&...args) :
				Associative("&", std::forward<Args>(args)...) {}
		};

		class XorBin : public Associative
		{
		public:
			template <typename ...Args>
			XorBin(Args &&...args) :
				Associative("^", std::forward<Args>(args)...) {}
		};

		class OrBin : public Associative
		{
		public:
			template <typename ...Args>
			OrBin(Args &&...args) :
				Associative("||", std::forward<Args>(args)...) {}
		};

		class And : public Associative
		{
		public:
			template <typename ...Args>
			And(Args &&...args) :
				Associative("&&", std::forward<Args>(args)...) {}
		};

		class Or : public Associative
		{
		public:
			template <typename ...Args>
			Or(Args &&...args) :
				Associative("||", std::forward<Args>(args)...) {}
		};

		class Assign : public Associative
		{
		public:
			template <typename ...Args>
			Assign(Args &&...args) :
				Associative("=", std::forward<Args>(args)...) {}
		};

		class AssignAdd : public Associative
		{
		public:
			template <typename ...Args>
			AssignAdd(Args &&...args) :
				Associative("+=", std::forward<Args>(args)...) {}
		};

		class AssignSub : public Associative
		{
		public:
			template <typename ...Args>
			AssignSub(Args &&...args) :
				Associative("-=", std::forward<Args>(args)...) {}
		};

		class AssignMul : public Associative
		{
		public:
			template <typename ...Args>
			AssignMul(Args &&...args) :
				Associative("*=", std::forward<Args>(args)...) {}
		};

		class AssignDiv : public Associative
		{
		public:
			template <typename ...Args>
			AssignDiv(Args &&...args) :
				Associative("/=", std::forward<Args>(args)...) {}
		};

		class AssignRem : public Associative
		{
		public:
			template <typename ...Args>
			AssignRem(Args &&...args) :
				Associative("%=", std::forward<Args>(args)...) {}
		};

		class AssignLShift : public Associative
		{
		public:
			template <typename ...Args>
			AssignLShift(Args &&...args) :
				Associative("<<=", std::forward<Args>(args)...) {}
		};

		class AssignRShift : public Associative
		{
		public:
			template <typename ...Args>
			AssignRShift(Args &&...args) :
				Associative(">>=", std::forward<Args>(args)...) {}
		};

		class AssignAndBin : public Associative
		{
		public:
			template <typename ...Args>
			AssignAndBin(Args &&...args) :
				Associative("&=", std::forward<Args>(args)...) {}
		};

		class AssignXorBin : public Associative
		{
		public:
			template <typename ...Args>
			AssignXorBin(Args &&...args) :
				Associative("^=", std::forward<Args>(args)...) {}
		};

		class AssignOrBin : public Associative
		{
		public:
			template <typename ...Args>
			AssignOrBin(Args &&...args) :
				Associative("|=", std::forward<Args>(args)...) {}
		};
	}

	template <typename S>
	CppGenerator::Op::Add Value::operator+(S &&val)
	{
		return CppGenerator::Op::Add(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::Sub Value::operator-(S &&val)
	{
		return CppGenerator::Op::Sub(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::Mul Value::operator*(S &&val)
	{
		return CppGenerator::Op::Mul(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::Div Value::operator/(S &&val)
	{
		return CppGenerator::Op::Div(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::Rem Value::operator%(S &&val)
	{
		return CppGenerator::Op::Rem(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::LShift Value::operator<<(S &&val)
	{
		return CppGenerator::Op::LShift(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::RShift Value::operator>>(S &&val)
	{
		return CppGenerator::Op::RShift(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::Less Value::operator<(S &&val)
	{
		return CppGenerator::Op::Less(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::LessEq Value::operator<=(S &&val)
	{
		return CppGenerator::Op::LessEq(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::Greater Value::operator>(S &&val)
	{
		return CppGenerator::Op::Greater(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::GreaterEq Value::operator>=(S &&val)
	{
		return CppGenerator::Op::GreaterEq(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::Eq Value::operator==(S &&val)
	{
		return CppGenerator::Op::Eq(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::Dif Value::operator!=(S &&val)
	{
		return CppGenerator::Op::Dif(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::AndBin Value::operator&(S &&val)
	{
		return CppGenerator::Op::AndBin(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::XorBin Value::operator^(S &&val)
	{
		return CppGenerator::Op::XorBin(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::OrBin Value::operator|(S &&val)
	{
		return CppGenerator::Op::OrBin(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::And Value::operator&&(S &&val)
	{
		return CppGenerator::Op::And(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::Or Value::operator||(S &&val)
	{
		return CppGenerator::Op::Or(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::Assign Value::operator=(S &&val)
	{
		return CppGenerator::Op::Assign(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::AssignAdd Value::operator+=(S &&val)
	{
		return CppGenerator::Op::AssignAdd(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::AssignSub Value::operator-=(S &&val)
	{
		return CppGenerator::Op::AssignSub(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::AssignMul Value::operator*=(S &&val)
	{
		return CppGenerator::Op::AssignMul(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::AssignDiv Value::operator/=(S &&val)
	{
		return CppGenerator::Op::AssignDiv(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::AssignRem Value::operator%=(S &&val)
	{
		return CppGenerator::Op::AssignRem(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::AssignLShift Value::operator<<=(S &&val)
	{
		return CppGenerator::Op::AssignLShift(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::AssignRShift Value::operator>>=(S &&val)
	{
		return CppGenerator::Op::AssignRShift(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::AssignAndBin Value::operator&=(S &&val)
	{
		return CppGenerator::Op::AssignAndBin(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::AssignXorBin Value::operator^=(S &&val)
	{
		return CppGenerator::Op::AssignXorBin(toString(), std::forward<S>(val));
	}

	template <typename S>
	CppGenerator::Op::AssignOrBin Value::operator|=(S &&val)
	{
		return CppGenerator::Op::AssignOrBin(toString(), std::forward<S>(val));
	}

	class Comma : public Op::Associative
	{
	public:
		template <typename ...Args>
		Comma(Args &&...args) :
			Op::Associative(",", std::forward<Args>(args)...) {}
	};

	class Value::Modifiers::Inc : public Op::PostfixUnary
	{
	public:
		template <typename T>
		Inc(T &&val) :
			Op::PostfixUnary(std::forward<T>(val), "++") {}
	};

	class Value::Modifiers::Dec : public Op::PostfixUnary
	{
	public:
		template <typename T>
		Dec(T &&val) :
			Op::PostfixUnary(std::forward<T>(val), "--") {}
	};

	inline Value::Modifiers::Inc Value::Inc(void)
	{
		return Modifiers::Inc(toString());
	}

	inline Value::Modifiers::Dec Value::Dec(void)
	{
		return Modifiers::Dec(toString());
	}

	class Value::Modifiers::Call : public Value
	{
	public:
		template <typename T, typename ...Args>
		Call(T &&val, Args &&...args) :
			m_fun_name(std::forward<T>(val)),
			m_args(util::vectorize_args<Value>(std::forward<Args>(args)...))
		{
		}

		void write(std::ostream &o) const override
		{
			m_fun_name.write(o);
			o << "(";
			auto comma = "";
			for (auto &s : m_args) {
				o << comma;
				s.write(o);
				comma = ", ";
			}
			o << ")";
		}

	private:
		Value m_fun_name;
		std::vector<Value> m_args;
	};

	template <typename ...Args>
	Value::Modifiers::Call Value::Call(Args &&...args)
	{
		return Modifiers::Call(toString(), std::forward<Args>(args)...);
	}

	class Sizeof : public Value::Modifiers::Call
	{
	public:
		template <typename T>
		Sizeof(T &&val) :
			Value::Modifiers::Call("sizeof", std::forward<T>(val)) {}
	};

	class Value::Modifiers::Array : public Value
	{
	public:
		template <typename A, typename S, typename ...Ss>
		Array(A &&array, S &&subscript, Ss &&...additional_subscript) :
			m_array(std::forward<A>(array)),
			m_subscript(util::vectorize_args<Value>(std::forward<S>(subscript), std::forward<Ss>(additional_subscript)...))
		{
		}

		void write(std::ostream &o) const override
		{
			m_array.write(o);
			for (auto &s : m_subscript) {
				o << "[";
				s.write(o);
				o << "]";
			}
		}

	private:
		Value m_array;
		std::vector<Value> m_subscript;
	};

	template <typename ...Args>
	Value::Modifiers::Array Value::Array(Args &&...args)
	{
		return Modifiers::Array(toString(), std::forward<Args>(args)...);
	}

	class Value::Modifiers::Member : public Op::Associative
	{
	public:
		template <typename ...Args>
		Member(Args &&...args) :
			Op::Associative(".", std::forward<Args>(args)...) {}
	};

	template <typename ...Args>
	Value::Modifiers::Member Value::Member(Args &&...args)
	{
		return Modifiers::Member(toString(), std::forward<Args>(args)...);
	}

	class Value::Modifiers::MemberPtr : public Op::Associative
	{
	public:
		template <typename ...Args>
		MemberPtr(Args &&...args) :
			Op::Associative("->", std::forward<Args>(args)...) {}
	};

	template <typename ...Args>
	Value::Modifiers::MemberPtr Value::MemberPtr(Args &&...args)
	{
		return Modifiers::MemberPtr(toString(), std::forward<Args>(args)...);
	}

	Value::Modifiers::Inc Value::operator++(int)
	{
		return Inc();
	}

	Value::Modifiers::Dec Value::operator--(int)
	{
		return Dec();
	}

	template <typename ...Args>
	Value::Modifiers::Call Value::operator()(Args &&...args)
	{
		return Call(std::forward<Args>(args)...);
	}

	template <typename T>
	Value::Modifiers::Array Value::operator[](T &&val)
	{
		return Array(std::forward<T>(val));
	}

	class Type::Modifiers::Array : public Type
	{
	public:
		template <typename T, typename ...Args>
		Array(T &&type, Args &&...args) :
			m_type(std::forward<T>(type)),
			m_args(util::vectorize_args<Value>(std::forward<Args>(args)...))
		{
			if (m_args.size() == 0)
				m_args.emplace_back();
		}

		void write(std::ostream &o) const override
		{
			m_type.write(o);
			for (auto &a : m_args) {
				o << "[";
				a.write(o);
				o << "]";
			}
		}

	private:
		Type m_type;
		std::vector<Value> m_args;
	};

	template <typename ...Args>
	inline Type::Modifiers::Array Type::Array(Args &&...args)
	{
		return Modifiers::Array(toString(), std::forward<Args>(args)...);
	}

	template <typename ...Args>
	Type::Modifiers::Array Type::operator[](Args &&...args)
	{
		return Modifiers::Array(toString(), std::forward<Args>(args)...);
	}

	inline Type::Modifiers::Ptr Type::operator*(void)
	{
		return Modifiers::Ptr(toString());
	}

	inline Type::Modifiers::LRef Type::operator&(void)
	{
		return Modifiers::LRef(toString());
	}

	class Class : public Util::Collection, public Type
	{
		using Type::write;

	public:
		enum class Visibility {
			Public,
			Protected,
			Private
		};

		Class(const std::string &name, Visibility base_visibility = Visibility::Public) :
			Util::Collection(name),
			Type(getBaseName()),
			m_base_visibility(base_visibility),
			m_visibility(m_base_visibility)
		{
		}
		~Class(void)
		{
		}

		static const std::string& VisibilityToStr(const Visibility &visibility)
		{
			static const std::map<Visibility, std::string> table = {
				{Visibility::Public, "public"},
				{Visibility::Protected, "protected"},
				{Visibility::Private, "private"}
			};

			return table.at(visibility);
		}

		class Member
		{
		public:
			Member(Visibility visibility) :
				m_visibility(visibility)
			{
			}
			~Member(void)
			{
			}

			operator Visibility(void) const
			{
				return m_visibility;
			}

		private:
			Visibility m_visibility;
		};

		template <typename Membered>
		class Memberize : public Membered, public Member
		{
		public:
			template <typename ...Args>
			Memberize(Visibility visibility, Args &&...args) :
				Membered(std::forward<Args>(args)...),
				Member(visibility)
			{
			}
			~Memberize(void) override
			{
			}
		};

	private:
		using Util::Collection::add;

	public:
		template <class PrimitiveType, typename ...Args>
		PrimitiveType& add(Args &&...args)
		{
			return Util::Collection::add<Memberize<PrimitiveType>>(m_visibility, std::forward<Args>(args)...);
		}

		void set(Visibility visiblity)
		{
			m_visibility = visiblity;
		}

		void write(Util::File &o) const override
		{
			o.new_line() << getPrimType() << " " << getName() << o.end_line();
			o.new_line() << "{" << o.end_line();
			o.indent();
			bool is_first = true;
			Visibility cur_vis = m_base_visibility;
			for (auto &p : getPrimitives()) {
				auto &mem = dynamic_cast<const Member&>(p);

				Visibility vis(mem);
				if (vis != cur_vis) {
					if (!is_first)
						o << o.end_line();
					o.unindent();
					o.new_line() << VisibilityToStr(mem) << ":" << o.end_line();
					o.indent();
					cur_vis = vis;
				}

				p.write(o);
				is_first = false;
			}
			o.unindent();
			o.new_line() << "};" << o.end_line();
		}

	protected:
		virtual const std::string& getPrimType(void) const
		{
			static const std::string res("class");

			return res;
		}

	private:
		Visibility m_base_visibility;
		Visibility m_visibility;
	};

	class Struct : public Class
	{
	public:
		Struct(const std::string &name) :
			Class(name, Visibility::Public)
		{
		}
		~Struct(void)
		{
		}

		const std::string& getPrimType(void) const override
		{
			static const std::string res("struct");

			return res;
		}
	};

	class Using : public Util::Primitive::Named, public Type
	{
		using Type::write;

	public:
		template <typename T>
		Using(const std::string &name, T &&type) :
			Util::Primitive::Named(name),
			Type(getBaseName()),
			m_type(std::forward<T>(type))
		{
		}
		~Using(void)
		{
		}

		void write(Util::File &o) const
		{
			o.new_line() << "using " << getName() << " = " << m_type << ";" << o.end_line();
		}

	private:
		const Type m_type;
	};


	class Statement : public Util::FileWritable
	{
		template <typename W>
		static inline constexpr bool is_w_ok_v = std::is_base_of_v<Statement, std::remove_reference_t<W>> && !std::is_same_v<std::remove_reference_t<W>, Statement>;

	public:
		Statement(void)
		{
		}

		Statement(Statement &other) :
			Util::FileWritable(other)
		{
		}
		Statement(Statement&&) = default;

		template <typename W, class = std::enable_if_t<is_w_ok_v<W> && std::is_rvalue_reference_v<W&&>>>
		Statement(W &&sub) :
			Util::FileWritable(std::move(sub))
		{
		}

		template <typename W, class = std::enable_if_t<is_w_ok_v<W>>>
		Statement(W &sub) :
			Util::FileWritable(sub)
		{
		}

		~Statement(void) override
		{
		}

		void write(Util::File &o) const override
		{
			write_sub(o);
		}
	};

	class IdentifierName : public Value
	{
	public:
		IdentifierName(const char *name) :
			m_name(name)
		{
		}

		IdentifierName(const IdentifierName &other) :
			m_name(other.m_name)
		{
		}

		void write(std::ostream &o) const override
		{
			o << m_name;
		}

	private:
		const char *m_name;
	};

	template <typename TupleType>
	class IdentifierBind : public Value
	{
	public:
		IdentifierBind(const TupleType &bind) :
			m_bind(bind)
		{
		}

		IdentifierBind(const IdentifierBind &other) :
			m_bind(other.m_bind)
		{
		}

		void write(std::ostream &o) const override
		{
			o << "[";
			writeIter(o, m_bind);
			o << "]";
		}

		const TupleType& getTuple(void) const
		{
			return m_bind;
		}

	private:
		TupleType m_bind;

		template <size_t I = 0, typename ...Types>
		void writeIter(std::ostream &o, const std::tuple<Types...> &tup) const
		{
			if constexpr (I < sizeof...(Types)) {
				if (I > 0)
					o << ", ";
				o << std::get<I>(tup);
				writeIter<I + 1>(o, tup);
			}
		}
	};

	template <typename IdentifierType>
	class Variable : public IdentifierType, public Statement
	{
	public:
		template <typename T, typename Id>
		Variable(T &&type, const Id &id) :
			IdentifierType(id),
			m_type(std::forward<T>(type))
		{
		}

		using Value::write;

		template <typename O>
		void declare(O &o) const
		{
			decl(m_type, static_cast<const Value&>(*this), o);
		}

		void write(Util::File &o) const override
		{
			o.new_line();
			declare(o);
			o << ";" << o.end_line();
		}

		template <typename T, typename Str, typename O>
		static void decl(T &&type, Str &&name, O &o)
		{
			auto s = util::sstream_str(type);

			auto size = countArrSize(s);
			auto t = s.substr(0, s.size() - size);
			auto arr = s.substr(s.size() - size, size);
			o << t;
			auto s_name = util::sstream_str(std::forward<Str>(name));
			if (s_name.size() > 0)
				o << " " << s_name;
			o << arr;
		}

	protected:
		Type m_type;

	private:
		static size_t countArrSize(const std::string &inputType)
		{
			size_t res = 0;

			size_t depth = 0;
			auto end = inputType.rend();
			for (auto it = inputType.rbegin(); it != end; it++) {
				auto c = *it;
				if (c == ']')
					depth++;
				else if (c == '[')
					depth--;
				else if (depth == 0)
					break;
				res++;
			}
			return res;
		}
	};

	template <typename IdType>
	class Util::VariableDeclWithValue : public IdType, public Statement
	{
	public:
		template <typename T, typename Id, typename V>
		VariableDeclWithValue(T &&type, const Id &id, V &&value, bool is_equal = false) :
			IdType(id),
			m_type(std::forward<T>(type)),
			m_value(std::forward<V>(value)),
			m_is_equal(is_equal)
		{
		}

		using Value::write;

		void write(Util::File &o) const override
		{
			o.new_line();
			Variable<IdType>::decl(m_type, util::sstream_str(static_cast<const Value&>(*this)), o);
			if (m_is_equal)
				o << " = ";
			else
				o << " ";
			o << m_value << ";" << o.end_line();
		}

	private:
		Type m_type;
		Value m_value;
		bool m_is_equal;
	};

	template <typename IdType>
	class Util::VariableDecl : public Variable<IdType>
	{
		using Variable<IdType>::Value::operator-;
		using Variable<IdType>::Value::operator=;

	public:
		template <typename ...Args>
		VariableDecl(Args &&...args) :
			Variable<IdType>(std::forward<Args>(args)...)
		{
		}

		template <typename V>
		VariableDeclWithValue<IdType> operator-(V &&value)
		{
			return VariableDeclWithValue<IdType>(std::move(this->m_type), static_cast<const IdType&>(*this), std::forward<V>(value));
		}

		template <typename V>
		VariableDeclWithValue<IdType> operator=(V &&value)
		{
			return VariableDeclWithValue<IdType>(std::move(this->m_type), static_cast<IdType&>(*this), std::forward<V>(value), true);
		}

		/*template <typename ...Args>
		VariableDeclCtor operator()(Args &&...args)
		{

		}*/
	};

	auto Type::operator-(const char *name)
	{
		return Util::VariableDecl<IdentifierName>(util::sstream_str(*this), name);
	}

	template <typename BindType>
	auto Type::operator-(const BindType &bind)
	{
		return Util::VariableDecl<IdentifierBind<BindType>>(util::sstream_str(*this), bind);
	}

	template <typename V, class>
	Value Type::operator-(V &&val)
	{
		return Value::String(util::sstream_str(*this) + std::string(" ") + util::sstream_str(std::forward<V>(val)));
	}

	template <typename ...Values>
	Value Type::operator()(Values &&...val)
	{
		std::stringstream ss;

		ss << *this << "(";
		auto values = util::vectorize_args<Value>(std::forward<Values>(val)...);
		auto comma = "";
		for (auto &v : values) {
			ss << comma << v;
			comma = ", ";
		}
		ss << ")";
		return Value::String(ss.str());
	}

	class Function : public Util::Primitive::Named
	{
	public:
		template <typename RetType>
		Function(RetType &&return_type, const std::string &name) :
			Util::Primitive::Named(name),
			m_return_type(std::forward<RetType>(return_type))
		{
		}
		~Function(void)
		{
		}

		template <typename ...Args>
		decltype(auto) addArg(Args &&...args)
		{
			return m_args.emplace(std::forward<Args>(args)...);
		}

		template <typename First, typename ...Args>
		decltype(auto) add(First &&first, Args &&...args)
		{
			decltype(auto) res = emplaceValSmt(std::forward<First>(first));

			if constexpr (util::are_args_empty_v<Args...>)
				return res;
			else
				return std::tuple_cat(std::tuple<decltype(res)>(res), addMul(std::forward<Args>(args)...));
		}

		template <typename Type, typename ...Args>
		Type& add(Args &&...args)
		{
			return m_smts.emplace<Type>(std::forward<Args>(args)...);
		}

		void write(Util::File &o) const
		{
			o.new_line() << m_return_type << " " << getName() << "(";

			auto comma = "";
			for (auto &a : m_args) {
				o << comma;
				a.declare(o);
				comma = ", ";
			}
			if (m_args.size() == 0)
				o << "void";
			o << ")" << o.end_line();
			o.new_line() << "{" << o.end_line();
			o.indent();
			for (auto &s : m_smts)
				s.write(o);
			o.unindent();
			o.new_line() << "}" << o.end_line();
		}

	private:
		Type m_return_type;
		util::unique_vector<Variable<IdentifierName>> m_args;
		util::unique_vector<Statement> m_smts;
		util::unique_vector<Value> m_values;

		friend Util::Collection;
		template <typename Sf, typename First, typename ...Args>
		auto popArg(Sf &&sf, First &&first, Args &&...args)
		{
			auto &to_add = addArg(std::forward<First>(first));

			auto res = std::tuple_cat(std::forward<Sf>(sf), std::tuple<Variable<IdentifierName>&>(to_add));
			if constexpr (!util::are_args_empty_v<Args...>)
				return popArg(res, std::forward<Args>(args)...);
			else
				return res;
		}

		template <size_t I, typename ...Types>
		decltype(auto) genBindValues(const std::tuple<Types...> &tup)
		{
			if constexpr (I < sizeof...(Types)) {
				auto &res = m_values.emplace(Value::String(std::get<I>(tup)));
				return std::tuple_cat(std::tuple<Value&>(res), genBindValues<I + 1>(tup));
			} else
				return std::make_tuple();
		}

		template <typename Src>
		decltype(auto) getDecl(Src &&src)
		{
			using SrcNoRef = std::remove_reference_t<Src>;

			if constexpr (util::is_base_of_template_v<IdentifierBind, SrcNoRef>)
				return genBindValues<0>(src.getTuple());
			else
				return m_values.emplace(Value::String(util::sstream_str(std::forward<Src>(src))));
		}

		template <typename Src>
		decltype(auto) emplaceValSmt(Src &&src)
		{
			using SrcNoRef = std::remove_reference_t<Src>;

			if constexpr (util::is_base_of_template_v<Variable, SrcNoRef> || util::is_base_of_template_v<Util::VariableDeclWithValue, SrcNoRef>) {
				decltype(auto) res = getDecl(std::forward<Src>(src));
				m_smts.emplace(std::forward<Src>(src));
				return res;
			} else
				return m_smts.emplace(std::forward<Src>(src));
		}

		template <typename First, typename ...Args>
		decltype(auto) addMul(First &&first, Args &&...args)
		{
			decltype(auto) res = emplaceValSmt(std::forward<First>(first));

			auto tup = std::tuple<decltype(res)>(res);
			if constexpr (util::are_args_empty_v<Args...>)
				return tup;
			else
				return std::tuple_cat(tup, addMul(std::forward<Args>(args)...));
		}
	};

	class Return : public Statement
	{
	public:
		Return(void) :
			Statement(),
			m_empty(true)
		{
		}

		template <typename V>
		Return(V &&val) :
			m_value(std::forward<V>(val))
		{
		}

		void write(Util::File &o) const override
		{
			o.new_line() << "return";
			if (!m_empty)
				o << " ";
			o << m_value << ";" << o.end_line();
		}

	private:
		Value m_value;
		bool m_empty = false;
	};

	class Brace : public Value
	{
	public:
		template<typename ...Args>
		Brace(Args &&...args) :
			m_values(util::vectorize_args<Value>(std::forward<Args>(args)...))
		{
		}

		void write(std::ostream &o) const override
		{
			o << "{";
			auto comma = "";
			for (auto &v : m_values) {
				o << comma << v;
				comma = ", ";
			}
			o << "}";
		}

	private:
		std::vector<Value> m_values;
	};

	using B = Brace;

	/*class If : public Statement
	{
	public:
		template <typename >
		If()
	};*/
}

namespace cppgen = CppGenerator;