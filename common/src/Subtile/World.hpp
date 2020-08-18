#pragma once

#include <random>
#include "Entity.hpp"
#include "Event/World/Observer.hpp"

namespace Subtile {

class SessionBase;
class InstanceBase;
namespace Render {
class Pass;
}

class WorldBase : public EntityBase
{
public:
	WorldBase(void);
	~WorldBase(void) = 0;

	Subtile::Event::World::Observer events;

	double urandf(void);
	double srandf(void);

protected:
	static util::stack<std::reference_wrapper<InstanceBase>>& getInstanceStack(void);

private:
	friend SessionBase;
	template <typename WorldType>
	friend class Entity;
	friend Render::Pass;

	std::mt19937_64 m_rand_gen;
};

template <typename InstanceType>
class World : public WorldBase
{
public:
	World(void) :
		instance(reinterpret_cast<InstanceType&>(getInstanceStack().top().get()))
	{
	}

	InstanceType &instance;

	template <class EntityType, typename ...Args>
	EntityType& add(Args &&...args)
	{
		auto &res = getCtx().emplace_frame(std::function([&]() -> auto& {
			return m_children.emplace<EntityType>(std::forward<Args>(args)...);
		}), this, this);
		getEntityStack().pop();
		//res.setAbsolute();
		return res;
	}
};

}

#include "Session.hpp"

namespace Subtile {
	template <typename WorldType, typename ...ArgsTypes>
	auto& SessionBase::add(ArgsTypes &&...args)
	{
		auto &res = WorldBase::getInstanceStack().emplace_frame(std::function([&]() -> auto& {
			return EntityBase::getCtx().emplace_frame(std::function([&]() -> auto& {
				return m_worlds.emplace<WorldType>(std::forward<ArgsTypes>(args)...);
			}), nullptr, nullptr);
		}), m_instance);
		EntityBase::getEntityStack().pop();
		return res;
	}
}

#include "Instance.hpp"