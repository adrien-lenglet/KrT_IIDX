#pragma once

#include "Krt.hpp"
#include "Subtile/RenderList.hpp"
#include "res.resdecl.hpp"

namespace Krt {

class EntityTest;

class Track : public Instance::World<Track>
{
public:
	Track(void);
	~Track(void) override;

	Event<> done;
	int track_data = 96;

	class Render : public sb::Render::Pass
	{
		decltype(res.shaders().modules().camera().loaded()) m_camera_shader;
		decltype(res.shaders().render_passes().deffered().loaded()) m_render_pass;
		decltype(instance.graphics.primary()) m_cmd_buf;

	public:
		Render(Instance &instance) :
			m_camera_shader(instance.load(res.shaders().modules().camera())),
			m_render_pass(instance.load(res.shaders().render_passes().deffered())),
			m_cmd_buf(instance.graphics.primary()),
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