#pragma once

#include "Subtile/World.hpp"
#include "Subtile/RenderList.hpp"
#include "res.resdecl.hpp"

namespace Krt {

class EntityTest;

class Track : public sb::World
{
public:
	using Entity = sb::Entity<Track>;

	Track(void);
	~Track(void) override;

	Event<> done;
	int track_data = 96;

	class Render : public sb::Render::Pass
	{
		decltype(res.shaders().modules().camera().loaded()) m_camera_shader;

	public:
		Render(sb::Instance &instance) :
			m_camera_shader(instance.load(res.shaders().modules().camera())),
			camera(m_camera_shader.camera())
		{
		}

		void render(void);

		decltype(m_camera_shader.camera()) camera;
	};

	Render render;

private:
	EntityTest &entity;
};

}

#include "EntityTest.hpp"