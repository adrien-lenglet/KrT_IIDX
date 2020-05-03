#include "World.hpp"

namespace Subtile {

WorldBase::WorldBase(Subtile::Event::System::Observer &system) :
	events(system)
{
}

WorldBase::~WorldBase(void)
{
}

thread_local util::stack<std::reference_wrapper<Subtile::Event::System::Observer>> World::m_systems;

World::World(void) :
	WorldBase(m_systems.top())
{
}

World::~World(void)
{
}

}