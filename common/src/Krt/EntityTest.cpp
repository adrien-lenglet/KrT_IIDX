#include "EntityTest.hpp"

#include <iostream>

namespace Krt {

EntityTest::EntityTest(void) :
	entity1(add<EntityTest2>()),
	entity2(add<EntityTest2>())
{
	bind(world.events.system.input.button.pressed("quit"), [this](){
		std::cout << "quit pressed" << std::endl;
		trigger(just_died, 14.2);
	});

	bind(world.events.system.input.button.released("quit"), [this](){
		std::cout << "quit released" << std::endl;
		trigger(got_score, 7.92);
	});

	bind(world.events.update, [this](auto &t){
		pos = pos + sb::vec3(t, 0.0, 0.0);
		auto &w = model_world();
		for (size_t i = 0; i < 4; i++) {
			auto comma = "";
			for (size_t j = 0; j < 4; j++) {
				std::cout << comma << w[j][i];
				comma = ", ";
			}
			std::cout << std::endl;
		}
	});
}

EntityTest::~EntityTest(void)
{
}

}