#include "Entity.hpp"
#include "util.hpp"

namespace Subtile {

Entity::Entity(void) :
	world(m_ctx.top().getWorld(*this)),
	m_parent(m_ctx.top().getParent())
{
	m_stack.emplace(*this);
}

Entity::~Entity(void)
{
}

void Entity::destroy(void)
{
	auto &p = getParent();
	auto got = p.m_children.find(*this);

	if (got == p.m_children.end())
		throw std::runtime_error("Can't find children to destroy");
	p.m_children.erase(got);
}

Entity& Entity::getParent(void)
{
	if (m_parent)
		return *m_parent;
	else
		throw std::runtime_error("No parent associated with this entity");
}

thread_local util::stack<Entity::Context> Entity::m_ctx;
thread_local util::stack<std::reference_wrapper<Entity>> Entity::m_stack;

}