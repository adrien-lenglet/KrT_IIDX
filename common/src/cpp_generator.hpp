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

		class Long_t;
		class Long_m;

		class IdentifierName;
		template <typename TupleType>
		class IdentifierBind;

		template <typename IdType>
		class Variable;
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

			if constexpr (!util::are_args_empty_v<Args...>)
				func.popArg(std::forward<Args>(args)...);
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
			for (auto &p : getPrimitives())
				p.write(o);
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
		template <typename W>
		static inline constexpr bool is_w_ok_v = std::is_base_of_v<Type, std::remove_reference_t<W>> && !std::is_same_v<std::remove_reference_t<W>, Type>;

	public:
		class Direct;

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
			class Template;
		};

		auto LRef(void);
		auto RRef(void);
		template <typename ...Args>
		auto Ptr(Args &&...args);
		auto RConst(void);
		template <typename ...Args>
		auto Array(Args &&...args);

		template <typename ...Args>
		auto operator[](Args &&...args);
		auto operator*(void);
		auto operator&(void);

		auto operator|(const char *name);
		template <typename BindType>
		auto operator|(const BindType &bind);

	private:
		template <typename V>
		static inline constexpr bool is_identifier_v = util::is_instance_of_template<V, std::tuple>{} || std::is_same_v<std::decay_t<V>, const char*>;

	public:
		template <typename V, class = std::enable_if_t<!is_identifier_v<V>>>
		auto operator|(V &&val);
		template <typename ...Values>
		Value operator()(Values &&...val);

		template <typename O>
		auto operator>>(O &&other);

		template <typename ...Args>
		auto Template(Args &&...args);
		template <typename ...Args>
		auto T(Args &&...args);

		template <typename O>
		auto operator/(O &&other);
		template <typename O>
		auto operator<<(O &&other);

	protected:
		Direct toString(void) const;
	};

	class Type::Direct : public Type
	{
	public:
		Direct(const std::string &str) :
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

	auto operator ""_t(const char *str, size_t size)
	{
		std::string s;

		s.reserve(size);
		for (size_t i = 0; i < size; i++)
			s.push_back(str[i]);
		return Type::Direct(str);
	}

	inline Type::Type(const std::string &str) :
		Type(static_cast<Direct&&>(Direct(str)))
	{
	}

	inline Type::Direct Type::toString(void) const
	{
		return Direct(util::sstream_str(*this));
	}

	static Type Auto("auto");
	static Type Void("void");
	static Type Char("char");
	static Type Short("short");
	static Type Int("int");
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

	class Util::Long_m : public Util::PrependKeyword
	{
	public:
		template <typename T>
		Long_m(T &&type) :
			Util::PrependKeyword("long", std::forward<T>(type)) {}
	};

	class Util::Long_t : public Type
	{
	public:
		template <typename ...Args>
		Long_t(Args &&...args) :
			Type(std::forward<Args>(args)...)
		{
		}

		template <typename T>
		auto operator()(T &&type)
		{
			return Util::Long_m(std::forward<T>(type));
		}
	};

	static Util::Long_t Long("long");

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

	class Constexpr : public Util::PrependKeyword
	{
	public:
		template <typename T>
		Constexpr(T &&type) :
			Util::PrependKeyword("constexpr", std::forward<T>(type)) {}
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

	inline auto Type::LRef(void)
	{
		return Modifiers::LRef(util::sstream_str(*this));
	}

	inline auto Type::RRef(void)
	{
		return Modifiers::RRef(util::sstream_str(*this));
	}

	template <typename ...Args>
	auto Type::Ptr(Args &&...args)
	{
		return Modifiers::Ptr(util::sstream_str(*this), std::forward<Args>(args)...);
	}

	inline auto Type::RConst(void)
	{
		return Modifiers::RConst(util::sstream_str(*this));
	}

	class Type::Modifiers::Template : public Type
	{
	public:
		template <typename T, typename ...Args>
		Template(T &&type, Args &&...args) :
			m_base(std::forward<T>(type)),
			m_args(util::vectorize_args<Type>(std::forward<Args>(args)...))
		{
		}

		void write(std::ostream &o) const override
		{
			o << m_base << "<";
			auto comma = "";
			for (auto &a : m_args) {
				o << comma << a;
				comma = ", ";
			}
			o << ">";
		}

	private:
		Type m_base;
		std::vector<Type> m_args;
	};

	template <typename ...Args>
	auto Type::Template(Args &&...args)
	{
		return Modifiers::Template(toString(), std::forward<Args>(args)...);
	}

	template <typename ...Args>
	auto Type::T(Args &&...args)
	{
		return Template(std::forward<Args>(args)...);
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
			class Template;
		};

		auto Inc(void);
		auto Dec(void);
		template <typename ...Args>
		auto Call(Args &&...args);
		template <typename ...Args>
		auto Array(Args &&...args);
		template <typename ...Args>
		auto Member(Args &&...args);
		template <typename ...Args>
		auto MemberPtr(Args &&...args);

		template <typename ...Args>
		decltype(auto) M(Args &&...args)
		{
			return Member(std::forward<Args>(args)...);
		}

		template <typename ...Args>
		decltype(auto) Mp(Args &&...args)
		{
			return MemberPtr(std::forward<Args>(args)...);
		}

		auto operator ++(int);
		auto operator --(int);
		template <typename ...Args>
		auto operator ()(Args &&...args);
		template <typename V>
		auto operator[](V &&val);

		auto operator++(void);
		auto operator--(void);
		auto operator+(void);
		auto operator-(void);
		auto operator!(void);
		auto operator~(void);
		auto operator*(void);
		auto operator&(void);

		template <typename S>
		auto operator+(S &&val);
		template <typename S>
		auto operator-(S &&val);
		template <typename S>
		auto operator*(S &&val);
		template <typename S>
		auto operator/(S &&val);
		template <typename S>
		auto operator%(S &&val);
		template <typename S>
		auto operator<<(S &&val);
		template <typename S>
		auto operator>>(S &&val);
		template <typename S>
		auto operator<(S &&val);
		template <typename S>
		auto operator<=(S &&val);
		template <typename S>
		auto operator>(S &&val);
		template <typename S>
		auto operator>=(S &&val);
		template <typename S>
		auto operator==(S &&val);
		template <typename S>
		auto operator!=(S &&val);
		template <typename S>
		auto operator&(S &&val);
		template <typename S>
		auto operator^(S &&val);
		template <typename S>
		auto operator|(S &&val);
		template <typename S>
		auto operator&&(S &&val);
		template <typename S>
		auto operator||(S &&val);
		template <typename S>
		auto operator=(S &&val);
		template <typename S>
		auto operator+=(S &&val);
		template <typename S>
		auto operator-=(S &&val);
		template <typename S>
		auto operator*=(S &&val);
		template <typename S>
		auto operator/=(S &&val);
		template <typename S>
		auto operator%=(S &&val);
		template <typename S>
		auto operator<<=(S &&val);
		template <typename S>
		auto operator>>=(S &&val);
		template <typename S>
		auto operator&=(S &&val);
		template <typename S>
		auto operator^=(S &&val);
		template <typename S>
		auto operator|=(S &&val);
		template <typename S>
		auto operator,(S &&val);

		class Direct;

		template <typename ...Args>
		auto Template(Args &&...args);
		template <typename ...Args>
		auto T(Args &&...args);

	protected:
		Direct toString(void) const;

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

		template <typename V>
		std::string convertFloat(V f)
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

		template <typename V>
		std::string dummyConv(V val, const char *suffix = "")
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

	class Value::Direct : public Value
	{
	public:
		Direct(const std::string &str) :
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

	auto operator ""_v(const char *str, size_t size)
	{
		std::string s;

		s.reserve(size);
		for (size_t i = 0; i < size; i++)
			s.push_back(str[i]);
		return Value::Direct(str);
	}

	static Value Nil;

	inline Value::Value(const std::string &str) :
		Value(Direct(stringLiteral(str)))
	{
	}

	inline Value::Value(const char str[]) :
		Value(Direct(stringLiteral(str)))
	{
	}

	inline Value::Value(std::nullptr_t) :
		Value(Direct("nullptr"))
	{
	}

	inline Value::Value(bool b) :
		Value(Direct(boolLiteral(b)))
	{
	}

	inline Value::Value(float f) :
		Value(Direct(floatLiteral(f)))
	{
	}

	inline Value::Value(double f) :
		Value(Direct(doubleLiteral(f)))
	{
	}

	inline Value::Value(long double f) :
		Value(Direct(longDoubleLiteral(f)))
	{
	}

	inline Value::Value(unsigned char u) :
		Value(Direct(unsignedCharLiteral(u)))
	{
	}

	inline Value::Value(unsigned short u) :
		Value(Direct(unsignedShortLiteral(u)))
	{
	}

	inline Value::Value(unsigned int u) :
		Value(Direct(unsignedIntLiteral(u)))
	{
	}

	inline Value::Value(unsigned long u) :
		Value(Direct(unsignedLongLiteral(u)))
	{
	}


	inline Value::Value(unsigned long long u) :
		Value(Direct(unsignedLongLongLiteral(u)))
	{
	}

	inline Value::Value(char i) :
		Value(Direct(charLiteral(i)))
	{
	}

	inline Value::Value(short i) :
		Value(Direct(shortLiteral(i)))
	{
	}

	inline Value::Value(int i) :
		Value(Direct(intLiteral(i)))
	{
	}

	inline Value::Value(long i) :
		Value(Direct(longLiteral(i)))
	{
	}

	inline Value::Value(long long i) :
		Value(Direct(longLongLiteral(i)))
	{
	}

	inline Value::Direct Value::toString(void) const
	{
		return Direct(util::sstream_str(*this));
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

	auto Value::operator++(void)
	{
		return Op::Inc(toString());
	}

	auto Value::operator--(void)
	{
		return Op::Dec(toString());
	}

	auto Value::operator+(void)
	{
		return Op::Plus(toString());
	}

	auto Value::operator-(void)
	{
		return Op::Minus(toString());
	}

	auto Value::operator!(void)
	{
		return Op::Not(toString());
	}

	auto Value::operator~(void)
	{
		return Op::NotBin(toString());
	}

	auto Value::operator*(void)
	{
		return Op::Deref(toString());
	}

	auto Value::operator&(void)
	{
		return Op::Address(toString());
	}

	class Cast : public Value
	{
		class Cpp : public Value
		{
		public:
			template <typename Tp, typename S>
			Cpp(const char *cast_type, Tp &&type, S &&val) :
				m_cast_type(cast_type),
				m_type(std::forward<Tp>(type)),
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

	class Paren : public Value
	{
	public:
		template <typename V>
		Paren(V &&value) :
			m_value(std::forward<V>(value))
		{
		}

		void write(std::ostream &o) const override
		{
			o << "(" << m_value << ")";
		}

	private:
		Value m_value;
	};

	namespace Op {
		template <bool do_space>
		class GenAssociative : public Value
		{
		public:
			template <typename Ta, typename Tb, typename ...Supp>
			GenAssociative(const char *op, Ta &&a, Tb &&b, Supp &&...supp) :
				m_op(op),
				m_args(util::vectorize_args<Value>(std::forward<Ta>(a), std::forward<Tb>(b), std::forward<Supp>(supp)...))
			{
			}

			void write(std::ostream &o) const override
			{
				o << "(";
				auto first = true;
				for (auto &a : m_args) {
					if (!first) {
						if constexpr (do_space)
							o << " " << m_op << " ";
						else
							o << m_op;
					}
					first = false;
					a.write(o);
				}
				o << ")";
			}

		private:
			const char *m_op;
			std::vector<Value> m_args;
		};

		using Associative = GenAssociative<true>;
		using AssociativeNoSpace = GenAssociative<false>;

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

		class Comma : public AssociativeNoSpace
		{
		public:
			template <typename ...Args>
			Comma(Args &&...args) :
				AssociativeNoSpace(", ", std::forward<Args>(args)...) {}
		};
	}

	template <typename S>
	auto Value::operator+(S &&val)
	{
		return Op::Add(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator-(S &&val)
	{
		return Op::Sub(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator*(S &&val)
	{
		return Op::Mul(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator/(S &&val)
	{
		return Op::Div(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator%(S &&val)
	{
		return Op::Rem(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator<<(S &&val)
	{
		return Op::LShift(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator>>(S &&val)
	{
		return Op::RShift(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator<(S &&val)
	{
		return Op::Less(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator<=(S &&val)
	{
		return Op::LessEq(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator>(S &&val)
	{
		return Op::Greater(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator>=(S &&val)
	{
		return Op::GreaterEq(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator==(S &&val)
	{
		return Op::Eq(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator!=(S &&val)
	{
		return Op::Dif(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator&(S &&val)
	{
		return Op::AndBin(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator^(S &&val)
	{
		return Op::XorBin(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator|(S &&val)
	{
		return Op::OrBin(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator&&(S &&val)
	{
		return Op::And(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator||(S &&val)
	{
		return Op::Or(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator=(S &&val)
	{
		return Op::Assign(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator+=(S &&val)
	{
		return Op::AssignAdd(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator-=(S &&val)
	{
		return Op::AssignSub(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator*=(S &&val)
	{
		return Op::AssignMul(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator/=(S &&val)
	{
		return Op::AssignDiv(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator%=(S &&val)
	{
		return Op::AssignRem(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator<<=(S &&val)
	{
		return Op::AssignLShift(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator>>=(S &&val)
	{
		return Op::AssignRShift(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator&=(S &&val)
	{
		return Op::AssignAndBin(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator^=(S &&val)
	{
		return Op::AssignXorBin(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator|=(S &&val)
	{
		return Op::AssignOrBin(toString(), std::forward<S>(val));
	}

	template <typename S>
	auto Value::operator,(S &&val)
	{
		return CppGenerator::Op::Comma(toString(), std::forward<S>(val));
	}

	template <typename ...Args>
	auto Value::Template(Args &&...args)
	{
		return CppGenerator::Value::Modifiers::Template(toString(), std::forward<Args>(args)...);
	}

	template <typename ...Args>
	auto Value::T(Args &&...args)
	{
		return Template(std::forward<Args>(args)...);
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

	inline auto Value::Inc(void)
	{
		return Modifiers::Inc(toString());
	}

	inline auto Value::Dec(void)
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
	auto Value::Call(Args &&...args)
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
	auto Value::Array(Args &&...args)
	{
		return Modifiers::Array(toString(), std::forward<Args>(args)...);
	}

	class Value::Modifiers::Member : public Op::AssociativeNoSpace
	{
	public:
		template <typename ...Args>
		Member(Args &&...args) :
			Op::AssociativeNoSpace(".", std::forward<Args>(args)...) {}
	};

	template <typename ...Args>
	auto Value::Member(Args &&...args)
	{
		return Modifiers::Member(toString(), std::forward<Args>(args)...);
	}

	class Value::Modifiers::MemberPtr : public Op::AssociativeNoSpace
	{
	public:
		template <typename ...Args>
		MemberPtr(Args &&...args) :
			Op::AssociativeNoSpace("->", std::forward<Args>(args)...) {}
	};

	template <typename ...Args>
	auto Value::MemberPtr(Args &&...args)
	{
		return Modifiers::MemberPtr(toString(), std::forward<Args>(args)...);
	}

	auto Value::operator++(int)
	{
		return Inc();
	}

	auto Value::operator--(int)
	{
		return Dec();
	}

	template <typename ...Args>
	auto Value::operator()(Args &&...args)
	{
		return Call(std::forward<Args>(args)...);
	}

	template <typename V>
	auto Value::operator[](V &&val)
	{
		return Array(std::forward<V>(val));
	}

	class Value::Modifiers::Template : public Value
	{
	public:
		template <typename V, typename ...Args>
		Template(V &&val, Args &&...args) :
			m_base(std::forward<V>(val)),
			m_args(util::vectorize_args<Type>(std::forward<Args>(args)...))
		{
		}

		void write(std::ostream &o) const override
		{
			o << m_base << "<";
			auto comma = "";
			for (auto &a : m_args) {
				o << comma << a;
				comma = ", ";
			}
			o << ">";
		}

	private:
		Value m_base;
		std::vector<Type> m_args;
	};

	class Template : public Value
	{
	public:
		template <typename V>
		Template(V &&value) :
			m_value(std::forward<V>(value))
		{
		}

		void write(std::ostream &o) const override
		{
			o << "template " << m_value;
		}

	private:
		Value m_value;
	};

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
	auto Type::Array(Args &&...args)
	{
		return Modifiers::Array(toString(), std::forward<Args>(args)...);
	}

	template <typename ...Args>
	auto Type::operator[](Args &&...args)
	{
		return Modifiers::Array(toString(), std::forward<Args>(args)...);
	}

	inline auto Type::operator*(void)
	{
		return Modifiers::Ptr(toString());
	}

	inline auto Type::operator&(void)
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
		class Direct;

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

		Statement(Value &val);
		Statement(Value &&val);

		~Statement(void) override
		{
		}

		void write(Util::File &o) const override
		{
			write_sub(o);
		}
	};

	class Statement::Direct : public Statement
	{
	public:
		template <typename V>
		Direct(V &&value) :
			m_value(Value::Direct(util::sstream_str(std::forward<V>(value))))
		{
		}

		void write(Util::File &o) const override
		{
			o.new_line() << m_value << ";" << o.end_line();
		}

	private:
		Value m_value;
	};

	Statement::Statement(Value &val) :
		Statement(Statement::Direct(val))
	{
	}

	Statement::Statement(Value &&val) :
		Statement(Statement::Direct(std::move(val)))
	{
	}

	class Util::IdentifierName : public Value
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
	class Util::IdentifierBind : public Value
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

	template <typename IdType>
	class Util::Variable : public Value
	{
	public:
		template <typename T, typename Id>
		Variable(T &&type, const Id &id) :
			m_type(std::forward<T>(type)),
			m_id(id)
		{
		}

		using Value::write;

		template <typename O>
		void declare(O &o) const
		{
			decl(m_type, static_cast<const Value&>(m_id), o);
		}

		void write(std::ostream &o) const override
		{
			declare(o);
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
		IdType m_id;

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
	class Util::VariableDeclWithValue : public Value
	{
	public:
		template <typename T, typename Id, typename V>
		VariableDeclWithValue(T &&type, const Id &id, V &&value, bool is_equal = false) :
			m_type(std::forward<T>(type)),
			m_id(id),
			m_value(std::forward<V>(value)),
			m_is_equal(is_equal)
		{
		}

		void write(std::ostream &o) const override
		{
			Util::Variable<IdType>::decl(m_type, util::sstream_str(static_cast<const Value&>(m_id)), o);
			if (m_is_equal)
				o << " = ";
			else
				o << " ";
			o << m_value;
		}

	private:
		Type m_type;
		IdType m_id;
		Value m_value;
		bool m_is_equal;
	};

	template <typename IdType>
	class Util::VariableDecl : public Util::Variable<IdType>
	{
		using Util::Variable<IdType>::Value::operator|;
		using Util::Variable<IdType>::Value::operator=;

	public:
		template <typename ...Args>
		VariableDecl(Args &&...args) :
			Util::Variable<IdType>(std::forward<Args>(args)...)
		{
		}

		template <typename V>
		auto operator|(V &&value)
		{
			return VariableDeclWithValue<IdType>(std::move(this->m_type), this->m_id, std::forward<V>(value));
		}

		template <typename V>
		VariableDeclWithValue<IdType> operator=(V &&value)
		{
			return VariableDeclWithValue<IdType>(std::move(this->m_type), this->m_id, std::forward<V>(value), true);
		}

		/*template <typename ...Args>
		VariableDeclCtor operator()(Args &&...args)
		{

		}*/
	};

	auto Type::operator|(const char *name)
	{
		return Util::VariableDecl<Util::IdentifierName>(util::sstream_str(*this), name);
	}

	template <typename BindType>
	auto Type::operator|(const BindType &bind)
	{
		return Util::VariableDecl<Util::IdentifierBind<BindType>>(util::sstream_str(*this), bind);
	}

	template <typename V, class>
	auto Type::operator|(V &&val)
	{
		return Value::Direct(util::sstream_str(*this) + std::string(" ") + util::sstream_str(std::forward<V>(val)));
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
		return Value::Direct(ss.str());
	}

	template <typename O>
	auto Type::operator>>(O &&other)
	{
		std::stringstream ss;

		ss << *this << "::" << other;

		if constexpr (std::is_base_of_v<Type, std::remove_reference_t<O>>)
			return Direct(ss.str());
		else
			return Value::Direct(ss.str());
	}

	template <typename O>
	auto Type::operator/(O &&other)
	{
		std::stringstream ss;

		ss << *this << ", " << other;
		return Direct(ss.str());
	}

	template <typename O>
	auto Type::operator<<(O &&other)
	{
		return Modifiers::Template(toString(), std::forward<O>(other));
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
		util::unique_vector<Util::Variable<Util::IdentifierName>> m_args;
		util::unique_vector<Statement> m_smts;
		util::unique_vector<Value> m_values;

		friend Util::Collection;
		template <typename First, typename ...Args>
		decltype(auto) popArg(First &&first, Args &&...args)
		{
			auto &to_add = addArg(std::forward<First>(first));

			auto res = std::tuple<Util::Variable<Util::IdentifierName>&>(to_add);
			if constexpr (!util::are_args_empty_v<Args...>)
				return std::tuple_cat(res, popArg(std::forward<Args>(args)...));
			else
				return res;
		}

		template <typename Src>
		decltype(auto) emplaceValSmt(Src &&src)
		{
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

	namespace Pp {
		class Include : public Util::Primitive
		{
		public:
			Include(const std::string &file) :
				m_file(file)
			{
			}
			~Include(void) override
			{
			}

			void write(Util::File &o) const override
			{
				o.new_line() << "#include " << lquote() << m_file << rquote() << o.end_line();
			}

			class Std;

		protected:
			virtual const std::string& lquote(void) const
			{
				static const std::string res("\"");

				return res;
			}

			virtual const std::string& rquote(void) const
			{
				static const std::string res("\"");

				return res;
			}

		private:
			const std::string m_file;
		};

		class Include::Std : public Include
		{
		public:
			template <typename ...Args>
			Std(Args &&...args) :
				Include(std::forward<Args>(args)...)
			{
			}

		protected:
			const std::string& lquote(void) const override
			{
				static const std::string res("<");

				return res;
			}

			const std::string& rquote(void) const override
			{
				static const std::string res(">");

				return res;
			}
		};
	}

	class For : public Statement
	{
	public:
		class Range : public Statement
		{
		public:
			template <typename Decl, typename Expr, typename ...Loop>
			Range(Decl &&decl, Expr &&expr, Loop &&...loop) :
				m_decl(std::forward<Decl>(decl)),
				m_expr(std::forward<Expr>(expr)),
				m_loop(util::vectorize_args<Statement>(std::forward<Loop>(loop)...))
			{
			}

			void write(Util::File &o) const override
			{
				o.new_line() << "for (" << m_decl << " : " << m_expr << ") {" << o.end_line();
				o.indent();
				for (auto &s : m_loop)
					s.write(o);
				o.unindent();
				o.new_line() << "}" << o.end_line();
			}

		private:
			Value m_decl;
			Value m_expr;
			std::vector<Statement> m_loop;
		};

		template <typename Decl, typename Cond, typename End, typename ...Loop>
		For(Decl &&decl, Cond &&cond, End &&end, Loop &&...loop) :
			m_decl(std::forward<Decl>(decl)),
			m_cond(std::forward<Cond>(cond)),
			m_end(std::forward<End>(end)),
			m_loop(util::vectorize_args<Statement>(std::forward<Loop>(loop)...))
		{
		}

		void write(Util::File &o) const override
		{
			o.new_line() << "for (" << m_decl << "; " << m_cond << "; " << m_end << ") {" << o.end_line();
			o.indent();
			for (auto &s : m_loop)
				s.write(o);
			o.unindent();
			o.new_line() << "}" << o.end_line();
		}

	private:
		Value m_decl;
		Value m_cond;
		Value m_end;
		std::vector<Statement> m_loop;
	};

	class While : public Statement
	{
	public:
		class Do : public Statement
		{
		public:
			template <typename Cond, typename ...Loop>
			Do(Cond &&cond, Loop &&...loop) :
				m_cond(std::forward<Cond>(cond)),
				m_loop(util::vectorize_args<Statement>(std::forward<Loop>(loop)...))
			{
			}

			void write(Util::File &o) const override
			{
				o.new_line() << "do {" << o.end_line();
				o.indent();
				for (auto &s : m_loop)
					s.write(o);
				o.unindent();
				o.new_line() << "} while (" << m_cond << ");" << o.end_line();
			}

		private:
			Value m_cond;
			std::vector<Statement> m_loop;
		};

		template <typename Cond, typename ...Loop>
		While(Cond &&cond, Loop &&...loop) :
			m_cond(std::forward<Cond>(cond)),
			m_loop(util::vectorize_args<Statement>(std::forward<Loop>(loop)...))
		{
		}

		void write(Util::File &o) const override
		{
			o.new_line() << "while (" << m_cond << ") {" << o.end_line();
			o.indent();
			for (auto &s : m_loop)
				s.write(o);
			o.unindent();
			o.new_line() << "}" << o.end_line();
		}

	private:
		Value m_cond;
		std::vector<Statement> m_loop;
	};

	class If : public Statement
	{
	protected:
		class Payload
		{
		public:
			template <typename Cond, typename ...Smts>
			Payload(Cond &&cond, Smts &&...smts) :
				m_cond(std::forward<Cond>(cond)),
				m_smts(util::vectorize_args<Statement>(std::forward<Smts>(smts)...))
			{
			}

			void write(Util::File &o) const
			{
				o << "if (" << m_cond << ") {" << o.end_line();
				o.indent();
				for (auto &s : m_smts)
					s.write(o);
				o.unindent();
				o.new_line() << "}";
			}

		private:
			Value m_cond;
			std::vector<Statement> m_smts;
		};

	public:
		template <typename Cond, typename ...Smts>
		If(Cond &&cond, Smts &&...smts) :
			m_payload(std::forward<Cond>(cond), std::forward<Smts>(smts)...)
		{
		}

		void write(Util::File &o) const override
		{
			o.new_line();
			m_payload.write(o);
			o << o.end_line();
		}

		template <typename Cond, typename ...Smts>
		auto ElseIf(Cond &&cond, Smts &&...smts);

		template <typename ...Smts>
		auto Else(Smts &&...smts);

	protected:
		Payload m_payload;

	private:
		class CElseIf;
		class CElse;
		friend CElseIf;
		friend CElse;
	};

	class If::CElseIf : public Statement
	{
	public:
		template <typename Cond, typename ...Smts>
		CElseIf(If &&f, Cond &&cond, Smts &&...smts) :
			m_base_payload(std::move(f.m_payload))
		{
			m_payloads.emplace_back(std::forward<Cond>(cond), std::forward<Smts>(smts)...);
		}

		template <typename Cond, typename ...Smts>
		CElseIf(CElseIf &&f, Cond &&cond, Smts &&...smts) :
			m_base_payload(std::move(f.m_base_payload)),
			m_payloads(std::move(f.m_payloads))
		{
			m_payloads.emplace_back(std::forward<Cond>(cond), std::forward<Smts>(smts)...);
		}

		void write(Util::File &o) const override
		{
			o.new_line();
			m_base_payload.write(o);
			for (auto &p : m_payloads) {
				o << " else ";
				p.write(o);
			}
			o << o.end_line();
		}

		template <typename Cond, typename ...Smts>
		auto ElseIf(Cond &&cond, Smts &&...smts)
		{
			return CElseIf(std::move(*this), std::forward<Cond>(cond), std::forward<Smts>(smts)...);
		}

		template <typename ...Smts>
		auto Else(Smts &&...smts);

	private:
		friend CElse;

		Payload m_base_payload;
		std::vector<Payload> m_payloads;
	};

	template <typename Cond, typename ...Smts>
	auto If::ElseIf(Cond &&cond, Smts &&...smts)
	{
		return CElseIf(std::move(*this), std::forward<Cond>(cond), std::forward<Smts>(smts)...);
	}

	class If::CElse : public Statement
	{
	public:
		template <typename ...Smts>
		CElse(If &&f, Smts &&...smts) :
			m_base_payload(std::move(f.m_payload)),
			m_smts(util::vectorize_args<Statement>(std::forward<Smts>(smts)...))
		{
		}

		template <typename ...Smts>
		CElse(CElseIf &&f, Smts &&...smts) :
			m_base_payload(std::move(f.m_base_payload)),
			m_payloads(std::move(f.m_payloads)),
			m_smts(util::vectorize_args<Statement>(std::forward<Smts>(smts)...))
		{
		}

		void write(Util::File &o) const override
		{
			o.new_line();
			m_base_payload.write(o);
			for (auto &p : m_payloads) {
				o << " else ";
				p.write(o);
			}
			o << " else {" << o.end_line();
			o.indent();
			for (auto &s : m_smts)
				s.write(o);
			o.unindent();
			o.new_line() << "}" << o.end_line();
		}

	private:
		Payload m_base_payload;
		std::vector<Payload> m_payloads;
		std::vector<Statement> m_smts;
	};

	template <typename ...Smts>
	auto If::Else(Smts &&...smts)
	{
		return CElse(std::move(*this), std::forward<Smts>(smts)...);
	}

	template <typename ...Smts>
	auto If::CElseIf::Else(Smts &&...smts)
	{
		return CElse(std::move(*this), std::forward<Smts>(smts)...);
	}
}

namespace cppgen = CppGenerator;