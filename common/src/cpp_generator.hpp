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

	class Primitive
	{
	public:
		virtual ~Primitive(void) = default;

		virtual void write(Writer &w) const = 0;

		class Named;
	};
	
	class Collection;
	class Namespace;

	class Primitive::Named : public Primitive
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
		Primitive::Named *m_parent;
		const std::string m_base_name;

		friend Collection;
		friend Namespace;
		static std::stack<Primitive::Named*>& getStack(void)
		{
			static thread_local std::stack<Primitive::Named*> res;

			return res;
		}
	};

	class Collection : public Primitive::Named
	{
	public:
		Collection(const std::string &name) :
			Primitive::Named(name)
		{
		}
		~Collection(void) override
		{
		}

		template <class PrimitiveType, typename ...Args>
		PrimitiveType& add(Args &&...args)
		{
			auto &s = Primitive::Named::getStack();
			s.emplace(this);
			auto &res = m_primitives.emplace<PrimitiveType>(std::forward<Args>(args)...);
			s.pop();
			return res;
		}
	
	protected:
		const util::unique_vector<Primitive>& getPrimitives(void) const
		{
			return m_primitives;
		}

	private:
		util::unique_vector<Primitive> m_primitives;
	};

	class Namespace : public Collection
	{
	public:
		Namespace(const std::string &name) :
			Collection(name)
		{
			if (name == "")
				Primitive::Named::getStack().pop();
		}
		~Namespace(void) override
		{
		}

		static Namespace global(void)
		{
			auto &s = Primitive::Named::getStack();

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

	class Type : public Writable
	{
		class String;

		template <typename W>
		static inline constexpr bool is_w_ok_v = std::is_base_of_v<Type, std::remove_reference_t<W>> && !std::is_same_v<std::remove_reference_t<W>, Type>;

	public:
		Type(void)
		{
		}

		Type(Type &other) :
			Writable(other)
		{
		}
		Type(Type&&) = default;

		template <typename W, class = std::enable_if_t<is_w_ok_v<W> && std::is_rvalue_reference_v<W&&>>>
		Type(W &&sub) :
			Writable(std::move(sub))
		{
		}

		template <typename W, class = std::enable_if_t<is_w_ok_v<W>>>
		Type(W &sub) :
			Writable(sub)
		{
		}

		Type(const std::string &str);
		Type(const Primitive::Named &prim) :
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

	class PrependKeyword : public Type
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

	class Const : public PrependKeyword
	{
	public:
		template <typename T>
		Const(T &&type) :
			PrependKeyword(std::forward<T>(type), "const")
		{
		}
	};

	class Volatile : public PrependKeyword
	{
	public:
		template <typename T>
		Volatile(T &&type) :
			PrependKeyword(std::forward<T>(type), "volatile")
		{
		}
	};

	class Typename : public PrependKeyword
	{
	public:
		template <typename T>
		Typename(T &&type) :
			PrependKeyword(std::forward<T>(type), "typename")
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

	class Type::Modifiers::Array : public Type
	{
	public:
		template <typename T>
		Array(T &&type) :
			Type(std::forward<T>(type))
		{
		}

		void write(std::ostream &o) const override
		{
			write_sub(o);
			o << "[]";
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

	template <typename ...Args>
	inline Type::Modifiers::Array Type::Array(Args &&...args)
	{
		return Modifiers::Array(toString(), std::forward<Args>(args)...);
	}

	class Class : public Collection, public Type
	{
		using Type::write;

	public:
		enum class Visibility {
			Public,
			Protected,
			Private
		};

		Class(const std::string &name, Visibility base_visibility = Visibility::Public) :
			Collection(name),
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
		using Collection::add;

	public:
		template <class PrimitiveType, typename ...Args>
		PrimitiveType& add(Args &&...args)
		{
			return Collection::add<Memberize<PrimitiveType>>(m_visibility, std::forward<Args>(args)...);
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

	class Using : public Primitive::Named, public Type
	{
		using Type::write;

	public:
		template <typename T>
		Using(const std::string &name, T &&type) :
			Primitive::Named(name),
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

	class Variable : public Primitive::Named
	{
	public:
		template <typename T>
		Variable(T &&type, const std::string &name) :
			Primitive::Named(name),
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

	class Statement : public Writable
	{
		class String;

		template <typename W>
		static inline constexpr bool is_w_ok_v = std::is_base_of_v<Statement, std::remove_reference_t<W>> && !std::is_same_v<std::remove_reference_t<W>, Statement>;

	public:
		Statement(void)
		{
		}

		Statement(Statement &other) :
			Writable(other)
		{
		}
		Statement(Statement&&) = default;

		template <typename W, class = std::enable_if_t<is_w_ok_v<W> && std::is_rvalue_reference_v<W&&>>>
		Statement(W &&sub) :
			Writable(std::move(sub))
		{
		}

		template <typename W, class = std::enable_if_t<is_w_ok_v<W>>>
		Statement(W &sub) :
			Writable(sub)
		{
		}

		Statement(const std::string &str);
		Statement(const char str[]);
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

		CppGenerator::Inc operator++(void);
		CppGenerator::Dec operator--(void);
		CppGenerator::Plus operator+(void);
		CppGenerator::Minus operator-(void);
		CppGenerator::Not operator!(void);
		CppGenerator::NotBin operator~(void);
		CppGenerator::Deref operator*(void);
		CppGenerator::Address operator&(void);

		template <typename S>
		CppGenerator::Add operator+(S &&smt);
		template <typename S>
		CppGenerator::Sub operator-(S &&smt);
		template <typename S>
		CppGenerator::Mul operator*(S &&smt);
		template <typename S>
		CppGenerator::Div operator/(S &&smt);
		template <typename S>
		CppGenerator::Rem operator%(S &&smt);
		template <typename S>
		CppGenerator::LShift operator<<(S &&smt);
		template <typename S>
		CppGenerator::RShift operator>>(S &&smt);
		template <typename S>
		CppGenerator::Less operator<(S &&smt);
		template <typename S>
		CppGenerator::LessEq operator<=(S &&smt);
		template <typename S>
		CppGenerator::Greater operator>(S &&smt);
		template <typename S>
		CppGenerator::GreaterEq operator>=(S &&smt);
		template <typename S>
		CppGenerator::Eq operator==(S &&smt);
		template <typename S>
		CppGenerator::Dif operator!=(S &&smt);
		template <typename S>
		CppGenerator::AndBin operator&(S &&smt);
		template <typename S>
		CppGenerator::XorBin operator^(S &&smt);
		template <typename S>
		CppGenerator::OrBin operator|(S &&smt);
		template <typename S>
		CppGenerator::And operator&&(S &&smt);
		template <typename S>
		CppGenerator::Or operator||(S &&smt);
		template <typename S>
		CppGenerator::Assign operator=(S &&smt);
		template <typename S>
		CppGenerator::AssignAdd operator+=(S &&smt);
		template <typename S>
		CppGenerator::AssignSub operator-=(S &&smt);
		template <typename S>
		CppGenerator::AssignMul operator*=(S &&smt);
		template <typename S>
		CppGenerator::AssignDiv operator/=(S &&smt);
		template <typename S>
		CppGenerator::AssignRem operator%=(S &&smt);
		template <typename S>
		CppGenerator::AssignLShift operator<<=(S &&smt);
		template <typename S>
		CppGenerator::AssignRShift operator>>=(S &&smt);
		template <typename S>
		CppGenerator::AssignAndBin operator&=(S &&smt);
		template <typename S>
		CppGenerator::AssignXorBin operator^=(S &&smt);
		template <typename S>
		CppGenerator::AssignOrBin operator|=(S &&smt);

	private:
		template <typename First, typename ...Args>
		static void vectorizeArgsFirst(std::vector<Statement> &res, First &&first, Args &&...args)
		{
			res.emplace_back(std::forward<First>(first));
			if constexpr (!util::are_args_empty_v<Args...>)
				vectorizeArgsFirst(res, std::forward<Args>(args)...);
		}

	protected:
		template <typename ...Args>
		static std::vector<Statement> vectorizeArgs(Args &&...args)
		{
			std::vector<Statement> res;

			if constexpr (!util::are_args_empty_v<Args...>)
				vectorizeArgsFirst(res, std::forward<Args>(args)...);
			return res;
		}

		String toString(void) const;

	private:
		void writeChar(std::ostream &o, char c)
		{
			if (c >= 32 && c < 127)
				o << c;
			else
				o << "\\x" << std::hex << static_cast<size_t>(static_cast<uint8_t>(c));
		}

		std::string stringLitteral(const std::string &src)
		{
			std::stringstream ss;

			ss << "\"";
			for (auto &c : src)
				writeChar(ss, c);
			ss << "\"";
			return ss.str();
		}

		std::string boolLitteral(bool b)
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

		std::string floatLitteral(float f)
		{
			std::stringstream ss;

			ss << convertFloat(f) << "f";
			return ss.str();
		}

		std::string doubleLitteral(double f)
		{
			std::stringstream ss;

			ss << convertFloat(f);
			return ss.str();
		}

		std::string longDoubleLitteral(long double f)
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

		std::string unsignedCharLitteral(unsigned char u)
		{
			return convSingleChar(u);
		}

		std::string unsignedShortLitteral(unsigned short u)
		{
			return dummyConv(static_cast<max_unsigned>(u));
		}

		std::string unsignedIntLitteral(unsigned int u)
		{
			return dummyConv(static_cast<max_unsigned>(u), "U");
		}

		std::string unsignedLongLitteral(unsigned long u)
		{
			return dummyConv(static_cast<max_unsigned>(u), "UL");
		}

		std::string unsignedLongLongLitteral(unsigned long long u)
		{
			return dummyConv(static_cast<max_unsigned>(u), "ULL");
		}

		std::string charLitteral(char i)
		{
			return convSingleChar(i);
		}

		std::string shortLitteral(short i)
		{
			return dummyConv(static_cast<max_signed>(i));
		}

		std::string intLitteral(int i)
		{
			return dummyConv(static_cast<max_signed>(i));
		}

		std::string longLitteral(long i)
		{
			return dummyConv(static_cast<max_signed>(i), "L");
		}

		std::string longLongLitteral(long long i)
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
		Statement(String(stringLitteral(str)))
	{
	}

	inline Statement::Statement(const char str[]) :
		Statement(String(stringLitteral(str)))
	{
	}

	inline Statement::Statement(bool b) :
		Statement(String(boolLitteral(b)))
	{
	}

	inline Statement::Statement(float f) :
		Statement(String(floatLitteral(f)))
	{
	}

	inline Statement::Statement(double f) :
		Statement(String(doubleLitteral(f)))
	{
	}

	inline Statement::Statement(long double f) :
		Statement(String(longDoubleLitteral(f)))
	{
	}

	inline Statement::Statement(unsigned char u) :
		Statement(String(unsignedCharLitteral(u)))
	{
	}

	inline Statement::Statement(unsigned short u) :
		Statement(String(unsignedShortLitteral(u)))
	{
	}

	inline Statement::Statement(unsigned int u) :
		Statement(String(unsignedIntLitteral(u)))
	{
	}

	inline Statement::Statement(unsigned long u) :
		Statement(String(unsignedLongLitteral(u)))
	{
	}


	inline Statement::Statement(unsigned long long u) :
		Statement(String(unsignedLongLongLitteral(u)))
	{
	}

	inline Statement::Statement(char i) :
		Statement(String(charLitteral(i)))
	{
	}

	inline Statement::Statement(short i) :
		Statement(String(shortLitteral(i)))
	{
	}

	inline Statement::Statement(int i) :
		Statement(String(intLitteral(i)))
	{
	}

	inline Statement::Statement(long i) :
		Statement(String(longLitteral(i)))
	{
	}

	inline Statement::Statement(long long i) :
		Statement(String(longLongLitteral(i)))
	{
	}

	inline Statement::String Statement::toString(void) const
	{
		return Statement::String(Writable::toString());
	}

	class UnaryOp : public Smt
	{
	public:
		template <typename T>
		UnaryOp(T &&smt, const char *op) :
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

	class Inc : public UnaryOp
	{
	public:
		template <typename T>
		Inc(T &&smt) :
			UnaryOp(std::forward<T>(smt), "++") {}
	};

	class Dec : public UnaryOp
	{
	public:
		template <typename T>
		Dec(T &&smt) :
			UnaryOp(std::forward<T>(smt), "--") {}
	};

	class Plus : public UnaryOp
	{
	public:
		template <typename T>
		Plus(T &&smt) :
			UnaryOp(std::forward<T>(smt), "+") {}
	};

	class Minus : public UnaryOp
	{
	public:
		template <typename T>
		Minus(T &&smt) :
			UnaryOp(std::forward<T>(smt), "-") {}
	};

	class Not : public UnaryOp
	{
	public:
		template <typename T>
		Not(T &&smt) :
			UnaryOp(std::forward<T>(smt), "!") {}
	};

	class NotBin : public UnaryOp
	{
	public:
		template <typename T>
		NotBin(T &&smt) :
			UnaryOp(std::forward<T>(smt), "~") {}
	};

	class Deref : public UnaryOp
	{
	public:
		template <typename T>
		Deref(T &&smt) :
			UnaryOp(std::forward<T>(smt), "*") {}
	};

	class Address : public UnaryOp
	{
	public:
		template <typename T>
		Address(T &&smt) :
			UnaryOp(std::forward<T>(smt), "&") {}
	};

	CppGenerator::Inc Smt::operator++(void)
	{
		return CppGenerator::Inc(toString());
	}

	CppGenerator::Dec Smt::operator--(void)
	{
		return CppGenerator::Dec(toString());
	}

	CppGenerator::Plus Smt::operator+(void)
	{
		return CppGenerator::Plus(toString());
	}

	CppGenerator::Minus Smt::operator-(void)
	{
		return CppGenerator::Minus(toString());
	}

	CppGenerator::Not Smt::operator!(void)
	{
		return CppGenerator::Not(toString());
	}

	CppGenerator::NotBin Smt::operator~(void)
	{
		return CppGenerator::NotBin(toString());
	}

	CppGenerator::Deref Smt::operator*(void)
	{
		return CppGenerator::Deref(toString());
	}

	CppGenerator::Address Smt::operator&(void)
	{
		return CppGenerator::Address(toString());
	}

	class Cast : public Smt
	{
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

	private:
		Type m_type;
		Smt m_smt;
	};

	class CppCast : public Smt
	{
	public:
		template <typename T, typename S>
		CppCast(const char *cast_type, T &&type, S &&smt) :
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

	class StaticCast : public CppCast
	{
	public:
		template <typename ...Args>
		StaticCast(Args &&...args) :
			CppCast("static_cast", std::forward<Args>(args)...) {}
	};

	class DynamicCast : public CppCast
	{
	public:
		template <typename ...Args>
		DynamicCast(Args &&...args) :
			CppCast("dynamic_cast", std::forward<Args>(args)...) {}
	};

	class ConstCast : public CppCast
	{
	public:
		template <typename ...Args>
		ConstCast(Args &&...args) :
			CppCast("const_cast", std::forward<Args>(args)...) {}
	};

	class ReinterpretCast : public CppCast
	{
	public:
		template <typename ...Args>
		ReinterpretCast(Args &&...args) :
			CppCast("reinterpret_cast", std::forward<Args>(args)...) {}
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

	class AssociativeOp : public Smt
	{
	public:
		template <typename Ta, typename Tb, typename ...Supp>
		AssociativeOp(const char *op, Ta &&a, Tb &&b, Supp &&...supp) :
			m_op(op),
			m_args(vectorizeArgs(std::forward<Ta>(a), std::forward<Tb>(b), std::forward<Supp>(supp)...))
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

	class Add : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Add(Args &&...args) :
			AssociativeOp("+", std::forward<Args>(args)...) {}
	};

	class Sub : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Sub(Args &&...args) :
			AssociativeOp("-", std::forward<Args>(args)...) {}
	};

	class Mul : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Mul(Args &&...args) :
			AssociativeOp("*", std::forward<Args>(args)...) {}
	};

	class Div : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Div(Args &&...args) :
			AssociativeOp("/", std::forward<Args>(args)...) {}
	};

	class Rem : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Rem(Args &&...args) :
			AssociativeOp("%", std::forward<Args>(args)...) {}
	};

	class LShift : public AssociativeOp
	{
	public:
		template <typename ...Args>
		LShift(Args &&...args) :
			AssociativeOp("<<", std::forward<Args>(args)...) {}
	};

	class RShift : public AssociativeOp
	{
	public:
		template <typename ...Args>
		RShift(Args &&...args) :
			AssociativeOp(">>", std::forward<Args>(args)...) {}
	};

	class Less : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Less(Args &&...args) :
			AssociativeOp("<", std::forward<Args>(args)...) {}
	};

	class LessEq : public AssociativeOp
	{
	public:
		template <typename ...Args>
		LessEq(Args &&...args) :
			AssociativeOp("<=", std::forward<Args>(args)...) {}
	};

	class Greater : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Greater(Args &&...args) :
			AssociativeOp(">", std::forward<Args>(args)...) {}
	};

	class GreaterEq : public AssociativeOp
	{
	public:
		template <typename ...Args>
		GreaterEq(Args &&...args) :
			AssociativeOp(">=", std::forward<Args>(args)...) {}
	};

	class Eq : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Eq(Args &&...args) :
			AssociativeOp("==", std::forward<Args>(args)...) {}
	};

	class Dif : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Dif(Args &&...args) :
			AssociativeOp("!=", std::forward<Args>(args)...) {}
	};

	class AndBin : public AssociativeOp
	{
	public:
		template <typename ...Args>
		AndBin(Args &&...args) :
			AssociativeOp("&", std::forward<Args>(args)...) {}
	};

	class XorBin : public AssociativeOp
	{
	public:
		template <typename ...Args>
		XorBin(Args &&...args) :
			AssociativeOp("^", std::forward<Args>(args)...) {}
	};

	class OrBin : public AssociativeOp
	{
	public:
		template <typename ...Args>
		OrBin(Args &&...args) :
			AssociativeOp("||", std::forward<Args>(args)...) {}
	};

	class And : public AssociativeOp
	{
	public:
		template <typename ...Args>
		And(Args &&...args) :
			AssociativeOp("&&", std::forward<Args>(args)...) {}
	};

	class Or : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Or(Args &&...args) :
			AssociativeOp("||", std::forward<Args>(args)...) {}
	};

	class Assign : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Assign(Args &&...args) :
			AssociativeOp("=", std::forward<Args>(args)...) {}
	};

	class AssignAdd : public AssociativeOp
	{
	public:
		template <typename ...Args>
		AssignAdd(Args &&...args) :
			AssociativeOp("+=", std::forward<Args>(args)...) {}
	};

	class AssignSub : public AssociativeOp
	{
	public:
		template <typename ...Args>
		AssignSub(Args &&...args) :
			AssociativeOp("-=", std::forward<Args>(args)...) {}
	};

	class AssignMul : public AssociativeOp
	{
	public:
		template <typename ...Args>
		AssignMul(Args &&...args) :
			AssociativeOp("*=", std::forward<Args>(args)...) {}
	};

	class AssignDiv : public AssociativeOp
	{
	public:
		template <typename ...Args>
		AssignDiv(Args &&...args) :
			AssociativeOp("/=", std::forward<Args>(args)...) {}
	};

	class AssignRem : public AssociativeOp
	{
	public:
		template <typename ...Args>
		AssignRem(Args &&...args) :
			AssociativeOp("%=", std::forward<Args>(args)...) {}
	};

	class AssignLShift : public AssociativeOp
	{
	public:
		template <typename ...Args>
		AssignLShift(Args &&...args) :
			AssociativeOp("<<=", std::forward<Args>(args)...) {}
	};

	class AssignRShift : public AssociativeOp
	{
	public:
		template <typename ...Args>
		AssignRShift(Args &&...args) :
			AssociativeOp(">>=", std::forward<Args>(args)...) {}
	};

	class AssignAndBin : public AssociativeOp
	{
	public:
		template <typename ...Args>
		AssignAndBin(Args &&...args) :
			AssociativeOp("&=", std::forward<Args>(args)...) {}
	};

	class AssignXorBin : public AssociativeOp
	{
	public:
		template <typename ...Args>
		AssignXorBin(Args &&...args) :
			AssociativeOp("^=", std::forward<Args>(args)...) {}
	};

	class AssignOrBin : public AssociativeOp
	{
	public:
		template <typename ...Args>
		AssignOrBin(Args &&...args) :
			AssociativeOp("|=", std::forward<Args>(args)...) {}
	};

	template <typename S>
	CppGenerator::Add Smt::operator+(S &&smt)
	{
		return CppGenerator::Add(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Sub Smt::operator-(S &&smt)
	{
		return CppGenerator::Sub(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Mul Smt::operator*(S &&smt)
	{
		return CppGenerator::Mul(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Div Smt::operator/(S &&smt)
	{
		return CppGenerator::Div(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Rem Smt::operator%(S &&smt)
	{
		return CppGenerator::Rem(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::LShift Smt::operator<<(S &&smt)
	{
		return CppGenerator::LShift(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::RShift Smt::operator>>(S &&smt)
	{
		return CppGenerator::RShift(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Less Smt::operator<(S &&smt)
	{
		return CppGenerator::Less(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::LessEq Smt::operator<=(S &&smt)
	{
		return CppGenerator::LessEq(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Greater Smt::operator>(S &&smt)
	{
		return CppGenerator::Greater(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::GreaterEq Smt::operator>=(S &&smt)
	{
		return CppGenerator::GreaterEq(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Eq Smt::operator==(S &&smt)
	{
		return CppGenerator::Eq(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Dif Smt::operator!=(S &&smt)
	{
		return CppGenerator::Dif(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::AndBin Smt::operator&(S &&smt)
	{
		return CppGenerator::AndBin(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::XorBin Smt::operator^(S &&smt)
	{
		return CppGenerator::XorBin(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::OrBin Smt::operator|(S &&smt)
	{
		return CppGenerator::OrBin(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::And Smt::operator&&(S &&smt)
	{
		return CppGenerator::And(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Or Smt::operator||(S &&smt)
	{
		return CppGenerator::Or(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::Assign Smt::operator=(S &&smt)
	{
		return CppGenerator::Assign(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::AssignAdd Smt::operator+=(S &&smt)
	{
		return CppGenerator::AssignAdd(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::AssignSub Smt::operator-=(S &&smt)
	{
		return CppGenerator::AssignSub(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::AssignMul Smt::operator*=(S &&smt)
	{
		return CppGenerator::AssignMul(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::AssignDiv Smt::operator/=(S &&smt)
	{
		return CppGenerator::AssignDiv(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::AssignRem Smt::operator%=(S &&smt)
	{
		return CppGenerator::AssignRem(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::AssignLShift Smt::operator<<=(S &&smt)
	{
		return CppGenerator::AssignLShift(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::AssignRShift Smt::operator>>=(S &&smt)
	{
		return CppGenerator::AssignRShift(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::AssignAndBin Smt::operator&=(S &&smt)
	{
		return CppGenerator::AssignAndBin(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::AssignXorBin Smt::operator^=(S &&smt)
	{
		return CppGenerator::AssignXorBin(toString(), std::forward<S>(smt));
	}

	template <typename S>
	CppGenerator::AssignOrBin Smt::operator|=(S &&smt)
	{
		return CppGenerator::AssignOrBin(toString(), std::forward<S>(smt));
	}

	class Comma : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Comma(Args &&...args) :
			AssociativeOp(",", std::forward<Args>(args)...) {}
	};

	class PostfixUnaryOp : public Smt
	{
	public:
		template <typename T>
		PostfixUnaryOp(T &&smt, const char *op) :
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

	class Smt::Modifiers::Inc : public PostfixUnaryOp
	{
	public:
		template <typename T>
		Inc(T &&smt) :
			PostfixUnaryOp(std::forward<T>(smt), "++") {}
	};

	class Smt::Modifiers::Dec : public PostfixUnaryOp
	{
	public:
		template <typename T>
		Dec(T &&smt) :
			PostfixUnaryOp(std::forward<T>(smt), "--") {}
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
			m_args(vectorizeArgs(std::forward<Args>(args)...))
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
			m_subscript(vectorizeArgs(std::forward<S>(subscript), std::forward<Ss>(additional_subscript)...))
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

	class Smt::Modifiers::Member : public AssociativeOp
	{
	public:
		template <typename ...Args>
		Member(Args &&...args) :
			AssociativeOp(".", std::forward<Args>(args)...) {}
	};

	template <typename ...Args>
	Smt::Modifiers::Member Smt::Member(Args &&...args)
	{
		return Modifiers::Member(toString(), std::forward<Args>(args)...);
	}

	class Smt::Modifiers::MemberPtr : public AssociativeOp
	{
	public:
		template <typename ...Args>
		MemberPtr(Args &&...args) :
			AssociativeOp("->", std::forward<Args>(args)...) {}
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
}

namespace cppgen = CppGenerator;