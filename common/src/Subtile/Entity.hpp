#pragma once

#include <map>
#include <memory>

namespace Subtile {

class World;

class Entity
{
public:
	class Context
	{
	public:
		~Context(void) = default;

	private:
		friend Entity;
		friend World;

		Context(World &world, Entity *parent);

		World &m_world;
		Entity *m_parent;

		World& getWorld(void) const;
		Entity* getParent(void) const;
	};

	Entity(const Entity::Context &ctx);
	virtual ~Entity(void);

protected:
	World& getWorld(void);

	template <typename EntityType, class ...ArgType>
	EntityType& add(ArgType &&...args)
	{
		auto added = new EntityType(Context(m_world, this), std::forward(args)...);

		m_children.emplace(added, added);
		return *added;
	}

	void destroy(void);

private:
	friend World;
	World &m_world;
	Entity *m_parent;
	std::map<Subtile::Entity*, std::unique_ptr<Subtile::Entity>> m_children;

	Entity& getParent(void);
	void destroyChild(Entity &entity);
};

}

#include "World.hpp"