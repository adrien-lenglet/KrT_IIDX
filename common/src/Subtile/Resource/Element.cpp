#include "Element.hpp"

namespace Subtile {
namespace Resource {

std::stack<Element::Context>& Element::getStack(void)
{
	static thread_local std::stack<Element::Context> res;

	return res;
}

Element::Element(void) :
	Element(getStack().top())
{
}

Element::Element(const Element::Context &ctx) :
	m_parent(ctx.parent),
	m_name(ctx.name)
{
}

Element::~Element(void)
{
}

Folder& Element::getParent(void)
{
	return *m_parent;
}

std::string Element::getPath(void) const
{
	if (m_parent)
		return mergePaths(m_parent->getPath(), m_name);
	else
		return m_name;
}

std::string Element::mergePaths(const std::string &a, const std::string &b)
{
	static const std::string sep("/");

	return a + sep + b;
}

}
}

#include "Folder.hpp"