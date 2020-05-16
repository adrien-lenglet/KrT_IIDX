#include "Transform.hpp"
#include <glm/gtx/quaternion.hpp>

namespace Subtile {

class Entity;

template <>
Transform<Entity>::Transform(void) :
	scale(1.0),
	rot(1.0, 0.0, 0.0, 0.0),
	pos(0.0),
	m_is_local_up(false),
	m_is_world_up(false)
{
}

template <>
Transform<Entity>::~Transform(void)
{
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
mat4& Transform<Entity>::world(void)
{
	if (!m_is_world_up)
		updateWorld();
	return m_world;
}

template <>
void Transform<Entity>::updateLocal(void)
{
	mat4 buf;

	m_local = static_cast<mat4>(rot);
	glm::scale(buf, scale);
	m_local *= buf;
	glm::translate(buf, pos);
	m_local *= buf;
	m_is_local_up = true;
}

template <>
void Transform<Entity>::updateWorld(void)
{
	//if (m_parent)
	//	m_world = m_parent->world() * local();
	//else
		m_world = local();
	m_is_world_up = true;
}

}