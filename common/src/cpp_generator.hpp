#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include "util.hpp"

namespace CppGenerator {
	class Writer
	{
	public:
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

		Writer(const std::string &path, const std::string &basename) :
			m_filepath(path + std::string("/")),
			m_basedecl(basename + std::string(".hpp")),
			m_baseimpl(basename + std::string(".cpp")),
			m_decl(m_filepath + m_basedecl),
			m_impl(m_filepath + m_baseimpl)
		{
			m_decl.new_line() << "#pragma once" << m_decl.end_line() << m_decl.end_line();
			m_impl.new_line() << "#include \"" << m_basedecl << "\"" << m_decl.end_line() << m_decl.end_line();
		}
		~Writer(void)
		{
		}

		File& decl(void)
		{
			return m_decl;
		}

		File& impl(void)
		{
			return m_impl;
		}

		template <typename T>
		void write(T &&writable)
		{
			writable.write(*this);
		}

	private:
		const std::string m_filepath;
		const std::string m_basedecl;
		const std::string m_baseimpl;
		File m_decl;
		File m_impl;
	};

	namespace Util
	{
		class Primitive
		{
		public:
			virtual ~Primitive(void) = default;

			virtual void write(Writer &w) const = 0;

			class Named;
		};

		class Collection;

		class Writable
		{
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

			using HolderType = RefHolder<Writable>;

			template <typename W>
			static inline constexpr bool is_w_ok_v = !std::is_same_v<std::remove_reference_t<W>, Writable>;

		public:
			Writable(void)
			{
			}

			Writable(Writable&&) = default;

			template <typename W, class = std::enable_if_t<is_w_ok_v<W> && std::is_rvalue_reference_v<W&&>>>
			Writable(W &&sub) :
				m_sub(new HolderType::Unique(std::move(sub)))
			{
			}
			template <typename W, class = std::enable_if_t<is_w_ok_v<W>>>
			Writable(W &sub) :
				m_sub(new HolderType::Ref(sub))
			{
			}

			virtual ~Writable(void)
			{
			}

			virtual void write(std::ostream &o) const = 0;

		protected:
			void write_sub(std::ostream &o) const
			{
				if (m_sub)
					m_sub->get().write(o);
			}

			std::string toString(void) const  // explicit name instead of conversion method to avoid unwanted conversions
			{
				std::stringstream ss;

				write(ss);
				return ss.str();
			}

		private:
			std::unique_ptr<HolderType> m_sub;
		};

		class PrependKeyword;
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

		template <class PrimitiveType, typename ...Args>
		PrimitiveType& add(Args &&...args)
		{
			auto &s = Util::Primitive::Named::getStack();
			s.emplace(this);
			auto &res = m_primitives.emplace<PrimitiveType>(std::forward<Args>(args)...);
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
	};

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

		static Namespace global(void)
		{
			auto &s = Util::Primitive::Named::getStack();

			s.emplace(nullptr);
			return Namespace("");
		}

		void write(Writer &w) const override
		{
			auto isMain = getName() == "";

			if (!isMain) {
				writePrologue(w.decl());
				writePrologue(w.impl());
			}
			auto is_first = true;
			for (auto &p : getPrimitives()) {
				if (!is_first) {
					writeSep(w.decl());
					writeSep(w.impl());
				}
				is_first = false;
				p.write(w);
			}
			if (!isMain) {
				writeEpilogue(w.decl());
				writeEpilogue(w.impl());
			}
		}

	private:
		void writePrologue(Writer::File &f) const
		{
			f.new_line() << "namespace " << getName() << f.end_line();
			f.new_line() << "{" << f.end_line();
			f.indent();
		}

		void writeSep(Writer::File &f) const
		{
			f << f.end_line();
		}

