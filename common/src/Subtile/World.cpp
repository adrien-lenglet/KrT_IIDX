#include <limits>
#include <ctime>
#include "World.hpp"
#include "Instance.hpp"

namespace Subtile {

WorldBase::WorldBase(void) :
	EntityBase(getCtx().top().getParent()),
	events(getInstanceStack().top().get().m_events),
	m_rand_gen(std::time(nullptr))
{
}

WorldBase::~WorldBase(void)
{
	m_children.clear();
}

double WorldBase::urandf(void)
{
	return static_cast<double>(m_rand_gen()) / static_cast<double>(std::numeric_limits<decltype(m_rand_gen())>::max());
}

double WorldBase::srandf(void)
{
	return urandf() * 2.0 - 1.0;
}

util::stack<std::reference_wrapper<InstanceBase>>& WorldBase::getInstanceStack(void)
{
	static thread_local util::stack<std::reference_wrapper<InstanceBase>> res;

	return res;
}

}