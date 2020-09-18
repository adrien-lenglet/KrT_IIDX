#pragma once

#include "Track.hpp"
#include "res.resdecl.hpp"

namespace Krt {

class EntityTest : public Track::Entity
{
public:
	EntityTest(void);
	~EntityTest(void) override;

	Event<double> just_died;
	Event<size_t> got_score;

private:
	decltype(world.instance.device.load(res.shaders().diffuse())) m_shader;
	decltype(m_shader.material(world.instance.graphics)) m_material;
	decltype(m_shader.object(world.instance.graphics)) m_object;
	sb::Buffer::Vertex<decltype(m_shader)::Vertex> m_model_buffer;
	decltype(world.instance.device.model(m_model_buffer)) m_model;

	decltype(m_model_buffer) createModelBuffer(void);

	double m_angle = 0.0;
	bool do_rot = false;
};

}