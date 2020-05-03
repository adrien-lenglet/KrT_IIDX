#include "World.hpp"

namespace Subtile {

WorldBase::WorldBase(Subtile::Event::System::Observer &system) :
	events(system)
{
}

WorldBase::~WorldBase(void)
{
}

std::stack<std::reference_wrapper<Subtile::Event::System::Observer>> World::m_systems;
void World::pushEngine(Subtile::Event::System::Observer &system)
{
	m_systems.emplace(system);
}

Subtile::Event::System::Observer& World::popEngine(void)
{
	if (m_systems.size() == 0)
		throw std::runtime_error("No context for world creation");

	auto res = std::move(m_systems.top());

	m_systems.pop();
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