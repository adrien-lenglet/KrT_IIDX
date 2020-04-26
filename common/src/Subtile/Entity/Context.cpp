#include "../Entity.hpp"

namespace Subtile {

Entity::Context::Context(World *world, EntityImpl *parent) :
	m_world(world),
	m_parent(parent)
{
}

EntityImpl* Entity::Context::getParent(void) const
{
	return m_parent;
}

}