#pragma once

#include "Instance.hpp"
#include "Entity.hpp"

namespace Subtile {

class World
{
public:
	World(Instance &engine);
	~World(void);

	template <typename EntityType, class ...ArgType>
	void set(ArgType &&...args)
	{
		m_root.reset(new EntityType(Entity::Context(*this, nullptr), std::forward(args)...));
	}

private:
	Instance &m_engine;
	std::unique_ptr<Entity> m_root;
};

}