		void writeEpilogue(Writer::File &f) const
		{
			f.unindent();
			f.new_line() << "}" << f.end_line();
		}
	};

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
			class ConstAhead;
			class Array;
		};

		Modifiers::LRef LRef(void);
		Modifiers::RRef RRef(void);
		template <typename ...Args>
		Modifiers::Ptr Ptr(Args &&...args);
		Modifiers::ConstAhead Const(void);
		template <typename ...Args>
		Modifiers::Array Array(Args &&...args);

		template <typename ...Args>
		Modifiers::Array operator[](Args &&...args);
		Modifiers::Ptr operator*(void);
		Modifiers::LRef operator&(void);
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

	class Util::PrependKeyword : public Type
	{
	public:
		template <typename T>
		PrependKeyword(T &&type, const char *str) :
			m_type(std::forward<T>(type)),
			m_str(str)
		{
		}

		void write(std::ostream &o) const override
		{
			o << m_str << " ";
			m_type.write(o);
		}

	private:
		Type m_type;
		const char *m_str;
	};

	class Const : public Util::PrependKeyword
	{
	public:
		template <typename T>
		Const(T &&type) :
			Util::PrependKeyword(std::forward<T>(type), "const")
		{
		}
	};

	class Volatile : public Util::PrependKeyword
	{
	public:
		template <typename T>
		Volatile(T &&type) :
			Util::PrependKeyword(std::forward<T>(type), "volatile")
		{
		}
	};

	class Typename : public Util::PrependKeyword
	{
	public:
		template <typename T>
		Typename(T &&type) :
			Util::PrependKeyword(std::forward<T>(type), "typename")
		{
		}
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

	class Type::Modifiers::ConstAhead : public Type
	{
	public:
		template <typename T>
		ConstAhead(T &&type) :
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
		return Modifiers::LRef(toString());
	}

	inline Type::Modifiers::RRef Type::RRef(void)
	{
		return Modifiers::RRef(toString());
	}

	template <typename ...Args>
	Type::Modifiers::Ptr Type::Ptr(Args &&...args)
	{
		return Modifiers::Ptr(toString(), std::forward<Args>(args)...);
	}

	inline Type::Modifiers::ConstAhead Type::Const(void)
	{
		return Modifiers::ConstAhead(toString());
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

		void write(Writer &w) const override
		{
			auto &decl = w.decl();

			decl.new_line() << getPrimType() << " " << getName() << decl.end_line();
			decl.new_line() << "{" << decl.end_line();
			decl.indent();
			bool is_first = true;
			Visibility cur_vis = m_base_visibility;
			for (auto &p : getPrimitives()) {
				auto &mem = dynamic_cast<const Member&>(p);

				Visibility vis(mem);
				if (vis != cur_vis) {
					if (!is_first)
						decl << decl.end_line();
					decl.unindent();
					decl.new_line() << VisibilityToStr(mem) << ":" << decl.end_line();
					decl.indent();
					cur_vis = vis;
				}

				p.write(w);
				is_first = false;
			}
			decl.unindent();
			decl.new_line() << "};" << decl.end_line();
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

		void write(Writer &w) const
		{
			auto &decl = w.decl();

			decl.new_line() << "using " << getName() << " = ";
			m_type.write(w.decl());
			decl << ";" << decl.end_line();
		}

	private:
		const Type m_type;
	};

	class Variable : public Util::Primitive::Named
	{
	public:
		template <typename T>
		Variable(T &&type, const std::string &name) :
			Util::Primitive::Named(name),
			m_type(std::forward<T>(type))
		{
		}
		~Variable(void)
		{
		}

		void write(Writer &w) const
		{
			auto &decl = w.decl();

			decl.new_line();
			m_type.write(decl);
			decl << " " << getName() << ";" << decl.end_line();
		}

	private:
		Type m_type;
	};

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

	class Statement : public Util::Writable
	{
		class String;

		template <typename W>
		static inline constexpr bool is_w_ok_v = std::is_base_of_v<Statement, std::remove_reference_t<W>> && !std::is_same_v<std::remove_reference_t<W>, Statement>;

	public:
		Statement(void)
		{
		}

		Statement(Statement &other) :
			Util::Writable(other)
		{
		}
		Statement(Statement&&) = default;

		template <typename W, class = std::enable_if_t<is_w_ok_v<W> && std::is_rvalue_reference_v<W&&>>>
		Statement(W &&sub) :
			Util::Writable(std::move(sub))
		{
		}

		template <typename W, class = std::enable_if_t<is_w_ok_v<W>>>
		Statement(W &sub) :
			Util::Writable(sub)
		{
		}

		Statement(const std::string &str);
		Statement(const char str[]);
		Statement(std::nullptr_t null);
		Statement(bool b);
		Statement(float f);
		Statement(double f);
		Statement(long double f);
		Statement(unsigned char u);
		Statement(unsigned short u);
		Statement(unsigned int u);
		Statement(unsigned long u);
		Statement(unsigned long long u);
		Statement(char i);
		Statement(int i);
		Statement(short s);
		Statement(long i);
		Statement(long long i);

		~Statement(void) override
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
		Modifiers::Array operator[](T &&smt);

		CppGenerator::Op::Inc operator++(void);
		CppGenerator::Op::Dec operator--(void);
		CppGenerator::Op::Plus operator+(void);
		CppGenerator::Op::Minus operator-(void);
		CppGenerator::Op::Not operator!(void);
		CppGenerator::Op::NotBin operator~(void);
		CppGenerator::Op::Deref operator*(void);
		CppGenerator::Op::Address operator&(void);

		template <typename S>
		CppGenerator::Op::Add operator+(S &&smt);
		template <typename S>
		CppGenerator::Op::Sub operator-(S &&smt);
		template <typename S>
		CppGenerator::Op::Mul operator*(S &&smt);
		template <typename S>
		CppGenerator::Op::Div operator/(S &&smt);
		template <typename S>
		CppGenerator::Op::Rem operator%(S &&smt);
		template <typename S>
		CppGenerator::Op::LShift operator<<(S &&smt);
		template <typename S>
		CppGenerator::Op::RShift operator>>(S &&smt);
		template <typename S>
		CppGenerator::Op::Less operator<(S &&smt);
		template <typename S>
		CppGenerator::Op::LessEq operator<=(S &&smt);
		template <typename S>
		CppGenerator::Op::Greater operator>(S &&smt);
		template <typename S>
		CppGenerator::Op::GreaterEq operator>=(S &&smt);
		template <typename S>
		CppGenerator::Op::Eq operator==(S &&smt);
		template <typename S>
		CppGenerator::Op::Dif operator!=(S &&smt);
		template <typename S>
		CppGenerator::Op::AndBin operator&(S &&smt);
		template <typename S>
		CppGenerator::Op::XorBin operator^(S &&smt);
		template <typename S>
		CppGenerator::Op::OrBin operator|(S &&smt);
		template <typename S>
		CppGenerator::Op::And operator&&(S &&smt);
		template <typename S>
		CppGenerator::Op::Or operator||(S &&smt);
		template <typename S>
		CppGenerator::Op::Assign operator=(S &&smt);
		template <typename S>
		CppGenerator::Op::AssignAdd operator+=(S &&smt);
		template <typename S>
		CppGenerator::Op::AssignSub operator-=(S &&smt);
		template <typename S>
		CppGenerator::Op::AssignMul operator*=(S &&smt);
		template <typename S>
		CppGenerator::Op::AssignDiv operator/=(S &&smt);
		template <typename S>
		CppGenerator::Op::AssignRem operator%=(S &&smt);
		template <typename S>
		CppGenerator::Op::AssignLShift operator<<=(S &&smt);
		template <typename S>
		CppGenerator::Op::AssignRShift operator>>=(S &&smt);
		template <typename S>
		CppGenerator::Op::AssignAndBin operator&=(S &&smt);
		template <typename S>
		CppGenerator::Op::AssignXorBin operator^=(S &&smt);
		template <typename S>
		CppGenerator::Op::AssignOrBin operator|=(S &&smt);

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

	using Smt = Statement;

	class Statement::String : public Smt
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

	inline Statement::Statement(const std::string &str) :
		Statement(String(stringLiteral(str)))
	{
	}

	inline Statement::Statement(const char str[]) :
		Statement(String(stringLiteral(str)))
	{
	}

	inline Statement::Statement(std::nullptr_t) :
		Statement(String("nullptr"))
	{
	}

	inline Statement::Statement(bool b) :
		Statement(String(boolLiteral(b)))
	{
	}

	inline Statement::Statement(float f) :
		Statement(String(floatLiteral(f)))
	{
	}

	inline Statement::Statement(double f) :
		Statement(String(doubleLiteral(f)))
	{
	}

	inline Statement::Statement(long double f) :
		Statement(String(longDoubleLiteral(f)))
	{
	}

	inline Statement::Statement(unsigned char u) :
		Statement(String(unsignedCharLiteral(u)))
	{
	}

	inline Statement::Statement(unsigned short u) :
		Statement(String(unsignedShortLiteral(u)))
	{
	}

	inline Statement::Statement(unsigned int u) :
		Statement(String(unsignedIntLiteral(u)))
	{
	}

	inline Statement::Statement(unsigned long u) :
		Statement(String(unsignedLongLiteral(u)))
	{
	}


	inline Statement::Statement(unsigned long long u) :
		Statement(String(unsignedLongLongLiteral(u)))
	{
	}

	inline Statement::Statement(char i) :
		Statement(String(charLiteral(i)))
	{
	}

	inline Statement::Statement(short i) :
		Statement(String(shortLiteral(i)))
	{
	}

	inline Statement::Statement(int i) :
		Statement(String(intLiteral(i)))
	{
	}

	inline Statement::Statement(long i) :
		Statement(String(longLiteral(i)))
	{
	}

	inline Statement::Statement(long long i) :
		Statement(String(longLongLiteral(i)))
	{
	}

	inline Statement::String Statement::toString(void) const
	{
		return Statement::String(Util::Writable::toString());
	}

	namespace Op {
		class Unary : public Smt
		{
		public:
			template <typename T>
			Unary(T &&smt, const char *op) :
				m_smt(std::forward<T>(smt)),
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
			Smt m_smt;
			const char *m_op;
		};

		class PostfixUnary : public Smt
		{
		public:
			template <typename T>
			PostfixUnary(T &&smt, const char *op) :
				m_smt(std::forward<T>(smt)),
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
			Smt m_smt;
			const char *m_op;
		};

		class Inc : public Unary
		{
		public:
			template <typename T>
			Inc(T &&smt) :
				Unary(std::forward<T>(smt), "++") {}
		};

		class Dec : public Unary
		{
		public:
			template <typename T>
			Dec(T &&smt) :
				Unary(std::forward<T>(smt), "--") {}
		};

		class Plus : public Unary
		{
		public:
			template <typename T>
			Plus(T &&smt) :
				Unary(std::forward<T>(smt), "+") {}
		};

		class Minus : public Unary
		{
		public:
			template <typename T>
			Minus(T &&smt) :
				Unary(std::forward<T>(smt), "-") {}
		};

		class Not : public Unary
		{
		public:
			template <typename T>
			Not(T &&smt) :
				Unary(std::forward<T>(smt), "!") {}
		};

		class NotBin : public Unary
		{
		public:
			template <typename T>
			NotBin(T &&smt) :
				Unary(std::forward<T>(smt), "~") {}
		};

		class Deref : public Unary
		{
		public:
			template <typename T>
			Deref(T &&smt) :
				Unary(std::forward<T>(smt), "*") {}
		};

		class Address : public Unary
		{
		public:
			template <typename T>
			Address(T &&smt) :
				Unary(std::forward<T>(smt), "&") {}
		};
	}

	CppGenerator::Op::Inc Smt::operator++(void)
	{
		return CppGenerator::Op::Inc(toString());
	}

	CppGenerator::Op::Dec Smt::operator--(void)
	{
		return CppGenerator::Op::Dec(toString());
	}

	CppGenerator::Op::Plus Smt::operator+(void)
	{
		return CppGenerator::Op::Plus(toString());
	}

	CppGenerator::Op::Minus Smt::operator-(void)
	{
		return CppGenerator::Op::Minus(toString());
	}

	CppGenerator::Op::Not Smt::operator!(void)
	{
		return CppGenerator::Op::Not(toString());
	}

	CppGenerator::Op::NotBin Smt::operator~(void)
	{
		return CppGenerator::Op::NotBin(toString());
	}

	CppGenerator::Op::Deref Smt::operator*(void)
	{
		return CppGenerator::Op::Deref(toString());
	}

	CppGenerator::Op::Address Smt::operator&(void)
	{
		return CppGenerator::Op::Address(toString());
	}

	class Cast : public Smt
	{
		class Cpp : public Smt
		{
		public:
			template <typename T, typename S>
			Cpp(const char *cast_type, T &&type, S &&smt) :
				m_cast_type(cast_type),
				m_type(std::forward<T>(type)),
				m_smt(std::forward<S>(smt))
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
			Smt m_smt;
		};

	public:
		template <typename T, typename S>
		Cast(T &&type, S &&smt) :
			m_type(std::forward<T>(type)),
			m_smt(std::forward<S>(smt))
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
		Smt m_smt;
	};

	class Ternary : public Smt
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
		Smt m_predicate;
		Smt m_true_smt;
		Smt m_false_smt;
	};

	namespace Op {
		class Associative : public Smt
		{
		public:
			template <typename Ta, typename Tb, typename ...Supp>
			Associative(const char *op, Ta &&a, Tb &&b, Supp &&...supp) :
				m_op(op),
				m_args(util::vectorize_args<Smt>(std::forward<Ta>(a), std::forward<Tb>(b), std::forward<Supp>(supp)...))
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
			std::vector<Smt> m_args;
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
	CppGenerator::Op::Add Smt::operator+(S &&smt)
	{
		return CppGenerator::Op::Add(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::Sub Smt::operator-(S &&smt)
	{
		return CppGenerator::Op::Sub(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::Mul Smt::operator*(S &&smt)
	{
		return CppGenerator::Op::Mul(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::Div Smt::operator/(S &&smt)
	{
		return CppGenerator::Op::Div(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::Rem Smt::operator%(S &&smt)
	{
		return CppGenerator::Op::Rem(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::LShift Smt::operator<<(S &&smt)
	{
		return CppGenerator::Op::LShift(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::RShift Smt::operator>>(S &&smt)
	{
		return CppGenerator::Op::RShift(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::Less Smt::operator<(S &&smt)
	{
		return CppGenerator::Op::Less(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::LessEq Smt::operator<=(S &&smt)
	{
		return CppGenerator::Op::LessEq(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::Greater Smt::operator>(S &&smt)
	{
		return CppGenerator::Op::Greater(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::GreaterEq Smt::operator>=(S &&smt)
	{
		return CppGenerator::Op::GreaterEq(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::Eq Smt::operator==(S &&smt)
	{
		return CppGenerator::Op::Eq(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::Dif Smt::operator!=(S &&smt)
	{
		return CppGenerator::Op::Dif(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::AndBin Smt::operator&(S &&smt)
	{
		return CppGenerator::Op::AndBin(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::XorBin Smt::operator^(S &&smt)
	{
		return CppGenerator::Op::XorBin(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::OrBin Smt::operator|(S &&smt)
	{
		return CppGenerator::Op::OrBin(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::And Smt::operator&&(S &&smt)
	{
		return CppGenerator::Op::And(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::Or Smt::operator||(S &&smt)
	{
		return CppGenerator::Op::Or(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::Assign Smt::operator=(S &&smt)
	{
		return CppGenerator::Op::Assign(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::AssignAdd Smt::operator+=(S &&smt)
	{
		return CppGenerator::Op::AssignAdd(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::AssignSub Smt::operator-=(S &&smt)
	{
		return CppGenerator::Op::AssignSub(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::AssignMul Smt::operator*=(S &&smt)
	{
		return CppGenerator::Op::AssignMul(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::AssignDiv Smt::operator/=(S &&smt)
	{
		return CppGenerator::Op::AssignDiv(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::AssignRem Smt::operator%=(S &&smt)
	{
		return CppGenerator::Op::AssignRem(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::AssignLShift Smt::operator<<=(S &&smt)
	{
		return CppGenerator::Op::AssignLShift(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::AssignRShift Smt::operator>>=(S &&smt)
	{
		return CppGenerator::Op::AssignRShift(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::AssignAndBin Smt::operator&=(S &&smt)
	{
		return CppGenerator::Op::AssignAndBin(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::AssignXorBin Smt::operator^=(S &&smt)
	{
		return CppGenerator::Op::AssignXorBin(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Op::AssignOrBin Smt::operator|=(S &&smt)
	{
		return CppGenerator::Op::AssignOrBin(toString(), std::forward<S>(smt));
	}

	class Comma : public Op::Associative
	{
	public:
		template <typename ...Args>
		Comma(Args &&...args) :
			Op::Associative(",", std::forward<Args>(args)...) {}
	};

	class Smt::Modifiers::Inc : public Op::PostfixUnary
	{
	public:
		template <typename T>
		Inc(T &&smt) :
			Op::PostfixUnary(std::forward<T>(smt), "++") {}
	};

	class Smt::Modifiers::Dec : public Op::PostfixUnary
	{
	public:
		template <typename T>
		Dec(T &&smt) :
			Op::PostfixUnary(std::forward<T>(smt), "--") {}
	};

	inline Smt::Modifiers::Inc Smt::Inc(void)
	{
		return Modifiers::Inc(toString());
	}

	inline Smt::Modifiers::Dec Smt::Dec(void)
	{
		return Modifiers::Dec(toString());
	}

	class Smt::Modifiers::Call : public Smt
	{
	public:
		template <typename T, typename ...Args>
		Call(T &&smt, Args &&...args) :
			m_fun_name(std::forward<T>(smt)),
			m_args(util::vectorize_args<Smt>(std::forward<Args>(args)...))
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
		Smt m_fun_name;
		std::vector<Smt> m_args;
	};

	template <typename ...Args>
	Smt::Modifiers::Call Smt::Call(Args &&...args)
	{
		return Modifiers::Call(toString(), std::forward<Args>(args)...);
	}

	class Sizeof : public Smt::Modifiers::Call
	{
	public:
		template <typename T>
		Sizeof(T &&smt) :
			Smt::Modifiers::Call("sizeof", std::forward<T>(smt)) {}
	};

	class Smt::Modifiers::Array : public Smt
	{
	public:
		template <typename A, typename S, typename ...Ss>
		Array(A &&array, S &&subscript, Ss &&...additional_subscript) :
			m_array(std::forward<A>(array)),
			m_subscript(util::vectorize_args<Smt>(std::forward<S>(subscript), std::forward<Ss>(additional_subscript)...))
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
		Smt m_array;
		std::vector<Smt> m_subscript;
	};

	template <typename ...Args>
	Smt::Modifiers::Array Smt::Array(Args &&...args)
	{
		return Modifiers::Array(toString(), std::forward<Args>(args)...);
	}

	class Smt::Modifiers::Member : public Op::Associative
	{
	public:
		template <typename ...Args>
		Member(Args &&...args) :
			Op::Associative(".", std::forward<Args>(args)...) {}
	};

	template <typename ...Args>
	Smt::Modifiers::Member Smt::Member(Args &&...args)
	{
		return Modifiers::Member(toString(), std::forward<Args>(args)...);
	}

	class Smt::Modifiers::MemberPtr : public Op::Associative
	{
	public:
		template <typename ...Args>
		MemberPtr(Args &&...args) :
			Op::Associative("->", std::forward<Args>(args)...) {}
	};

	template <typename ...Args>
	Smt::Modifiers::MemberPtr Smt::MemberPtr(Args &&...args)
	{
		return Modifiers::MemberPtr(toString(), std::forward<Args>(args)...);
	}

	Smt::Modifiers::Inc Smt::operator++(int)
	{
		return Inc();
	}

	Smt::Modifiers::Dec Smt::operator--(int)
	{
		return Dec();
	}

	template <typename ...Args>
	Smt::Modifiers::Call Smt::operator()(Args &&...args)
	{
		return Call(std::forward<Args>(args)...);
	}

	template <typename T>
	Smt::Modifiers::Array Smt::operator[](T &&smt)
	{
		return Array(std::forward<T>(smt));
	}

	class Type::Modifiers::Array : public Type
	{
	public:
		template <typename T, typename ...Args>
		Array(T &&type, Args &&...args) :
			m_type(std::forward<T>(type)),
			m_args(util::vectorize_args<Smt>(std::forward<Args>(args)...))
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
		std::vector<Smt> m_args;
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
}

namespace cppgen = CppGenerator;