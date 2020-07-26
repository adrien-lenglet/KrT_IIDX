#include "EntityTest.hpp"
//#include "../../res/shaders/diffuse.hpp"

#include <iostream>

//#include "Subtile/Cache.hpp"

namespace Krt {

EntityTest::EntityTest(void) :
	entity1(add<EntityTest2>()),
	entity2(add<EntityTest2>()),
	m_shader(load(res.shaders().diffuse())),
	m_material(m_shader.material()),
	m_object(m_shader.object())
{
	bind(world.events.system.input.button.pressed("quit"), [this](){
		//std::cout << "quit pressed" << std::endl;
		trigger(just_died, 14.2);
	});

	bind(world.events.system.input.button.released("quit"), [this](){
		//std::cout << "quit released" << std::endl;
		trigger(got_score, 7.92);
	});

	bind(world.events.update, [this](auto &t){
		pos.x += t;
		transformed();
	});

	auto shader = load(res.shaders().diffuse());

	auto obj = shader.object();
	auto mat = shader.material();

	mat.color = sb::vec3(2.3);

	res.shaders().diffuse().getStages().at(sb::Shader::Stage::Fragment).getVk().getCompiled().read();
	res.shaders().diffuse().getStages().at(sb::Shader::Stage::Vertex).getVk().getCompiled().read();
}

EntityTest::~EntityTest(void)
{
}

}