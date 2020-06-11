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

	private:
		std::unique_ptr<HolderType> m_sub;
	};

	class LRef;
	class RRef;
	class Ptr;

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

		CppGenerator::LRef LRef(void);
		CppGenerator::RRef RRef(void);
		CppGenerator::Ptr Ptr(void);

	protected:
		operator std::string(void) const
		{
			std::stringstream ss;

			write(ss);
			return ss.str();
		}
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
		PrependKeyword(const char *str, T &&type) :
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
			PrependKeyword("const", std::forward<T>(type))
		{
		}
	};

	class Volatile : public PrependKeyword
	{
	public:
		template <typename T>
		Volatile(T &&type) :
			PrependKeyword("volatile", std::forward<T>(type))
		{
		}
	};

	class Typename : public PrependKeyword
	{
	public:
		template <typename T>
		Typename(T &&type) :
			PrependKeyword("typename", std::forward<T>(type))
		{
		}
	};

	class LRef : public Type
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

	class RRef : public Type
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

	class Ptr : public Type
	{
	public:
		template <typename T>
		Ptr(T &&type) :
			Type(std::forward<T>(type))
		{
		}

		void write(std::ostream &o) const override
		{
			write_sub(o);
			o << "*";
		}
	};

	inline LRef Type::LRef(void)
	{
		return CppGenerator::LRef(static_cast<std::string>(*this));
	}

	inline RRef Type::RRef(void)
	{
		return CppGenerator::RRef(static_cast<std::string>(*this));
	}

	inline Ptr Type::Ptr(void)
	{
		return CppGenerator::Ptr(static_cast<std::string>(*this));
	}

	class Using : public Primitive::Named
	{
	public:
		template <typename T>
		Using(const std::string &name, T &&type) :
			Primitive::Named(name),
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

	class Class : public Collection
	{
	public:
		enum class Visibility {
			Public,
			Protected,
			Private
		};

		Class(const std::string &name, Visibility base_visibility = Visibility::Public) :
			Collection(name),
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
					is_first = false;
					cur_vis = vis;
				}

				p.write(w);
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

	/*class Variable : public Primitive::Named
	{
	public:
		Variable(const Type &type, const std::string &name) :
			Primitive::Named(name),
			m_type(type)
		{
		}
		~Variable(void)
		{
		}

	private:
		const Type &m_type;
	};*/
}

namespace cppgen = CppGenerator;