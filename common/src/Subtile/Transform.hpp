#pragma once

#include "Math.hpp"

namespace Subtile {

class WorldBase;

/*template <class Final>
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
			transformed();
			return Extended::operator=(std::forward<Args>(args)...);
		}

		template <typename ...Args>
		auto& operator+=(Args &&...args)
		{
			transformed();
			return Extended::operator+=(std::forward<Args>(args)...);
		}

		template <typename ...Args>
		auto& operator-=(Args &&...args)
		{
			transformed();
			return Extended::operator-=(std::forward<Args>(args)...);
		}

		template <typename ...Args>
		auto& operator*=(Args &&...args)
		{
			transformed();
			return Extended::operator*=(std::forward<Args>(args)...);
		}

		template <typename ...Args>
		auto& operator/=(Args &&...args)
		{
			transformed();
			return Extended::operator/=(std::forward<Args>(args)...);
		}

		auto& operator++(void)
		{
			transformed();
			return Extended::operator++();
		}

		auto& operator--(void)
		{
			transformed();
			return Extended::operator--();
		}

		auto operator++(int v)
		{
			transformed();
			return Extended::operator++(v);
		}

		auto operator--(int v)
		{
			transformed();
			return Extended::operator--(v);
		}

	private:
		void transformed(void)
		{
			reinterpret_cast<Transform*>(reinterpret_cast<char*>(this) - off)->transformed();
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
	void transformed(void);

private:
	friend Final;
	friend WorldBase;

	Final& getFinal(void);

	mat4 m_local;
	mat4 m_world;

	bool m_is_local_up;
	bool m_is_world_up;
	bool m_is_absolute;

	void updateLocal(void);
	void updateWorld(void);
	void setAbsolute(void);
	void parentMoved(void);
};*/

}