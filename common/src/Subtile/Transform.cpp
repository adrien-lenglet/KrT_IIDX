#include "Transform.hpp"
#include "Entity.hpp"
#include "Math/Quaternion.hpp"
#include "Subtile/scp.hpp"

namespace Subtile {

rt_scc(Transform<Entity>,
	template <>
	scp::Transform(void) :
		scale(1.0),
		rot(1.0, 0.0, 0.0, 0.0),
		pos(0.0),
		m_local(1.0),
		m_world(1.0),
		m_is_local_up(true),
		m_is_world_up(true),
		m_is_absolute(false)
	{
	}

	template <>
	scp::~Transform(void)
	{
	}

	template <>
	Entity& scp::getFinal(void)
	{
		return static_cast<Entity&>(*this);
	}

	template <>
	void scp::updateLocal(void);
	template <>
	void scp::updateWorld(void);

	template <>
	mat4& scp::local(void)
	{
		if (!m_is_local_up)
			updateLocal();
		return m_local;
	}

	template <>
	mat4& scp::model_world(void)
	{
		if (!m_is_local_up || !m_is_world_up)
			updateWorld();
		return m_world;
	}

	template <>
	void scp::parentMoved(void);

	template <>
	void scp::transformed(void)
	{
		m_is_local_up = false;
		for (auto &c : getFinal().m_children)
			c.parentMoved();
	}

	template <>
	void scp::updateLocal(void)
	{
		m_local = static_cast<mat4>(rot);
		m_local = math::scale(m_local, scale);
		m_local = math::translate(m_local, pos);
		m_is_local_up = true;
	}

	template <>
	void scp::updateWorld(void)
	{
		auto &p = getFinal().m_parent;

		if (p && !m_is_absolute)
			m_world = p->model_world() * local();
		else
			m_world = local();
		m_is_world_up = true;
	}

	template <>
	void scp::setAbsolute(void)
	{
		m_is_absolute = true;
	}

	template <>
	void scp::parentMoved(void)
	{
		if (m_is_absolute)
			return;
		m_is_world_up = false;
		for (auto &c : getFinal().m_children)
			c.parentMoved();
	}
)

}