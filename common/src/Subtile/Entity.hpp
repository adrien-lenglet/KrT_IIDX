#pragma once

#include <vector>
#include <stack>
#include "Observer.hpp"
#include "Event/World/Socket.hpp"

namespace Subtile {

class World;
class WorldImpl;
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
	EntityImpl(const Context &ctx, Event::World::Observer *events = nullptr);
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
	Entity(Event::World::Observer *events = nullptr);
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
		Subtile::Event::Bindings<std::tuple<>, CallbackType> m_listeners;

		std::unique_ptr<Subtile::Event::Listener> listen(const std::tuple<> &, const CallbackType &callback)
		{
			return m_listeners.bind(std::tuple<>(), callback);
		}

		void trigger(const Subtile::Event::Socket &actionner, PayloadTypes &&...args)
		{
			if (&actionner != &m_owner)
				throw std::runtime_error("Not allowed to trigger this event");
			for (auto &p : m_listeners)
				for (auto &listener : p.second)
					listener(std::forward<PayloadTypes>(args)...);
		}
	};

private:
	friend WorldImpl;
	friend EntityImpl;
};

}

#include "World.hpp"