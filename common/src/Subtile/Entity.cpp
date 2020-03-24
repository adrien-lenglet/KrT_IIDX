#include "Entity.hpp"

namespace Subtile {

Entity::Entity(World &world) :
	m_world(world)
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
}

}