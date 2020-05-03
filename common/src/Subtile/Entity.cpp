#include "Entity.hpp"
#include "util.hpp"

namespace Subtile {

EntityBase::EntityBase(const EntityBase::Context &ctx) :
	world(ctx.getWorld(*this)),
	m_parent(ctx.getParent())
{
}

EntityBase::~EntityBase(void)
{
}

void EntityBase::destroy(void)
{
	/*if (m_parent == nullptr)
		m_world.resetRoot();
	else
		getParent().destroyChild(*this);*/
}

EntityBase& EntityBase::getParent(void)
{
	if (m_parent)
		return *m_parent;
	else
		throw std::runtime_error("No parent associated with this entity");
}

std::stack<EntityBase::Context> EntityBase::m_ctx;

EntityBase::Context EntityBase::popCtx(void)
{
	if (m_ctx.size() == 0)
		throw std::runtime_error("No context for entity creation");

	EntityBase::Context res = std::move(m_ctx.top());

	m_ctx.pop();
	return res;
}

Entity::Entity(void) :
	EntityBase(popCtx())
{
}
Entity::~Entity(void)
{
}

}