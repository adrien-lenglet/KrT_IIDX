#pragma once

#include "../Subtile.hpp"

#include <vector>
#include <stack>
#include "Observer.hpp"
#include "Event/World/Socket.hpp"
#include "Transform.hpp"
#include "Resource.hpp"

namespace Subtile {

class SessionBase;
class World;
namespace Resource {
class Shader;
}

template <typename WorldType>
class Entity;

class EntityBase : protected Event::World::Socket
{
	friend SessionBase;
	template <typename WorldType>
	friend class Entity;

	class Context
	{
	public:
		Context(World *world, EntityBase *parent);
		~Context(void) = default;

		template <class EntType>
		World& getWorld(EntType &ent) const
		{
			if (m_world)
				return *m_world;
			else
				return reinterpret_cast<World&>(ent);
		}
		EntityBase* getParent(void) const;

	private:
		friend EntityBase;
		friend EntityBase;
		World *m_world;
		EntityBase *m_parent;
	};

	static util::stack<Context>& getCtx(void);

	EntityBase(EntityBase *parent);

public:
	virtual ~EntityBase(void) = 0;

protected:
	void destroy_children(void);
	void destroy(void);

	template <typename ...PayloadTypes>
	class Event : public Subtile::Event::DescGen<Event<PayloadTypes...>>
	{
	public:
		Event(void) :
			m_owner(getEntityStack().top())
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
	friend World;

	static util::stack<std::reference_wrapper<EntityBase>>& getEntityStack(void);

	EntityBase *m_parent;
	util::unique_set<EntityBase> m_children;

	EntityBase& getParent(void);
};

template <typename WorldType>
class Entity : public EntityBase
{
	Entity(const EntityBase::Context &ctx) :
		EntityBase(ctx.getParent()),
		world(reinterpret_cast<WorldType&>(ctx.getWorld(*this)))
	{
	}

public:
	using world_type = WorldType;

	Entity(void) :
		Entity(getCtx().top())
	{
	}

protected:
	WorldType &world;

	template <class EntityType, typename ...Args>
	EntityType& add(Args &&...args)
	{
		static_assert(std::is_base_of_v<typename EntityType::world_type, world_type>, "Incompatible entity");

		auto &res = getCtx().emplace_frame(std::function([&]() -> auto& {
			return m_children.emplace<EntityType>(std::forward<Args>(args)...);
		}), &world, this);
		getEntityStack().pop();
		return res;
	}

	template <typename R>
	decltype(auto) load(R &&res)
	{
		return world.instance.load(std::forward<R>(res));
	}
};

}

#include "World.hpp"