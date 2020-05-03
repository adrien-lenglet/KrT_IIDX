#pragma once

#include "Entity.hpp"

namespace Subtile {

class World;

class WorldBase : public Entity
{
public:
	WorldBase(Instance &engine);
	~WorldBase(void) = 0;

	Subtile::Event::World::Observer &events;

private:
	friend World;
	friend Entity;
	friend EntityBase;

	Instance &m_engine;
};

class World : public WorldBase
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