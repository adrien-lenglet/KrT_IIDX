#pragma once

#include "Entity.hpp"
#include "Event/World/Observer.hpp"

namespace Subtile {

class SessionBase;

class World : public Entity
{
public:
	World(void);
	~World(void) = 0;

	Subtile::Event::World::Observer events;

	template <class EntityType, typename ...Args>
	EntityType& add(Args &&...args)
	{
		auto &res = Entity::add<EntityType>(std::forward<Args>(args)...);
		res.setAbsolute();
		return res;
	}

private:
	friend SessionBase;
	friend Entity;

	static util::stack<std::reference_wrapper<Subtile::Event::System::Observer>>& getSystems(void);
};

}