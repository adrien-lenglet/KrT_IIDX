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

	//std::cout << sb::Shader::Type::Vec<sb::Shader::Type::Float, 3>(glm::vec3(1.2)).y << std::endl;
	//std::cout << util::csize_t<46>{} << std::endl;

	//sb::Shader::Type::Std140::Mat<sb::Shader::Type::Float, 3, 3> matrix;
	/*sb::Shader::Type::Std140::Mat<sb::Shader::Type::Float, 3, 3> matrix(glm::identity<glm::mat3>());

	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++)
			std::cout << matrix[i][j] << ", ";
		std::cout << std::endl;
	}*/

	//std::cout << sizeof(sb::Shader::Type::Mat<sb::Shader::Type::Float, 3, 2>) << std::endl; // 48
	//std::cout << sizeof(sb::Shader::Type::Mat<sb::Shader::Type::Float, 2, 3>) << std::endl;	// 32

	/*std::cout << sizeof(sb::Shader::Type::Std140::Array<sb::Shader::Type::Float, 1>) << std::endl;
	std::cout << sizeof(sb::Shader::Type::Std140::Array<sb::Shader::Type::Float, 2>) << std::endl;
	std::cout << sizeof(sb::Shader::Type::Std140::Array<sb::Shader::Type::Float, 3>) << std::endl;
	using vec_arr = sb::Shader::Type::Std140::Array<sb::Shader::Type::Vec<sb::Shader::Type::Float, 2>, 1>;
	std::cout << sizeof(vec_arr) << std::endl;
	std::cout << vec_arr::salign{} << std::endl;
	std::cout << vec_arr::balign{} << std::endl;
	std::cout << vec_arr::ealign{} << std::endl;*/

	/*sb::Shader::Type::Array<sb::Shader::Type::Float, 3> arr;

	size_t i = 0;
	for (auto &e : arr)
		e = ++i + 1;

	for (auto &e : static_cast<const sb::Shader::Type::Array<sb::Shader::Type::Float, 3>&>(arr))
		std::cout << e << std::endl;*/

	/*std::cout << sizeof(UniformStruct) << std::endl;

	std::cout << std::endl;

	std::cout << offsetof(UniformStruct, base) << std::endl;
	std::cout << offsetof(UniformStruct, base2) << std::endl;
	std::cout << offsetof(UniformStruct, base3) << std::endl;
	std::cout << offsetof(UniformStruct, a) << std::endl;
	std::cout << offsetof(UniformStruct, c) << std::endl;

	std::cout << std::endl;

	UniformStruct col;
	std::cout << decltype(col.base)::offset{} << std::endl;
	std::cout << decltype(col.base2)::offset{} << std::endl;
	std::cout << decltype(col.base3)::offset{} << std::endl;
	std::cout << decltype(col.a)::offset{} << std::endl;
	std::cout << decltype(col.c)::offset{} << std::endl;

	std::cout << std::endl;*/

	//std::cout << sizeof(fboss) << std::endl;
	/*std::cout << simple::salign{} << std::endl;
	std::cout << simple::balign{} << std::endl;
	std::cout << simple::ealign{} << std::endl;*/

	//res_class::shaders_class::diffuse_type::objectMapped ubo;
	//std::cout << decltype(ubo.mvp)::offset_end::value << std::endl;

	//std::cout << &res.models().npc().gordon() << std::endl;
}

EntityTest::~EntityTest(void)
{
}

}