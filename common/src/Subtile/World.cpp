#include "World.hpp"

namespace Subtile {

World::World(Instance &engine) :
	m_engine(engine)
{
}

World::~World(void)
{
}

void World::resetRoot(void)
{
	m_root.reset(nullptr);
}

Event::World::Observer& World::getEvents(void)
{
	return m_engine.getEvents();
}

}