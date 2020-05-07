#include "Entity.hpp"
#include "util.hpp"

namespace Subtile {

EntityBase::EntityBase(const EntityBase::Context &ctx) :
	world(ctx.getWorld(*this)),
	m_parent(ctx.getParent())
{
	m_stack.emplace(*this);
}

EntityBase::~EntityBase(void)
{
}

void EntityBase::destroy(void)
{
	auto &p = getParent();
	auto got = p.m_children.find(*this);

	if (got == p.m_children.end())
		throw std::runtime_error("Can't find children to destroy");
	p.m_children.erase(got);
}

EntityBase& EntityBase::getParent(void)
{
	if (m_parent)
		return *m_parent;
	else
		throw std::runtime_error("No parent associated with this entity");
}

thread_local util::stack<EntityBase::Context> EntityBase::m_ctx;
thread_local std::stack<std::reference_wrapper<EntityBase>> EntityBase::m_stack;

Entity::Entity(void) :
	EntityBase(m_ctx.top())
{
}
Entity::~Entity(void)
{
}

}