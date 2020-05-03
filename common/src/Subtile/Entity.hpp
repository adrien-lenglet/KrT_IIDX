#pragma once

#include <vector>
#include <stack>
#include "Observer.hpp"
#include "Event/World/Socket.hpp"

namespace Subtile {

class World;
class WorldBase;
class Entity;
class Instance;

class EntityBase : protected Event::World::Socket
{
	friend Entity;
	friend Instance;
	class Context
	{
	public:
		Context(World *world, EntityBase *parent);
		~Context(void) = default;

	private:
		friend Entity;
		friend EntityBase;
		World *m_world;
		EntityBase *m_parent;

		template <typename EntType>
		World& getWorld(EntType &ent) const
		{
			if (m_world)
				return *m_world;
			else
				return static_cast<World&>(ent);
		}
		EntityBase* getParent(void) const;
	};

	static std::stack<Context> m_ctx;
	template <typename ...ArgsTypes>
	static void pushCtx(ArgsTypes &&...args)
	{
		m_ctx.emplace(std::forward<ArgsTypes>(args)...);
	}
	static Context popCtx(void);

public:
	EntityBase(const Context &ctx);
	virtual ~EntityBase(void) = 0;

protected:
	World &world;

	template <typename EntityType, class ...Args>
	EntityType& add(Args &&...args)
	{
		pushCtx(&world, this);
		return m_children.emplace<EntityType>(std::forward<Args>(args)...);
	}

	void destroy(void);

private:
	EntityBase *m_parent;
	util::unique_set<EntityBase> m_children;

	EntityBase& getParent(void);
};

class Entity : public EntityBase
{
public:
	Entity(void);
	~Entity(void) = 0;

	template <typename ...PayloadTypes>
	class Event : public Subtile::Event::DescGen<Event<PayloadTypes...>>
	{
	public:
		Event(const Subtile::Event::Socket &owner) :
			m_owner(owner)
		{
		}
		~Event(void)
		{
		}

	private:
		friend Subtile::Event::Socket;

		using CallbackType = std::function<void (PayloadTypes &&...args)>;
		const Subtile::Event::Socket &m_owner;
		Binding::Strong<CallbackType> m_listeners;

		void bind(Binding::Dependency::Socket &socket, const std::tuple<>&, const CallbackType &callback)
		{
			m_listeners.bind(socket, callback);
		}

		void trigger(const Subtile::Event::Socket &actionner, PayloadTypes &&...args)
		{
			if (&actionner != &m_owner)
				throw std::runtime_error("Not allowed to trigger this event");
			for (auto &listener : m_listeners)
				listener(std::forward<PayloadTypes>(args)...);
		}
	};

private:
	friend WorldBase;
	friend EntityBase;
};

}

#include "World.hpp"