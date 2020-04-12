#pragma once

#include "Instance.hpp"
#include "Entity.hpp"

namespace Subtile {

class World
{
public:
	World(Instance &engine);
	~World(void);

	template <typename EntityType, class ...ArgsTypes>
	void set(const ArgsTypes &...args)
	{
		m_root.reset(new EntityType(Entity::Context(*this, nullptr), args...));
	}

private:
	friend Entity;

	Instance &m_engine;
	std::unique_ptr<Entity> m_root;

	void resetRoot(void);
	Event::World::Observer& getEvents(void);
};

}