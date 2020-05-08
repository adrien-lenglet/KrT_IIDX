#pragma once

#include <vector>
#include <stack>
#include "Observer.hpp"
#include "Event/World/Socket.hpp"

namespace Subtile {

class SessionBase;
class World;
class WorldBase;

class Entity : protected Event::World::Socket
{
	friend SessionBase;
	class Context
	{
	public:
		Context(World *world, Entity *parent);
		~Context(void) = default;

	private:
		friend Entity;
		friend Entity;
		World *m_world;
		Entity *m_parent;

		template <typename EntType>
		World& getWorld(EntType &ent) const
		{
			if (m_world)
				return *m_world;
			else
				return static_cast<World&>(ent);
		}
		Entity* getParent(void) const;
	};

	static thread_local util::stack<Context> m_ctx;

public:
	Entity(void);
	virtual ~Entity(void) = 0;

protected:
	World &world;

	template <typename EntityType, class ...Args>
	EntityType& add(Args &&...args)
	{
		auto &res = m_ctx.emplace_frame(std::function([&]() -> auto& {
			return m_children.emplace<EntityType>(std::forward<Args>(args)...);
		}), &world, this);
		m_stack.pop();
		return res;
	}

	void destroy(void);

	template <typename ...PayloadTypes>
	class Event : public Subtile::Event::DescGen<Event<PayloadTypes...>>
	{
	public:
		Event(void) :
			m_owner(Entity::m_stack.top())
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

	static thread_local std::stack<std::reference_wrapper<Entity>> m_stack;

	Entity *m_parent;
	util::unique_set<Entity> m_children;

	Entity& getParent(void);
};

}

namespace sb = ::Subtile;

#include "World.hpp"