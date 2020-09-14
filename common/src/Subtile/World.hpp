#pragma once

#include <random>
#include "Entity.hpp"
#include "Event/World/Observer.hpp"

namespace Subtile {

class InstanceBase;

class WorldBase : public EntityBase
{
public:
	WorldBase(void);
	~WorldBase(void) = 0;

	Subtile::Event::World::Observer events;

	double urandf(void);
	double srandf(void);

private:
	template <typename>
	friend class Entity;
	template <typename, typename>
	friend class World;
	template <typename>
	friend class Instance;
	static util::stack<std::reference_wrapper<InstanceBase>>& getInstanceStack(void);

	std::mt19937_64 m_rand_gen;
};

template <typename InstanceType, typename WorldType>
class World : public WorldBase
{
public:
	World(void) :
		instance(reinterpret_cast<InstanceType&>(getInstanceStack().top().get()))
	{
	}

	InstanceType &instance;

	using instance_type = InstanceType;
	using Entity = sb::Entity<WorldType>;

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