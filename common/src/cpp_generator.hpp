#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include "util.hpp"
#include "util/sstream.hpp"

namespace CppGenerator {
	namespace Util {
		template <typename ...Types>
		class Bind : public std::tuple<Types...>
		{
		public:
			using tuple_type = std::tuple<Types...>;

			template <typename ...Args>
			Bind(Args &&...args) :
				std::tuple<Types...>(std::forward<Args>(args)...)
			{
			}
		};
	}

	template <typename ...Args>
	decltype(auto) StructuredBinding(Args &&...args)
	{
		return Util::Bind(std::make_tuple(std::forward<Args>(args)...));
	}

	template <typename ...Args>
	decltype(auto) Sb(Args &&...args)
	{
		return StructuredBinding(std::forward<Args>(args)...);
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

			operator std::ostream&(void)
			{
				return m_stream;
			}

		private:
			std::ofstream m_stream;
			size_t m_indent;
		};

		template <typename T>
		class RefHolder
		{
		public:
			virtual ~RefHolder(void) = default;

			virtual operator bool(void) const = 0;
			virtual T& get(void) = 0;

			class Unique;
			class Ref;
		};

		template <typename T>
		class RefHolder<T>::Unique : public RefHolder<T>
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

		template <typename T>
		class RefHolder<T>::Ref : public RefHolder<T>
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

		class Primitive
		{
		public:
			virtual ~Primitive(void) = default;

			virtual void write(Util::File &o) const = 0;

			class Named;
		};

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

