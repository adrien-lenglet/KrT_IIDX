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

	class Primitive::Named : public Primitive
	{
	public:
		Named(const std::string &name) :
			m_name(name)
		{
		}
		virtual ~Named(void)
		{
		}

		const std::string& getName(void) const
		{
			return m_name;
		}

	private:
		const std::string m_name;
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
			return m_primitives.emplace<PrimitiveType>(std::forward<Args>(args)...);
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
		}
		~Namespace(void) override
		{
		}

		static Namespace global(void)
		{
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

	class Type
	{
	public:
		virtual ~Type(void) = default;

		virtual void write(std::ostream&) const = 0;
	};

	class Class : public Collection, public Type
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
			return add<Memberize<PrimitiveType>>(m_visibility, std::forward<Args>(args)...);
		}

		void setVisibility(Visibility visiblity)
		{
			m_visibility = visiblity;
		}

		void write(std::ostream&) const override
		{
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

	class Variable : public Primitive::Named
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
	};
}

namespace cppgen = CppGenerator;