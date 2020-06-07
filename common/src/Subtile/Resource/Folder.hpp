#pragma once

#include "Element.hpp"
#include "util.hpp"

namespace Subtile {
namespace Resource {

class Folder : public Element
{
public:
	Folder(void);
	~Folder(void) override;

protected:
	Folder(const std::string &name);	// root folder

	template <class ElementType, typename ...Args>
	auto& add(const std::string &name, Args &&...args)
	{
		auto &stack = getStack();

		stack.emplace(this, name);
		auto &res = m_children.emplace<ElementType>(std::forward<Args>(args)...);
		stack.pop();

		return res;
	}

private:
	util::unique_set<Element> m_children;
};

}
}