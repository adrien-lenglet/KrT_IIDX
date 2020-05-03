#include "../Entity.hpp"

namespace Subtile {

Entity::Context::Context(World *world, EntityBase *parent) :
	m_world(world),
	m_parent(parent)
{
}

EntityBase* Entity::Context::getParent(void) const
{
	return m_parent;
}

}