#include "Entity.hpp"
#include "util.hpp"

namespace Subtile {

EntityImpl::EntityImpl(const EntityImpl::Context &ctx, Subtile::Event::World::Observer *events) :
	Event::World::Socket(events ? static_cast<Subtile::Event::World::Observer&>(*events) : ctx.getWorld(*this).getEvents()),
	world(ctx.getWorld(*this)),
	m_parent(ctx.getParent())
{
}

EntityImpl::~EntityImpl(void)
{
}

void EntityImpl::destroy(void)
{
	/*if (m_parent == nullptr)
		m_world.resetRoot();
	else
		getParent().destroyChild(*this);*/
}

EntityImpl& EntityImpl::getParent(void)
{
	if (m_parent)
		return *m_parent;
	else
		throw std::runtime_error("No parent associated with this entity");
}

std::stack<EntityImpl::Context> EntityImpl::m_ctx;

EntityImpl::Context EntityImpl::popCtx(void)
{
	if (m_ctx.size() == 0)
		throw std::runtime_error("No context for entity creation");

	EntityImpl::Context res = std::move(m_ctx.top());

	m_ctx.pop();
	return res;
}

Entity::Entity(Subtile::Event::World::Observer *events) :
	EntityImpl(popCtx(), events)
{
}
Entity::~Entity(void)
{
}

}