#pragma once

#include "Entity.hpp"
#include "Event/World/Observer.hpp"

namespace Subtile {

class World;
class SessionBase;

class WorldBase : public Entity
{
public:
	WorldBase(Subtile::Event::System::Observer &engine);
	~WorldBase(void) = 0;

	Subtile::Event::World::Observer events;

private:
	friend World;
	friend Entity;
	friend EntityBase;
};

class World : public WorldBase
{
public:
	World(void);
	~World(void) = 0;

private:
	friend SessionBase;

	static thread_local util::stack<std::reference_wrapper<Subtile::Event::System::Observer>> m_systems;
};

}