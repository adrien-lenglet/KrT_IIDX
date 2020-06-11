#pragma once

#include <iostream>
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

		operator std::string(void) const
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
			Type(std::forward<T>(type)),
			m_str(str)
		{
		}

		void write(std::ostream &o) const override
		{
			o << m_str << " ";
			write_sub(o);
		}

	private:
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
		return Modifiers::LRef(static_cast<std::string>(*this));
	}

	inline Type::Modifiers::RRef Type::RRef(void)
	{
		return Modifiers::RRef(static_cast<std::string>(*this));
	}

	template <typename ...Args>
	Type::Modifiers::Ptr Type::Ptr(Args &&...args)
	{
		return Modifiers::Ptr(static_cast<std::string>(*this), std::forward<Args>(args)...);
	}

	inline Type::Modifiers::ConstAhead Type::Const(void)
	{
		return Modifiers::ConstAhead(static_cast<std::string>(*this));
	}

	template <typename ...Args>
	inline Type::Modifiers::Array Type::Array(Args &&...args)
	{
		return Modifiers::Array(static_cast<std::string>(*this), std::forward<Args>(args)...);
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

	private:
		template <typename First, typename ...Args>
		static void vectorizeArgsFirst(std::vector<Statement> &res, First &&first, Args &&...args)
		{
			res.emplace_back(first);
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
		Statement(static_cast<String&&>(String(str)))
	{
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
		return Modifiers::Inc(static_cast<std::string>(*this));
	}

	inline Smt::Modifiers::Dec Smt::Dec(void)
	{
		return Modifiers::Dec(static_cast<std::string>(*this));
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
		return Modifiers::Call(static_cast<std::string>(*this), std::forward<Args>(args)...);
	}

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
		return Modifiers::Array(static_cast<std::string>(*this), std::forward<Args>(args)...);
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
		return Modifiers::Member(static_cast<std::string>(*this), std::forward<Args>(args)...);
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
		return Modifiers::MemberPtr(static_cast<std::string>(*this), std::forward<Args>(args)...);
	}
}

namespace cppgen = CppGenerator;