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

	class Render : public sb::RenderList
	{
		Instance &m_instance;
		decltype(res.shaders().modules().camera().loaded()) m_camera_shader;

	public:
		Render(Instance &instance) :
			m_instance(instance),
			m_camera_shader(instance.device.load(res.shaders().modules().camera())),
			base_cursor(instance.surface->cursor()),
			camera_pos(0.0, 0.0, -7.0),
			camera(m_camera_shader.camera(instance.graphics))
		{
		}
		~Render(void)
		{
			m_instance.graphics.waitIdle();
		}

		glm::dvec2 base_cursor;
		glm::vec3 camera_pos;

		void render(sb::CommandBuffer::Record::RenderPass &cmd);

		decltype(m_camera_shader.camera(instance.graphics)) camera;
	};

	Render render;

private:
	EntityTest &entity;
};

}

#include "EntityTest.hpp"