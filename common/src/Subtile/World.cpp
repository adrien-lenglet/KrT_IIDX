#include "World.hpp"

namespace Subtile {

World::World(void) :
	events(m_systems.top())
{
}

World::~World(void)
{
}

thread_local util::stack<std::reference_wrapper<Subtile::Event::System::Observer>> World::m_systems;

}