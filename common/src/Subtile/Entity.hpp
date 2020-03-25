#pragma once

#include <map>
#include <vector>
#include <memory>
#include <functional>

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

	void listen(const std::string &input, std::function<void (bool)> &callback);
	void listen(const std::string &input, std::function<void (double)> &callback, bool isTrigger = false);

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

	class InputListener
	{
	public:
		InputListener(const std::string &input, std::function<void (bool)> &callback);
		InputListener(const std::string &input, std::function<void (double)> &callback, bool isTrigger);
		~InputListener(void);

	private:
	};

	std::vector<InputListener> m_listeners;

	Entity& getParent(void);
	void destroyChild(Entity &entity);
};

}

#include "World.hpp"