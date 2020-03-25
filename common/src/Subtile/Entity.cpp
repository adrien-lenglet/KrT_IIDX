#include "Entity.hpp"
#include "util.hpp"

namespace Subtile {

Entity::Entity(const Entity::Context &ctx) :
	m_world(ctx.getWorld()),
	m_parent(ctx.getParent())
{
}

Entity::~Entity(void)
{
}

World& Entity::getWorld(void)
{
	return m_world;
}

void Entity::destroy(void)
{
	getParent().destroyChild(*this);
}

Entity& Entity::getParent(void)
{
	if (m_parent)
		return *m_parent;
	else
		throw std::runtime_error("No parent associated with this entity");
}

void Entity::destroyChild(Entity &entity)
{
	auto got = m_children.find(&entity);

	if (got != m_children.end())
		m_children.erase(got);
	else
		throw std::runtime_error("Entity to destroy not found among children");
}

void Entity::listenInput(const std::string &input, const std::function<void (bool)> &callback)
{
	m_input_listeners_bool.push_back(m_world.listenInput(input, callback));
}

void Entity::listenInput(const std::string &input, const std::function<void (double)> &callback)
{
	m_input_listeners_double.push_back(m_world.listenInput(input, callback));
}

}