#pragma once

#include "Entity.hpp"
#include "Event/World/Observer.hpp"

namespace Subtile {

class SessionBase;
class Instance;

class World : public Entity
{
public:
	World(void);
	~World(void) = 0;

	Instance &instance;
	Subtile::Event::World::Observer events;

	template <class EntityType, typename ...Args>
	EntityType& add(Args &&...args)
	{
		auto &res = getCtx().emplace_frame(std::function([&]() -> auto& {
			return m_children.emplace<EntityType>(std::forward<Args>(args)...);
		}), &world, this);
		getEntityStack().pop();
		res.setAbsolute();
		return res;
	}

private:
	friend SessionBase;
	friend Entity;

	static util::stack<std::reference_wrapper<Instance>>& getInstanceStack(void);
};

}

#include "Instance.hpp"