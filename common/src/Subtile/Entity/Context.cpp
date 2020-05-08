#include "../Entity.hpp"

namespace Subtile {

Entity::Context::Context(World *world, Entity *parent) :
	m_world(world),
	m_parent(parent)
{
}

Entity* Entity::Context::getParent(void) const
{
	return m_parent;
}

}