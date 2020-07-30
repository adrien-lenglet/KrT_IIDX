#include "Entity.hpp"
#include "util.hpp"

namespace Subtile {

EntityBase::Context::Context(World *world, EntityBase *parent) :
	m_world(world),
	m_parent(parent)
{
}

EntityBase* EntityBase::Context::getParent(void) const
{
	return m_parent;
}

EntityBase::EntityBase(EntityBase *parent) :
	m_parent(parent)
{
	getEntityStack().emplace(*this);
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

util::stack<EntityBase::Context>& EntityBase::getCtx(void)
{
	static thread_local util::stack<EntityBase::Context> res;

	return res;
}

util::stack<std::reference_wrapper<EntityBase>>& EntityBase::getEntityStack(void)
{
	static thread_local util::stack<std::reference_wrapper<EntityBase>> res;

	return res;
}

}