#include "World.hpp"

namespace Subtile {

World::World(void) :
	Entity(&popEngine().getEvents()),
	m_engine(popEngine())
{
}

World::~World(void)
{
}

Event::World::Observer& World::getEvents(void)
{
	return m_engine.getEvents();
}

std::stack<std::reference_wrapper<Instance>> World::m_engines;
void World::pushEngine(Instance &engine)
{
	m_engines.emplace(engine);
}

Instance& World::popEngine(void)
{
	if (m_engines.size() == 0)
		throw std::runtime_error("No context for world creation");

	auto res = std::move(m_engines.top());

	m_engines.pop();
	return res;
}

}