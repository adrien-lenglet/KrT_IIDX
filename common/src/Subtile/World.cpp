#include "World.hpp"

namespace Subtile {

World::World(void) :
	events(getSystems().top())
{
}

World::~World(void)
{
}

util::stack<std::reference_wrapper<Event::System::Observer>>& World::getSystems(void)
{
	static thread_local util::stack<std::reference_wrapper<Subtile::Event::System::Observer>> res;

	return res;
}

}