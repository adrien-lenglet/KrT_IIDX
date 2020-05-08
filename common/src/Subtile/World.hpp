#pragma once

#include "Entity.hpp"
#include "Event/World/Observer.hpp"

namespace Subtile {

class SessionBase;

class World : public Entity
{
public:
	World(void);
	~World(void) = 0;

	Subtile::Event::World::Observer events;

private:
	friend SessionBase;
	friend Entity;

	static thread_local util::stack<std::reference_wrapper<Subtile::Event::System::Observer>> m_systems;
};

}