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

}
}

#include "Folder.hpp"