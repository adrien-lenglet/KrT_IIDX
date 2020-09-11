#include <iostream>
#include "EntityTest.hpp"
#include <glm/gtx/transform.hpp>

namespace Krt {

EntityTest::EntityTest(void) :
	entity1(add<EntityTest2>()),
	entity2(add<EntityTest2>()),
	m_shader(world.instance.load(res.shaders().diffuse())),
	m_material(m_shader.material(world.instance.graphics)),
	m_object(m_shader.object(world.instance.graphics)),
	m_model_buffer(createModelBuffer()),
	m_model(world.instance.model(m_model_buffer))
{
	bind(world.events.system.input.button.pressed("quit"), [this](){
		//std::cout << "quit pressed" << std::endl;
		trigger(just_died, 14.2);
	});

	bind(world.events.system.input.button.released("quit"), [this](){
		//std::cout << "quit released" << std::endl;
		trigger(got_score, 7.92);
	});

	bind(world.render, m_shader.render(m_model, world.render.camera, m_material, m_object));

	bind(world.events.update, [this](auto &time){
		m_material.counter++;
		if (m_material.counter > 256) {
			m_material.counter = 0;
		}
		world.instance.uploadDescSet(m_material);

		m_angle += time / 16.0;
		auto mat = glm::rotate((float)m_angle, glm::normalize(glm::vec3(1.0, 1.0, 1.0)));
		m_object.model_world = mat;
		m_object.model_world_normal = mat;
		for (size_t i = 0; i < 3; i++)
			m_object.model_world_normal[3][i] = 0.0f;
		world.instance.uploadDescSet(m_object);
	});
}

EntityTest::~EntityTest(void)
{
}

decltype(EntityTest::m_model_buffer) EntityTest::createModelBuffer(void)
{
	std::vector<decltype(m_model_buffer)::value_type> values;

	for (size_t i = 0; i < 1000; i++) {
		decltype(m_model_buffer)::value_type tri[3];
		glm::vec3 points[3];
		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 3; j++) {
				points[i][j] = world.srandf() * 5.0;
				tri[i].pos[j] = points[i][j];
			}
		glm::vec3 normal = glm::normalize(glm::cross(points[1] - points[0], points[2] - points[0]));
		for (size_t i = 0; i < 3; i++)
			tri[i].normal = normal;
		for (size_t i = 0; i < 3; i++)
			for (size_t j = 0; j < 2; j++)
				tri[i].uv[j] = world.urandf();
		for (size_t i = 0; i < 3; i++)
			values.emplace_back(tri[i]);
	}
	auto res = world.instance.vertexBuffer<decltype(m_model_buffer)::value_type>(values.size(), world.instance.graphics);
	world.instance.copyBuffer(values, res);
	return res;
}

}