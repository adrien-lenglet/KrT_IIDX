#include <limits>
#include <ctime>
#include "World.hpp"

namespace Subtile {

World::World(void) :
	instance(getInstanceStack().top()),
	events(instance.m_events),
	m_rand_gen(std::time(nullptr))
{
}

World::~World(void)
{
	m_children.clear();
}

double World::urandf(void)
{
	return static_cast<double>(m_rand_gen()) / static_cast<double>(std::numeric_limits<decltype(m_rand_gen())>::max());
}

double World::srandf(void)
{
	return urandf() * 2.0 - 1.0;
}

util::stack<std::reference_wrapper<Instance>>& World::getInstanceStack(void)
{
	static thread_local util::stack<std::reference_wrapper<Instance>> res;

	return res;
}

}