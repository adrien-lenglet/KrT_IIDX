#pragma once

#include <vector>
#include "Observer.hpp"
#include "Event/World/Socket.hpp"

namespace Subtile {

class World;

class Entity : protected Event::World::Socket
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

	template <typename EntityType, class ...ArgsTypes>
	EntityType& add(ArgsTypes &&...args)
	{
		auto to_add = std::make_unique<EntityType>(Context(m_world, this), std::forward<ArgsTypes>(args)...);

		events.lifetime.add(*this, to_add);
		return *to_add;
	}

	void destroy(void);

private:
	World &m_world;
	Entity *m_parent;
	std::map<Subtile::Entity*, std::unique_ptr<Subtile::Entity>> m_children;

	Entity& getParent(void);
};

}

#include "World.hpp"