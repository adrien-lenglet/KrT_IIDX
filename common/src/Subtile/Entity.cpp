#include "Entity.hpp"
#include "util.hpp"

namespace Subtile {

Entity::Entity(const Entity::Context &ctx) :
	Event::World::Socket(ctx.getWorld().getEvents()),
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
	/*if (m_parent == nullptr)
		m_world.resetRoot();
	else
		getParent().destroyChild(*this);*/
}

Entity& Entity::getParent(void)
{
	if (m_parent)
		return *m_parent;
	else
		throw std::runtime_error("No parent associated with this entity");
}

}