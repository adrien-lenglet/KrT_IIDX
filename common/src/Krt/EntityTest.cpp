#include "EntityTest.hpp"
//#include "../../res/shaders/diffuse.hpp"

#include <iostream>

//#include "Subtile/Cache.hpp"

namespace Krt {

EntityTest::EntityTest(void) :
	entity1(add<EntityTest2>()),
	entity2(add<EntityTest2>()),
	m_shader(load(res.shaders().diffuse())),
	//m_material(m_shader.material()),
	//m_object(m_shader.object()),
	m_model(createModel())
{
	bind(world.events.system.input.button.pressed("quit"), [this](){
		//std::cout << "quit pressed" << std::endl;
		trigger(just_died, 14.2);
	});

	bind(world.events.system.input.button.released("quit"), [this](){
		//std::cout << "quit released" << std::endl;
		trigger(got_score, 7.92);
	});

	/*bind(world.events.update, [this](auto &t){
		pos.x += t;
		transformed();
	});*/
}

EntityTest::~EntityTest(void)
{
}

decltype(EntityTest::m_model) EntityTest::createModel(void)
{
	std::vector<decltype(m_shader)::Model::Triangle> triangles;
	auto gen_vtx = [this](){
		decltype(m_shader)::Model::Vertex res;
		for (size_t i = 0; i < 3; i++)
			res.in_pos[i] = world.srandf() * 50.0;
		for (size_t i = 0; i < 3; i++)
			res.in_normal[i] = world.srandf();
		res.in_normal = sb::math::normalize(res.in_normal);
		for (size_t i = 0; i < 2; i++)
			res.in_uv[i] = world.urandf();
		return res;
	};

	for (size_t i = 0; i < 10; i++) {
		decltype(m_shader)::Model::Triangle tri {gen_vtx(), gen_vtx(), gen_vtx()};
		triangles.emplace_back(tri);
	}
	return m_shader.model(std::move(triangles));
}

}