#include "Transform.hpp"
#include "Entity.hpp"
#include "Math/Quaternion.hpp"

namespace Subtile {

template <>
Transform<Entity>::Transform(void) :
	scale(1.0),
	rot(1.0, 0.0, 0.0, 0.0),
	pos(0.0),
	m_is_local_up(false),
	m_is_world_up(false),
	m_is_absolute(false)
{
}

template <>
Transform<Entity>::~Transform(void)
{
}

template <>
Entity& Transform<Entity>::getFinal(void)
{
	return static_cast<Entity&>(*this);
}

template <>
void Transform<Entity>::updateLocal(void);
template <>
void Transform<Entity>::updateWorld(void);

template <>
mat4& Transform<Entity>::local(void)
{
	if (!m_is_local_up)
		updateLocal();
	return m_local;
}

template <>
mat4& Transform<Entity>::model_world(void)
{
	if (!m_is_local_up || !m_is_world_up)
		updateWorld();
	return m_world;
}

template <>
void Transform<Entity>::updateLocal(void)
{
	m_local = static_cast<mat4>(rot);
	m_local = math::scale(m_local, scale);
	m_local = math::translate(m_local, pos);
	m_is_local_up = true;
}

template <>
void Transform<Entity>::updateWorld(void)
{
	auto &p = getFinal().m_parent;

	if (p && !m_is_absolute)
		m_world = p->model_world() * local();
	else
		m_world = local();
	m_is_world_up = true;
}

template <>
void Transform<Entity>::setAbsolute(void)
{
	m_is_absolute = true;
}

template <>
void Transform<Entity>::parentMoved(void);

template <>
void Transform<Entity>::propModified(void)
{
	m_is_local_up = false;
	for (auto &c : getFinal().m_children)
		c.parentMoved();
}

template <>
void Transform<Entity>::parentMoved(void)
{
	if (m_is_absolute)
		return;
	m_is_world_up = false;
	for (auto &c : getFinal().m_children)
		c.parentMoved();
}

}