#include "EntityTest.hpp"
//#include "../../res/shaders/diffuse.hpp"

#include <iostream>

//#include "Subtile/Cache.hpp"

namespace Krt {

struct simpleC
{
	sb::Shader::Type::StructMember<sb::Shader::Type::Bool> base;
	sb::Shader::Type::StructMember<sb::Shader::Type::Bool, decltype(base)> base2;
};

using simple = sb::Shader::Type::Struct<simpleC,
	decltype(simpleC().base),
	decltype(simpleC().base2)>;

struct UniformStructCollection
{
	sb::Shader::Type::StructMember<sb::Shader::Type::Bool> base;
	sb::Shader::Type::StructMember<sb::Shader::Type::Bool, decltype(base)> base2;
	sb::Shader::Type::StructMember<sb::Shader::Type::Bool, decltype(base2)> base3;
	sb::Shader::Type::StructMember<sb::Shader::Type::Vec<sb::Shader::Type::Float, 3>, decltype(base3)> a;
	sb::Shader::Type::StructMember<sb::Shader::Type::Bool, decltype(a)> c;
};

using UniformStruct = sb::Shader::Type::Struct<UniformStructCollection,
	decltype(UniformStructCollection().base),
	decltype(UniformStructCollection().base2),
	decltype(UniformStructCollection().base3),
	decltype(UniformStructCollection().a),
	decltype(UniformStructCollection().c)>;

struct final_boss
{
	sb::Shader::Type::StructMember<sb::Shader::Type::Vec<sb::Shader::Type::Float, 3>> a;
	sb::Shader::Type::StructMember<sb::Shader::Type::Float, decltype(a)> b;
};

using fboss = sb::Shader::Type::Struct<final_boss,
	decltype(final_boss().a),
	decltype(final_boss().b)>;

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