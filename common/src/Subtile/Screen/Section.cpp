#include "Section.hpp"

namespace Subtile {
namespace Screen {

Section::TopBase::TopBase(void)
{
	m_stack.pop();
}

Section::TopBase::~TopBase(void)
{
}

Section::Section(void)
{
	if (m_stack.size() > 0)
		m_stack.top().get().m_children.emplace_back(*this);
	m_stack.emplace(*this);
}

Section::~Section(void)
{
}

void Section::onRender(void)
{
}

thread_local util::stack<std::reference_wrapper<Section>> Section::m_stack;

void Section::render(void)
{
	for (auto &c : util::reverse(m_children))
		c.get().render();
	onRender();
}

}
}