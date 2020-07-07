#include "World.hpp"

namespace Subtile {

World::World(void) :
	instance(getInstanceStack().top()),
	events(instance.m_events)
{
}

World::~World(void)
{
	m_children.clear();
}

util::stack<std::reference_wrapper<Instance>>& World::getInstanceStack(void)
{
	static thread_local util::stack<std::reference_wrapper<Instance>> res;

	return res;
}

}