#pragma once

#include <vector>
#include <memory>

namespace Subtile {

class World;

class Entity
{
public:
	Entity(World &world);
	virtual ~Entity(void);

protected:
	World& getWorld(void);

	template <typename EntityType, class ...ArgType>
	void add(ArgType &&...args)
	{
		m_children.emplace_back(new EntityType(m_world, std::forward(args)...));
	}

	void destroy(void);

private:
	World &m_world;
	std::vector<std::unique_ptr<Entity>> m_children;
};

}

#include "World.hpp"