#pragma once

#include <random>
#include "Entity.hpp"
#include "Event/World/Observer.hpp"

namespace Subtile {

class SessionBase;
class Instance;
namespace Render {
class Pass;
}

class World : public Entity<World>
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
		//res.setAbsolute();
		return res;
	}

	double urandf(void);
	double srandf(void);

private:
	friend SessionBase;
	template <typename WorldType>
	friend class Entity;
	friend Render::Pass;

	static util::stack<std::reference_wrapper<Instance>>& getInstanceStack(void);

	template <typename S>
	decltype(auto) loadShader(S &&shaderres);

	std::mt19937_64 m_rand_gen;
};

}

#include "Instance.hpp"

namespace Subtile {
	template <typename S>
	decltype(auto) World::loadShader(S &&shaderres)
	{
		return instance.loadShader(std::forward<S>(shaderres));
	}
}