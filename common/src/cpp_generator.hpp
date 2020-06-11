#pragma once

#include <iostream>
#include <sstream>
#include "util.hpp"

namespace CppGenerator {
	class Primitive
	{
	public:
		virtual ~Primitive(void) = default;

		virtual void write(std::ostream &decl, std::ostream &impl) const = 0;

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
		const util::unique_set<Primitive>& getPrimitives(void) const
		{
			return m_primitives;
		}

	private:
		util::unique_set<Primitive> m_primitives;
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

		void write(std::ostream &decl, std::ostream &impl) const override
		{
			auto isMain = getName() == "";

			if (!isMain) {
				writePrologue(decl);
				writePrologue(impl);
			}
			for (auto &p : getPrimitives())
				p.write(decl, impl);
			if (!isMain) {
				writeEpilogue(decl);
				writeEpilogue(impl);
			}
		}

		void output(const std::string &path, const std::string &basename)
		{
			auto filepath = path + std::string("/");
			auto basedecl = basename + std::string(".hpp");
			auto baseimpl = basename + std::string(".cpp");
			std::ofstream decl(filepath + basedecl, std::ios::binary | std::ios::trunc);
			std::ofstream impl(filepath + baseimpl, std::ios::binary | std::ios::trunc);

			decl << "#pragma once" << std::endl;
			impl << "#include \"" << basedecl << "\"" << std::endl;
			write(decl, impl);
		}

	private:
		void writePrologue(std::ostream &o) const
		{
			o << "namespace " << getName() << " {";
		}

		void writeEpilogue(std::ostream &o) const
		{
			o << "}";
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

	class Type : public Writable
	{
		class String;

		template <typename W>
		static inline constexpr bool is_w_ok_v = std::is_base_of_v<Type, std::remove_reference_t<W>> && !std::is_same_v<std::remove_reference_t<W>, Type>;

	public:
		Type(void)
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

		~Type(void) override
		{
		}

		void write(std::ostream &o) const override
		{
			write_sub(o);
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

	class Const : public Type
	{
	public:
		template <typename T>
		Const(T &&type) :
			Type(std::forward<T>(type))
		{
		}

		void write(std::ostream &o) const override
		{
			o << "const ";
			write_sub(o);
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

		void write(std::ostream &decl, std::ostream &) const
		{
			decl << "using " << getName() << " = ";
			m_type.write(decl);
			decl << ";";
		}

	private:
		const Type m_type;

	};

	class Class : public Collection
	{
	public:
		Class(const std::string &name) :
			Collection(name),
			m_visibility(Visibility::Public)
		{
		}
		~Class(void)
		{
		}

		enum class Visibility {
			Public,
			Protected,
			Private
		};

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

		template <class PrimitiveType, typename ...Args>
		PrimitiveType& add(Args &&...args)
		{
			return Collection::add<Memberize<PrimitiveType>>(m_visibility, std::forward<Args>(args)...);
		}

		void setVisibility(Visibility visiblity)
		{
			m_visibility = visiblity;
		}

		void write(std::ostream &decl, std::ostream &impl) const override
		{
			decl << getPrimType() << " " << getName() << "{";
			for (auto &p : getPrimitives()) {
				auto &mem = dynamic_cast<const Member&>(p);
				decl << VisibilityToStr(mem) << ": ";
				p.write(decl, impl);
			}
			decl << "};";
		}

	protected:
		virtual const std::string& getPrimType(void) const
		{
			static const std::string res("class");

			return res;
		}

	private:
		Visibility m_visibility;

		using Collection::add;
	};

	class Struct : public Class
	{
	public:
		Struct(const std::string &name) :
			Class(name)
		{
			setVisibility(Visibility::Public);
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