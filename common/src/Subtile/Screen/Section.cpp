#include "Section.hpp"

namespace Subtile {
namespace Screen {

Section::TopBase::TopBase(void)
{
	getStack().pop();
}

Section::TopBase::~TopBase(void)
{
}

Section::Section(void)
{
	if (getStack().size() > 0)
		getStack().top().get().m_children.emplace_back(*this);
	getStack().emplace(*this);
}

Section::~Section(void)
{
}

void Section::onRender(void)
{
}

util::stack<std::reference_wrapper<Section>>& Section::getStack(void)
{
	static thread_local util::stack<std::reference_wrapper<Section>> res;

	return res;
}

void Section::render(void)
{
	for (auto &c : util::reverse(m_children))
		c.get().render();
	onRender();
}

}
}