#pragma once

#include <vector>
#include <stack>
#include "Observer.hpp"
#include "Event/World/Socket.hpp"

namespace Subtile {

class World;
class Entity;
class Instance;

class EntityImpl : protected Event::World::Socket
{
	friend Entity;
	friend Instance;
	class Context
	{
	public:
		Context(World *world, EntityImpl *parent);
		~Context(void) = default;

	private:
		friend Entity;
		friend EntityImpl;
		World *m_world;
		EntityImpl *m_parent;

		template <typename EntType>
		World& getWorld(EntType &ent) const
		{
			if (m_world)
				return *m_world;
			else
				return static_cast<World&>(ent);
		}
		EntityImpl* getParent(void) const;
	};

	static std::stack<Context> m_ctx;
	template <typename ...ArgsTypes>
	static void pushCtx(ArgsTypes &&...args)
	{
		m_ctx.emplace(std::forward<ArgsTypes>(args)...);
	}
	static Context popCtx(void);

public:
	EntityImpl(const Context &ctx);
	virtual ~EntityImpl(void) = 0;

protected:
	World &world;

	template <typename EntityType, class ...ArgsTypes>
	EntityType& add(ArgsTypes &&...args)
	{
		pushCtx(&world, this);
		auto to_add = new EntityType(std::forward<ArgsTypes>(args)...);

		m_children.emplace(to_add, to_add);
		return *to_add;
	}

	void destroy(void);

private:
	EntityImpl *m_parent;
	std::map<EntityImpl*, std::unique_ptr<EntityImpl>> m_children;

	EntityImpl& getParent(void);
};

class Entity : public EntityImpl
{
public:
	Entity(void);
	~Entity(void) = 0;

private:
	friend World;
	friend EntityImpl;
};

}

#include "World.hpp"