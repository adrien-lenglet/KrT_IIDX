#pragma once

#include "Math.hpp"

namespace Subtile {

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
			reinterpret_cast<Transform*>(this - off)->m_is_local_up = false;
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
	mat4& world(void);

private:
	mat4 m_local;
	mat4 m_world;

	bool m_is_local_up;
	bool m_is_world_up;

	void updateLocal(void);
	void updateWorld(void);
};

}