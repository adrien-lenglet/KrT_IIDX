#pragma once

#include <iostream>
#include <sstream>
#include "util.hpp"

namespace CppGenerator {
	class Primitive
	{
	public:
		Primitive(const std::string &name) :
			m_name(name)
		{
		}
		virtual ~Primitive(void)
		{
		}

		const std::string& getName(void) const
		{
			return m_name;
		}

		virtual void write(std::ostream &decl, std::ostream &impl) const = 0;
	
	private:
		const std::string m_name;
	};

	class Collection : public Primitive
	{
	public:
		Collection(const std::string &name) :
			Primitive(name)
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
}

namespace cppgen = CppGenerator;