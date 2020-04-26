#pragma once

#include "Entity.hpp"

namespace Subtile {

class World : public Entity
{
public:
	World(void);
	~World(void) = 0;

private:
	friend Instance;
	friend Entity;
	friend EntityImpl;

	Instance &m_engine;

	Event::World::Observer& getEvents(void);

	static std::stack<std::reference_wrapper<Instance>> m_engines;
	static void pushEngine(Instance &engine);
	static Instance& popEngine(void);
};

}

#include "Instance.hpp"