			virtual ~GenWritable(void) = default;

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
	}

	std::ostream& operator<<(std::ostream &o, const Util::Writable &value)
	{
		value.write(o);
		return o;
	}

	class Type;

	namespace Util {
		class Void_t;
		class Storage;

		template <typename>
		class Variable;

		class IdentifierName;
		class IdentifierCtor;
		template <typename ArgsType>
		class IdentifierFunArgs;
		class Identifier
		{
		public:
			Identifier(const char *name) :
				m_name(name)
			{
			}

			template <typename ...Args>
			auto operator()(Args &&...args);

			template <typename ...Args>
			static constexpr bool isFunction(void)
			{
				if constexpr (util::are_args_empty_v<Args...>)
					return true;
				else if constexpr (isVoidOnly<Args...>())
					return true;
				else
					return areArgsFunction<Args...>();
			}

			template <typename ...Args>
			static auto tupleizeVariables(Args &&...args)
			{
				if constexpr (util::are_args_empty_v<Args...>)
					return std::make_tuple();
				else if constexpr (isVoidOnly<Args...>())
					return std::make_tuple();
				else
					return util::tupleize_args(std::forward<Args>(args)...);
			}

		private:
			friend Type;
			const char *m_name;

			template <typename First, typename ...Args>
			static constexpr bool areArgsFunction(void)
			{
				using Arg = std::remove_reference_t<First>;

				if (std::is_same_v<Arg, Util::Variable<IdentifierName>> || std::is_base_of_v<Type, Arg>) {
					if constexpr (!util::are_args_empty_v<Args...>)
						return true;
					else
						return areArgsFunction<Args...>();
				} else
					return false;
			}

			template <typename First, typename ...Args>
			static constexpr bool isVoidOnly(void)
			{
				return std::is_same_v<std::remove_reference_t<First>, Void_t> && util::are_args_empty_v<Args...>;
			}
		};
	}

	auto operator ""_id(const char *str, size_t)
	{
		return Util::Identifier(str);
	}

	class Value;

	class Type
	{
	public:
		Type(const std::string &str) :
			m_value(str)
		{
		}

		Type(const Type&) = default;
		Type(Type&&) = default;

		virtual void write(std::ostream &o) const
		{
			o << m_value;
		}

		virtual const Util::Storage& getStorage(void) const;

		virtual ~Type(void) = default;

	protected:
		const std::string m_value;

	public:
		struct Modifiers
		{
			class Ref;
			class Ptr;
			class Array;
			class Template;
		};

		template <typename ...Args>
		auto operator[](Args &&...args);
		auto operator*(void);
		auto operator&(void);

		auto operator-(const Type &other)
		{
			return Type(m_value + std::string(" ") + other.m_value);
		}

		auto operator|(const char *name);
		auto operator|(Util::Identifier &&id);
		auto operator|(Util::IdentifierCtor &&id);
		template <typename ArgsType>
		auto operator|(Util::IdentifierFunArgs<ArgsType> &&id);

	private:
		template <typename V>
		static inline constexpr bool is_bind_v = util::is_instance_of_template<V, Util::Bind>{};
		template <typename V>
		static inline constexpr bool is_identifier_v = is_bind_v<V> || std::is_same_v<std::decay_t<V>, const char*>;

	public:
		template <typename BindType, class = std::enable_if<is_bind_v<BindType>>>
		auto operator|(const BindType &bind);
		template <typename V, class = std::enable_if_t<!is_identifier_v<V> && !std::is_base_of_v<Type, std::remove_reference_t<V>>>>
		auto operator|(V &&val);

		class DeclType;
		class DeclValue;

		template <typename V>
		auto operator=(V &&value);

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
	};

	auto& operator<<(std::ostream &o, const Type &type)
	{
		type.write(o);
		return o;
	}

	auto operator ""_t(const char *str, size_t size)
	{
		std::string s;

		s.reserve(size);
		for (size_t i = 0; i < size; i++)
			s.push_back(str[i]);
		return Type(str);
	}

	namespace Util {
		class Void_t : public Type
		{
		public:
			template <typename ...Args>
			Void_t(Args &&...args) :
				Type(std::forward<Args>(args)...)
			{
			}
		};
	}

	static Type Auto("auto");
	static Util::Void_t Void("void");
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
	static Type Long("long");

	static Type Const("const");
	static Type Volatile("volatile");
	static Type Typename("typename");
	static Type Signed("signed");
	static Type Unsigned("unsigned");
	static Type Constexpr("constexpr");

	class Type::Modifiers::Ref : public Type
	{
	public:
		Ref(const Type &type) :
			Type(std::string("&") + type.m_value)
		{
		}
	};

	class Type::Modifiers::Ptr : public Type
	{
	public:
		Ptr(const Type &type) :
			Type(std::string("*") + type.m_value)
		{
		}
	};

	class Type::Modifiers::Template : public Type
	{
	public:
		template <typename ...Args>
		Template(const Type &type, Args &&...args) :
			Type(getValue(type, util::vectorize_args<Type>(std::forward<Args>(args)...)))
		{
		}

	private:
		template <typename ...Args>
		std::string getValue(const Type &type, const std::vector<Type> &args) const
		{
			std::stringstream o;

			o << type.m_value << "<";
			auto comma = "";
			for (auto &a : args) {
				o << comma << a;
				comma = ", ";
			}
			o << ">";
			return o.str();
		}
	};

	template <typename ...Args>
	auto Type::Template(Args &&...args)
	{
		return Modifiers::Template(*this, std::forward<Args>(args)...);
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

	namespace Util {
		class IdentifierCtor
		{
		public:
			template <typename ...Args>
			IdentifierCtor(const char *name, Args &&...args) :
				m_name(name),
				m_args(util::vectorize_args<Value>(std::forward<Args>(args)...))
			{
			}

		private:
			friend Type;
			const char *m_name;
			std::vector<Value> m_args;
		};

		template <typename ArgsType>
		class IdentifierFunArgs
		{
		public:
			template <typename ...Args>
			IdentifierFunArgs(const char *name, ArgsType &&args) :
				m_name(name),
				m_args(std::move(args))
			{
			}

		private:
			friend Type;
			const char *m_name;
			ArgsType m_args;
		};

		template <typename ...Args>
		auto Identifier::operator()(Args &&...args)
		{
			if constexpr (isFunction<Args...>()) {
				auto params = Identifier::tupleizeVariables(std::forward<Args>(args)...);
				return IdentifierFunArgs<decltype(params)>(m_name, std::move(params));
			} else
				return IdentifierCtor(m_name, std::forward<Args>(args)...);
		}
	}

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

	static Value::Direct This("this");
	static Value::Direct Sizeof("sizeof");
	static Value::Direct Alignof("alignof");
	static Value::Direct Asm("asm");

	auto operator ""_v(const char *str, size_t size)
	{
		std::string s;

		s.reserve(size);
		for (size_t i = 0; i < size; i++)
			s.push_back(str[i]);
		return Value::Direct(str);
	}

	namespace Util {
		class Nil_t : public Type
		{
		public:
			Nil_t(void) :
				Type("")
			{
			}

			operator Value(void) const
			{
				return Value::Direct("");
			}
		};
	}

	static Util::Nil_t N;

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

	using StaticCast = Cast::Static;
	using DynamicCast = Cast::Dynamic;
	using ConstCast = Cast::Const;
	using ReinterpretCast = Cast::Reinterpret;

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

	namespace Util {
		class VTemplate : public Value
		{
		public:
			template <typename V>
			VTemplate(V &&value) :
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

		template <typename ArgsType>
		class TTemplate : public Type
		{
		public:
			TTemplate(ArgsType &&args) :
				Type(""),
				m_args(std::move(args))
			{
			}

			void write(std::ostream &o) const override
			{
				o << "template <";
				auto comma = "";
				write_next_arg(o, m_args, comma);
				o << ">";
			}

		private:
			ArgsType m_args;

			template <size_t I = 0, typename ...Args>
			void write_next_arg(std::ostream &o, const std::tuple<Args...> &tup, const char *&comma) const
			{
				if constexpr (I < sizeof... (Args)) {
					o << comma << std::get<I>(tup);
					comma = ", ";
					write_next_arg<I + 1>(o, tup, comma);
				}
			}
		};

		class Template
		{
		public:
			Template(void)
			{
			}

			template <typename ...Args>
			auto operator()(Args &&...args)
			{
				if constexpr (sizeof... (Args) == 1) {
					if constexpr (!std::is_base_of_v<Type, Args...>)
						return VTemplate(std::forward<Args>(args)...);
					else
						return make_ttemplate(std::forward<Args>(args)...);
				} else
					return make_ttemplate(std::forward<Args>(args)...);
			}

			template <typename ...Args>
			auto make_ttemplate(Args &&...args)
			{
				auto params = Identifier::tupleizeVariables(std::forward<Args>(args)...);
				return TTemplate<decltype(params)>(std::move(params));
			}
		};
	}

	static Util::Template Template;

	class Type::Modifiers::Array : public Type
	{
	public:
		template <typename ...Args>
		Array(const Type &type, Args &&...args) :
			Type(getValue(type, std::forward<Args>(args)...))
		{
		}

	private:
		template <typename ...Args>
		std::string getValue(const Type &type, Args &&...args) const
		{
			std::stringstream o;

			auto vargs = util::vectorize_args<Value>(std::forward<Args>(args)...);
			if (vargs.size() == 0)
				vargs.emplace_back();

			type.write(o);
			for (auto &a : vargs) {
				o << "[";
				a.write(o);
				o << "]";
			}
			return o.str();
		}
	};

	template <typename ...Args>
	auto Type::operator[](Args &&...args)
	{
		return Modifiers::Array(*this, std::forward<Args>(args)...);
	}

	inline auto Type::operator*(void)
	{
		return Modifiers::Ptr(*this);
	}

	inline auto Type::operator&(void)
	{
		return Modifiers::Ref(*this);
	}

	class Statement : public Util::FileWritable
	{
		template <typename W>
		static inline constexpr bool is_w_ok_v = std::is_base_of_v<Statement, std::remove_reference_t<W>> && !std::is_same_v<std::remove_reference_t<W>, Statement>;

	public:
		Statement(void)
		{
		}

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

		void write(Util::File &o) const override
		{
			write_sub(o);
		}

		class Direct;
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

	static Statement::Direct Break("break"_v);
	static Statement::Direct Continue("continue"_v);

	class Util::Storage
	{
	public:
		Storage(void)
		{
		}
		Storage(const char *quali) :
			m_qualifiers({quali})
		{
		}
		Storage(const Storage &base, const Storage &add) :
			m_qualifiers(base.m_qualifiers)
		{
			for (auto &a : add.m_qualifiers)
				m_qualifiers.emplace_back(a);
		}

		auto operator-(const Storage &other)
		{
			return Storage(*this, other);
		}

		auto operator|(const Type &type);

		void write(std::ostream &o) const
		{
			for (auto &q : m_qualifiers)
				o << q << " ";
		}

	private:
		std::vector<const char*> m_qualifiers;
	};

	static Util::Storage Inline("inline");
	static Util::Storage Static("static");
	static Util::Storage Extern("extern");
	static Util::Storage ThreadLocal("thread_local");
	static Util::Storage Register("register");
	static Util::Storage Mutable("mutable");
	static Util::Storage Virtual("virtual");

	auto& operator<<(std::ostream &o, const Util::Storage &storage)
	{
		storage.write(o);
		return o;
	}

	namespace Util {
		template <typename ArgsType>
		class Function;

		class StorageType : public Type
		{
		public:
			StorageType(const Storage &storage, const Type &type) :
				Type(type),
				m_storage(storage)
			{
			}

			const Storage& getStorage(void) const override
			{
				return m_storage;
			}

			void write(std::ostream &o) const override
			{
				o << m_storage;
				Type::write(o);
			}

		private:
			Storage m_storage;
		};

		auto Storage::operator|(const Type &type)
		{
			return StorageType(*this, type);
		}

		class IdentifierName : public Value
		{
		public:
			IdentifierName(const char *name) :
				m_name(name)
			{
			}

			IdentifierName(const IdentifierName &other) :
				Value(),
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

		template <typename IdType>
		class Variable : public Value
		{
		public:
			template <typename Id>
			Variable(const StorageType &stype, const Id &id) :
				m_stype(stype),
				m_id(id)
			{
			}

			void write(std::ostream &o) const override
			{
				declare(o);
			}

		protected:
			template <typename O>
			void declare(O &o) const
			{
				auto s = util::sstream_str(m_stype);

				auto size = countArrSize(s);
				auto t = s.substr(0, s.size() - size);
				auto arr = s.substr(s.size() - size, size);
				o << t;
				auto s_name = util::sstream_str(static_cast<const Value&>(m_id));
				if (s_name.size() > 0)
					o << " " << s_name;
				o << arr;
			}

		public:
			class DeclValue : public Variable
			{
			public:
				template <typename V>
				DeclValue(Variable &&base, V &&value, bool is_equal = false) :
					Variable(std::move(base)),
					m_value(std::forward<V>(value)),
					m_is_equal(is_equal)
				{
				}

				void write(std::ostream &o) const override
				{
					declare(o);
					if (m_is_equal)
						o << " = ";
					else
						o << " ";
					o << m_value;
				}

			private:
				Value m_value;
				bool m_is_equal;
			};

			class DeclCtor : public Variable
			{
			public:
				template <typename ...Args>
				DeclCtor(Variable &&base, Args &&...args) :
					Variable(std::move(base)),
					m_args(util::vectorize_args<Value>(std::forward<Args>(args)...))
				{
				}

				DeclCtor(Variable &&base, std::vector<Value> &&args) :
					Variable(std::move(base)),
					m_args(std::move(args))
				{
				}

				void write(std::ostream &o) const override
				{
					declare(o);
					o << "(";
					auto comma = "";
					for (auto &a : m_args) {
						o << comma << a;
						comma = ", ";
					}
					o << ")";
				}

			private:
				std::vector<Value> m_args;
			};

			template <typename V>
			auto operator|(V &&value)
			{
				return DeclValue(std::move(*this), std::forward<V>(value));
			}

			class DeclType : public Variable
			{
			public:
				template <typename T>
				DeclType(Variable &&base, T &&type) :
					Variable(std::move(base)),
					m_type(std::forward<T>(type))
				{
				}

				void write(std::ostream &o) const override
				{
					declare(o);
					o << " = ";
					o << m_type;
				}

			private:
				Type m_type;
			};

			template <typename V>
			auto operator=(V &&value)
			{
				if constexpr (std::is_base_of_v<Type, std::remove_reference_t<V>>)
					return DeclType(std::move(*this), std::forward<V>(value));
				else
					return DeclValue(std::move(*this), std::forward<V>(value), true);
			}

			template <typename ...Args>
			auto operator()(Args &&...args)
			{
				if constexpr (Identifier::isFunction<Args...>()) {
					auto params = Identifier::tupleizeVariables(std::forward<Args>(args)...);
					return Function<decltype(params)>(Util::StorageType(this->m_storage, this->m_type), this->m_id, std::move(params));
				} else
					return DeclCtor(std::move(*this), std::forward<Args>(args)...);
			}

		private:
			StorageType m_stype;
			IdType m_id;

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
	}

	const Util::Storage& Type::getStorage(void) const
	{
		static const Util::Storage res;

		return res;
	}

	auto Type::operator|(const char *name)
	{
		return Util::Variable<Util::IdentifierName>(Util::StorageType(getStorage(), *this), name);
	}

	auto Type::operator|(Util::Identifier &&id)
	{
		return Util::Variable<Util::IdentifierName>(Util::StorageType(getStorage(), *this), id.m_name);
	}

	auto Type::operator|(Util::IdentifierCtor &&id)
	{
		return Util::Variable<Util::IdentifierName>::DeclCtor(Util::Variable<Util::IdentifierName>(Util::StorageType(getStorage(), *this), id.m_name), std::move(id.m_args));
	}

	template <typename BindType, class>
	auto Type::operator|(const BindType &bind)
	{
		return Util::Variable<Util::IdentifierBind<BindType>>(Util::StorageType(getStorage(), *this), bind);
	}

	template <typename V, class>
	auto Type::operator|(V &&val)
	{
		return Value::Direct(util::sstream_str(*this) + std::string(" ") + util::sstream_str(std::forward<V>(val)));
	}

	class Type::DeclValue : public Value
	{
	public:
		template <typename V>
		DeclValue(const Type &type, V &&value) :
			m_type(type),
			m_value(std::forward<V>(value))
		{
		}

		void write(std::ostream &o) const override
		{
			o << m_type << " = " << m_value;
		}

	private:
		Type m_type;
		Value m_value;
	};

	class Type::DeclType : public Value
	{
	public:
		DeclType(const Type &type, const Type &value) :
			m_type(type),
			m_value(value)
		{
		}

		void write(std::ostream &o) const override
		{
			o << m_type << " = " << m_value;
		}

	private:
		Type m_type;
		Type m_value;
	};

	template <typename V>
	auto Type::operator=(V &&value)
	{
		if constexpr (std::is_base_of_v<Type, std::remove_reference_t<V>>)
			return DeclType(*this, std::forward<V>(value));
		else
			return DeclValue(*this, std::forward<V>(value));
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
			return Type(ss.str());
		else
			return Value::Direct(ss.str());
	}

	template <typename O>
	auto Type::operator/(O &&other)
	{
		std::stringstream ss;

		ss << *this << ", " << other;
		return Type(ss.str());
	}

	template <typename O>
	auto Type::operator<<(O &&other)
	{
		return Modifiers::Template(*this, std::forward<O>(other));
	}

	using Statements = std::initializer_list<Statement>;
	using S = Statements;

	namespace Util {
		class Block : public Statement
		{
		public:
			Block(Statements &&smts) :
				m_smts(util::initializer_list_move<std::vector>(std::move(smts)))
			{
			}

			void write(Util::File &o) const override
			{
				o << "{" << o.end_line();
				o.indent();
				for (auto &s : m_smts)
					s.write(o);
				o.unindent();
				o.new_line() << "}";
			}

		private:
			std::vector<Statement> m_smts;
		};

		class Else_t {};
	}

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

	class For : public Statement
	{
	public:
		class Range : public Statement
		{
		public:
			template <typename Decl, typename Expr>
			Range(Decl &&decl, Expr &&expr) :
				m_decl(std::forward<Decl>(decl)),
				m_expr(std::forward<Expr>(expr))
			{
			}

			void write(Util::File &o) const override
			{
				declare(o);
				o << ";" << o.end_line();
			}

			auto operator|(Util::Block &&blk) &&;

		protected:
			void declare(Util::File &o) const
			{
				o.new_line() << "for (" << m_decl << " : " << m_expr << ")";
			}

		private:
			Value m_decl;
			Value m_expr;

			class Loop;
		};

		template <typename Decl, typename Cond, typename End>
		For(Decl &&decl, Cond &&cond, End &&end) :
			m_decl(std::forward<Decl>(decl)),
			m_cond(std::forward<Cond>(cond)),
			m_end(std::forward<End>(end))
		{
		}

		void write(Util::File &o) const override
		{
			declare(o);
			o << ";" << o.end_line();
		}

		auto operator|(Util::Block &&blk) &&;

	protected:
		void declare(Util::File &o) const
		{
			o.new_line() << "for (" << m_decl << "; " << m_cond << "; " << m_end << ")";
		}

	private:
		Value m_decl;
		Value m_cond;
		Value m_end;

		class Loop;
	};

	class For::Loop : public For
	{
	public:
		Loop(For &&f, Util::Block &&loop) :
			For(std::move(f)),
			m_loop(std::move(loop))
		{
		}

		void write(Util::File &o) const override
		{
			For::declare(o);
			o << " ";
			m_loop.write(o);
			o << o.end_line();
		}

		Util::Block m_loop;
	};

	auto For::operator|(Util::Block &&blk) &&
	{
		return Loop(std::move(*this), std::move(blk));
	}

	class For::Range::Loop : public For::Range
	{
	public:
		Loop(Range &&f, Util::Block &&loop) :
			Range(std::move(f)),
			m_loop(std::move(loop))
		{
		}

		void write(Util::File &o) const override
		{
			Range::declare(o);
			o << " ";
			m_loop.write(o);
			o << o.end_line();
		}

		Util::Block m_loop;
	};

	auto For::Range::operator|(Util::Block &&blk) &&
	{
		return Loop(std::move(*this), std::move(blk));
	}

	class While : public Statement
	{
	public:
		class Do : public Statement
		{
		public:
			template <typename Cond>
			Do(Cond &&cond) :
				m_cond(std::forward<Cond>(cond))
			{
			}

			void write(Util::File &o) const override
			{
				declare_prologue(o);
				o << "{}";
				declare_epilogue(o);
			}

			auto operator|(Util::Block &&blk) &&;

		protected:
			void declare_prologue(Util::File &o) const
			{
				o.new_line() << "do ";
			}

			void declare_epilogue(Util::File &o) const
			{
				o << " while (" << m_cond << ");" << o.end_line();
			}

		private:
			Value m_cond;

			class Loop;
		};

		template <typename Cond>
		While(Cond &&cond) :
			m_cond(std::forward<Cond>(cond))
		{
		}

		void write(Util::File &o) const override
		{
			declare(o);
			o << ";" << o.end_line();
		}

		auto operator|(Util::Block &&blk) &&;

	protected:
		void declare(Util::File &o) const
		{
			o.new_line() << "while (" << m_cond << ")";
		}

	private:
		Value m_cond;

		class Loop;
	};

	class While::Loop : public While
	{
	public:
		Loop(While &&f, Util::Block &&loop) :
			While(std::move(f)),
			m_loop(std::move(loop))
		{
		}

		void write(Util::File &o) const override
		{
			While::declare(o);
			o << " ";
			m_loop.write(o);
			o << o.end_line();
		}

		Util::Block m_loop;
	};

	auto While::operator|(Util::Block &&blk) &&
	{
		return Loop(std::move(*this), std::move(blk));
	}

	class While::Do::Loop : public While::Do
	{
	public:
		Loop(Do &&f, Util::Block &&loop) :
			Do(std::move(f)),
			m_loop(std::move(loop))
		{
		}

		void write(Util::File &o) const override
		{
			Do::declare_prologue(o);
			m_loop.write(o);
			Do::declare_epilogue(o);
		}

		Util::Block m_loop;
	};

	auto While::Do::operator|(Util::Block &&blk) &&
	{
		return Loop(std::move(*this), std::move(blk));
	}

	class If : public Statement
	{
	public:
		template <typename Cond>
		explicit If(Cond &&cond) :
			m_cond(std::forward<Cond>(cond))
		{
		}

		void write(Util::File &o) const override
		{
			declare(o);
			o << o.end_line();
		}

		void declare(Util::File &o) const
		{
			declare_part(o);
			o << ";";
		}

		auto operator|(Util::Block &&blk);
		auto operator|(Util::Else_t &e);

		using has_blk = std::false_type;

		void declare_part(Util::File &o) const
		{
			o.new_line() << "if (" << m_cond << ")";
		}

	private:
		Value m_cond;

		class Blk;
		template <typename IfType>
		class CElse;
		template <typename IfType>
		class CElseIf;
	};

	class If::Blk : public Statement
	{
	public:
		Blk(If &&f, Util::Block &&blk) :
			m_base(std::move(f)),
			m_blk(std::move(blk))
		{
		}

		void write(Util::File &o) const override
		{
			declare(o);
			o << o.end_line();
		}

		auto operator|(Util::Else_t &e);

		using has_blk = std::true_type;

		void declare(Util::File &o) const
		{
			m_base.declare_part(o);
			o << " ";
			m_blk.write(o);			
		}

	private:
		template <typename IfType>
		friend class If::CElseIf;
		If m_base;
		Util::Block m_blk;
	};

	auto If::operator|(Util::Block &&blk)
	{
		return Blk(std::move(*this), std::move(blk));
	}

	template <typename IfType>
	class If::CElse : public Statement
	{
	public:
		CElse(IfType &&f) :
			m_base(std::move(f))
		{
		}

		void write(Util::File &o) const override
		{
			declare(o);
			o << ";" << o.end_line();
		}

		auto operator|(Util::Block &&blk)
		{
			return Blk(std::move(*this), std::move(blk));
		}

		auto operator|(If &&f);

		using has_blk = std::false_type;

		void declare(Util::File &o) const
		{
			m_base.declare(o);
			if constexpr (IfType::has_blk::value)
				o << " ";
			else {
				o << o.end_line();
				o.new_line();
			}
			o << "else";
		}

	private:
		IfType m_base;

		class Blk : public Statement
		{
		public:
			Blk(CElse &&e, Util::Block &&blk) :
				m_base(std::move(e)),
				m_blk(std::move(blk))
			{
			}

			void write(Util::File &o) const override
			{
				m_base.declare(o);
				o << " ";
				m_blk.write(o);
				o << o.end_line();
			}

			using has_blk = std::true_type;

		private:
			CElse m_base;
			Util::Block m_blk;
		};
	};

	auto If::operator|(Util::Else_t&)
	{
		return CElse<If>(std::move(*this));
	}

	auto If::Blk::operator|(Util::Else_t&)
	{
		return CElse<If::Blk>(std::move(*this));
	}

	template <typename IfType>
	class If::CElseIf : public Statement
	{
	public:
		CElseIf(IfType &&f, If &&cond) :
			m_base(std::move(f)),
			m_cond(std::move(cond.m_cond))
		{
		}

		void write(Util::File &o) const override
		{
			declare(o);
			o << o.end_line();
		}

		auto operator|(Util::Block &&blk)
		{
			return Blk(std::move(*this), std::move(blk));
		}

		auto operator|(Util::Else_t&)
		{
			return CElse<CElseIf<IfType>>(std::move(*this));
		}

		using has_blk = std::false_type;

		void declare_part(Util::File &o) const
		{
			m_base.declare(o);
			o << " if (" << m_cond << ")";
		}

		void declare(Util::File &o) const
		{
			declare_part(o);
			o << ";";
		}

	private:
		IfType m_base;
		Value m_cond;

		class Blk : public Statement
		{
		public:
			Blk(CElseIf &&e, Util::Block &&blk) :
				m_base(std::move(e)),
				m_blk(std::move(blk))
			{
			}

			void write(Util::File &o) const override
			{
				declare(o);
				o << o.end_line();
			}

			auto operator|(Util::Else_t&)
			{
				return CElse<CElseIf<IfType>::Blk>(std::move(*this));
			}

			using has_blk = std::true_type;

			void declare(Util::File &o) const
			{
				m_base.declare_part(o);
				o << " ";
				m_blk.write(o);
			}

		private:
			CElseIf m_base;
			Util::Block m_blk;
		};
	};

	template <typename IfType>
	auto If::CElse<IfType>::operator|(If &&f)
	{
		return CElseIf<CElse<IfType>>(std::move(*this), std::move(f));
	}

	static Util::Else_t Else;

	namespace Util {
		class Case;
		class Default;
	}

	class Switch : public Statement
	{
		template <typename Base>
		class Smt;

	public:
		template <typename Type>
		class Casable
		{
		public:
			template <typename S, class = std::enable_if_t<!std::is_same_v<Util::Case, std::remove_reference_t<S>>>>
			auto operator||(S &&smt)
			{
				return Smt<Type>(std::move(static_cast<Type&>(*this)), std::forward<S>(smt));
			}
			auto operator||(Util::Case&);
			auto operator||(Util::Default&);
		};

		template <typename V>
		Switch(V &&val) :
			m_value(std::forward<V>(val))
		{
		}

		void declare(Util::File &o) const
		{
			o.new_line() << "switch (" << m_value << ")";
		}

		void write(Util::File &o) const override
		{
			declare(o);
			o << ";" << o.end_line();
		}

		auto operator|(Util::Block &&blk);

	private:
		Value m_value;

		class Blk;
	};

	class Switch::Blk : public Statement
	{
	public:
		Blk(Switch &&base, Util::Block &&blk) :
			m_base(std::move(base)),
			m_blk(std::move(blk))
		{
		}

		void write(Util::File &o) const override
		{
			m_base.declare(o);
			o << " ";
			m_blk.write(o);
			o << o.end_line();
		}

	private:
		Switch m_base;
		Util::Block m_blk;
	};

	auto Switch::operator|(Util::Block &&blk)
	{
		return Blk(std::move(*this), std::move(blk));
	}

	namespace Util {
		class Case
		{
			class CCase : public Statement, public Switch::Casable<CCase>
			{
			public:

				template <typename V>
				CCase(V &&val) :
					m_value(std::forward<V>(val))
				{
				}

				void write(Util::File &o) const override
				{
					o.unindent();
					o.new_line() << "case " << m_value << ":" << o.end_line();
					o.indent();
				}

				template <typename Base>
				class Stacked;

			private:
				Value m_value;
			};

		public:
			Case(void)
			{
			}

			template <typename V>
			auto operator||(V &&val)
			{
				return CCase(std::forward<V>(val));
			}

			template <typename Base>
			class Stacked
			{
			public:
				Stacked(Base &&base) :
					m_base(std::move(base))
				{
				}

				void write(Util::File &o) const
				{
					m_base.write(o);
				}

				template <typename V>
				auto operator||(V &&val)
				{
					return CCase::Stacked<Stacked<Base>>(std::move(*this), std::forward<V>(val));
				}

			private:
				Base m_base;
			};
		};

		template <typename Base>
		class Case::CCase::Stacked : public Statement, public Switch::Casable<Stacked<Base>>
		{
		public:
			template <typename ...Args>
			Stacked(Base &&base, Args &&...args) :
				m_base(std::move(base)),
				m_case(std::forward<Args>(args)...)
			{
			}

			void write(Util::File &o) const override
			{
				m_base.write(o);
				m_case.write(o);
			}

		private:
			Base m_base;
			Case::CCase m_case;
		};

		class Default : public Statement, public Switch::Casable<Default>
		{
		public:
			template <typename Base>
			class Stacked;

			Default(void)
			{
			}

			void write(Util::File &o) const override
			{
				o.unindent();
				o.new_line() << "default:" << o.end_line();
				o.indent();
			}
		};

		template <typename Base>
		class Default::Stacked : public Statement, public Switch::Casable<Stacked<Base>>
		{
		public:
			template <typename ...Args>
			Stacked(Base &&base, Args &&...args) :
				m_base(std::move(base)),
				m_default(std::forward<Args>(args)...)
			{
			}

			void write(Util::File &o) const override
			{
				m_base.write(o);
				m_default.write(o);
			}

		private:
			Base m_base;
			Default m_default;
		};
	}

	template <typename Base>
	class Switch::Smt : public Statement
	{
	public:
		template <typename S>
		Smt(Base &&base, S &&smt) :
			m_base(std::move(base)),
			m_smt(std::move(smt))
		{
		}

		void write(Util::File &o) const override
		{
			m_base.write(o);
			m_smt.write(o);
		}

	private:
		Base m_base;
		Statement m_smt;
	};

	static Util::Case Case;
	static Util::Default Default;

	template <typename Type>
	auto Switch::Casable<Type>::operator||(Util::Case&)
	{
		return Util::Case::Stacked<Type>(std::move(static_cast<Type&>(*this)));
	}

	template <typename Type>
	auto Switch::Casable<Type>::operator||(Util::Default&)
	{
		return Util::Default::Stacked<Type>(std::move(static_cast<Type&>(*this)));
	}

	namespace Util {
		template <typename ArgsType>
		class Function : public Variable<IdentifierName>
		{
		public:
			Function(const StorageType &stype, const IdentifierName &id, ArgsType &&args) :
				Variable<IdentifierName>(stype, id),
				m_args(std::move(args))
			{
			}

		private:
			template <size_t I = 0, typename ...Args>
			void write_next_arg(std::ostream &o, const std::tuple<Args...> &tup, const char *&comma) const
			{
				if constexpr (I < sizeof... (Args)) {
					o << comma << std::get<I>(tup);
					comma = ", ";
					write_next_arg<I + 1>(o, tup, comma);
				}
			}

		public:
			void write(std::ostream &o) const override
			{
				declare(o);
				o << "(";
				auto comma = "";
				write_next_arg(o, m_args, comma);
				if constexpr (std::is_same_v<ArgsType, std::tuple<>>)
					o << Void;
				o << ")";
			}

			class Impl : public Statement
			{
			public:
				Impl(Function &&func, Block &&blk) :
					m_func(std::move(func)),
					m_blk(std::move(blk))
				{
				}

				void write(File &o) const override
				{
					o.new_line();
					m_func.write(o);
					o << o.end_line();
					o.new_line();
					m_blk.write(o);
					o << o.end_line();
				}

			private:
				Function m_func;
				Block m_blk;
			};

			auto operator|(Util::Block &&blk) &&
			{
				return Impl(std::move(*this), std::move(blk));
			}

		private:
			ArgsType m_args;
		};
	}

	template <typename ArgsType>
	auto Type::operator|(Util::IdentifierFunArgs<ArgsType> &&id)
	{
		return Util::Function<ArgsType>(Util::StorageType(getStorage(), *this), id.m_name, std::move(id.m_args));
	}

	namespace Util {
		class Collection
		{
		public:
			template <typename ...Args>
			Collection(Args &&...args)
			{
				add(std::forward<Args>(args)...);
			}

			template <typename ...Args>
			decltype(auto) add(Args &&...args)
			{
				if constexpr (!util::are_args_empty_v<Args...>)
					return addMul(std::forward<Args>(args)...);
			}

		protected:
			void write_collection(Util::File &o, bool indent = true) const
			{
				if (indent)
					o.indent();
				for (auto &s : m_smts)
					s.write(o);
				if (indent)
					o.unindent();
			}

		private:
			util::unique_vector<Statement> m_smts;

			template <typename Src>
			decltype(auto) emplaceValSmt(Src &&src)
			{
				m_smts.emplace(std::move(src));
			}

			template <typename First, typename ...Args>
			decltype(auto) addMul(First &&first, Args &&...args)
			{
				emplaceValSmt(std::forward<First>(first));

				auto res = std::make_tuple();
				if constexpr (!util::are_args_empty_v<Args...>)
					return std::tuple_cat(res, addMul(std::forward<Args>(args)...));
				else
					return res;
			}
		};
	}

	class Out;

	class Namespace : public Util::Collection, public Statement
	{
		friend Out;

		struct main_t {};

		template <typename ...Args>
		Namespace(const main_t&, Args &&...args) :
			Util::Collection(std::forward<Args>(args)...),
			m_is_main(true)
		{
		}

	public:
		template <typename ...Args>
		Namespace(const std::string &name, Args &&...args) :
			Util::Collection(std::forward<Args>(args)...),
			m_name(name)
		{
		}

		void write(Util::File &o) const final
		{
			if (!m_is_main) {
				o.new_line() << "namespace " << m_name << o.end_line();
				o.new_line() << "{" << o.end_line();
			}
			write_collection(o, !m_is_main);
			if (!m_is_main)
				o.new_line() << "}" << o.end_line();
		}

	private:
		std::string m_name;
		bool m_is_main = false;
	};

	class Class : public Util::Collection, public Statement
	{
	public:
		template <typename ...Args>
		Class(const std::string &name, Args &&...args) :
			Util::Collection(std::forward<Args>(args)...),
			m_name(name)
		{
		}

		void write(Util::File &o) const final
		{
			o.new_line() << "class " << m_name << o.end_line();
			o.new_line() << "{" << o.end_line();
			write_collection(o);
			o.new_line() << "};" << o.end_line();
		}

	private:
		std::string m_name;
	};

	class Struct : public Util::Collection, public Statement
	{
	public:
		template <typename ...Args>
		Struct(const std::string &name, Args &&...args) :
			Util::Collection(std::forward<Args>(args)...),
			m_name(name)
		{
		}

		void write(Util::File &o) const final
		{
			o.new_line() << "struct " << m_name << o.end_line();
			o.new_line() << "{" << o.end_line();
			write_collection(o);
			o.new_line() << "};" << o.end_line();
		}

	private:
		std::string m_name;
	};

	class Visibility : public Statement
	{
	public:
		Visibility(const std::string &name) :
			m_name(name)
		{
		}

		void write(Util::File &o) const final
		{
			o.unindent();
			o.new_line() << m_name << ":" << o.end_line();
			o.indent();
		}

	private:
		std::string m_name;
	};

	static Visibility Public("public");
	static Visibility Protected("protected");
	static Visibility Private("private");

	class Out : public Namespace
	{
	public:
		template <typename ...Args>
		Out(const std::string &path, Args &&...args) :
			Namespace(main_t(), std::forward<Args>(args)...),
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

	namespace Util {
		namespace Pp {
			class CInclude : public Statement
			{
			public:
				CInclude(const std::string &file) :
					m_file(file)
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
			class CInclude::Std : public CInclude
			{
			public:
				template <typename ...Args>
				Std(Args &&...args) :
					CInclude(std::forward<Args>(args)...)
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

			class Include
			{
			public:
				Include(void)
				{
				}

				template <typename T>
				auto operator|(T &&t)
				{
					return CInclude(std::forward<T>(t));
				}

				template <typename T>
				auto operator<<(T &&t)
				{
					return CInclude::Std(std::forward<T>(t));
				}
			};
		}
	}

	namespace Pp {
		static Util::Pp::Include Include;
	}
}

namespace cppgen = CppGenerator;