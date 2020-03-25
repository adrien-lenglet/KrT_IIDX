#pragma once

#include <vector>
#include "Observer.hpp"

namespace Subtile {

class World;

class Entity
{
public:
	class Context
	{
	public:
		~Context(void) = default;

	private:
		friend Entity;
		friend World;

		Context(World &world, Entity *parent);

		World &m_world;
		Entity *m_parent;

		World& getWorld(void) const;
		Entity* getParent(void) const;
	};

	Entity(const Entity::Context &ctx);
	virtual ~Entity(void);

protected:
	World& getWorld(void);

	void listenInput(const std::string &input, const std::function<void (bool)> &callback);
	void listenInput(const std::string &input, const std::function<void (double)> &callback);

	template <typename EntityType, class ...ArgsTypes>
	EntityType& add(const ArgsTypes &...args)
	{
		auto added = new EntityType(Context(m_world, this), args...);

		m_children.emplace(added, added);
		return *added;
	}

	void destroy(void);

private:
	World &m_world;
	Entity *m_parent;
	std::map<Subtile::Entity*, std::unique_ptr<Subtile::Entity>> m_children;

	std::vector<Observer<bool>::Listener> m_input_listeners_bool;
	std::vector<Observer<double>::Listener> m_input_listeners_double;

	Entity& getParent(void);
	void destroyChild(Entity &entity);
};

}

#include "World.hpp"