#pragma once

#include "Entity.hpp"

namespace Subtile {

class World;

class WorldImpl : public Entity
{
public:
	WorldImpl(Instance &engine);
	~WorldImpl(void) = 0;

private:
	friend World;
	friend Entity;
	friend EntityImpl;

	Instance &m_engine;

	Subtile::Event::World::Observer& getEvents(void);
};

class World : public WorldImpl
{
public:
	World(void);
	~World(void) = 0;

private:
	friend Instance;

	static std::stack<std::reference_wrapper<Instance>> m_engines;
	static void pushEngine(Instance &engine);
	static Instance& popEngine(void);
};

}

#include "Instance.hpp"