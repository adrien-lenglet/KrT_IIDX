#pragma once

#include "Math.hpp"

namespace Subtile {

class World;

template <class Final>
class Transform
{
	template <class Extended, size_t off>
	class ext : public Extended
	{
	public:
		template <typename ...Args>
		ext(Args &&...args) :
			Extended(std::forward<Args>(args)...)
		{
		}
		~ext(void)
		{
		}

		template <typename ...Args>
		auto& operator=(Args &&...args)
		{
			auto &t = *reinterpret_cast<Transform*>(reinterpret_cast<char*>(this) - off);
			t.m_is_local_up = false;
			for (auto &c : t.getFinal().m_children)
				c.parentMoved();
			return Extended::operator=(std::forward<Args>(args)...);
		}

		static size_t offset(void)
		{
			return off;
		}
	};

public:
	Transform(void);
	~Transform(void);

	ext<vec3, 0> scale;
	ext<quat, sizeof(scale)> rot;
	ext<vec3, sizeof(scale) + sizeof(rot)> pos;

	mat4& local(void);
	mat4& model_world(void);

private:
	friend Final;
	friend World;

	Final& getFinal(void)
	{
		return static_cast<Final&>(*this);
	}

	mat4 m_local;
	mat4 m_world;

	bool m_is_local_up;
	bool m_is_world_up;
	bool m_is_absolute;

	void updateLocal(void);
	void updateWorld(void);
	void setAbsolute(void);
	void parentMoved(void);
};

}