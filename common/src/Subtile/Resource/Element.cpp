#include <filesystem>
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
	m_name(ctx.name),
	m_id(computeId())
{
}

Element::~Element(void)
{
}

Folder& Element::getParent(void)
{
	return *m_parent;
}

const std::string& Element::getName(void)
{
	return m_name;
}

const std::string& Element::getId(void)
{
	return m_id;
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

std::string Element::computeId(void) const
{
	auto path = std::filesystem::path(m_name);

	return path.stem().string();
}

}
}

#include "Folder.hpp"