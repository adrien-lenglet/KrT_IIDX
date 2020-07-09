#include "EntityTest.hpp"
#include "res.resdecl.hpp"
//#include "../../res/shaders/diffuse.hpp"

#include <iostream>

//#include "Subtile/Cache.hpp"

namespace Krt {

EntityTest::EntityTest(void) :
	entity1(add<EntityTest2>()),
	entity2(add<EntityTest2>())
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
	auto mat = shader.material();

	//std::cout << sb::Shader::Type::Vec<sb::Shader::Type::Float, 3>(glm::vec3(1.2)).y << std::endl;
	//std::cout << util::csize_t<46>{} << std::endl;

	//sb::Shader::Type::Std140::Mat<sb::Shader::Type::Float, 3, 3> matrix;
	/*sb::Shader::Type::Std140::Mat<sb::Shader::Type::Float, 3, 3> matrix(glm::identity<glm::mat3>());

	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++)
			std::cout << matrix[i][j] << ", ";
		std::cout << std::endl;
	}*/

	std::cout << sizeof(sb::Shader::Type::Mat<sb::Shader::Type::Float, 3, 2>) << std::endl; // 48
	std::cout << sizeof(sb::Shader::Type::Mat<sb::Shader::Type::Float, 2, 3>) << std::endl;	// 32

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

	//std::cout << &res.models().npc().gordon() << std::endl;
}

EntityTest::~EntityTest(void)
{
}

}