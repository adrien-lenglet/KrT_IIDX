#include "World.hpp"

namespace Subtile {

WorldBase::WorldBase(Instance &engine) :
	events(engine.getEvents()),
	m_engine(engine)
{
}

WorldBase::~WorldBase(void)
{
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

World::World(void) :
	WorldBase(popEngine())
{
}

World::~World(void)
{
}

}