#include "EntityTest.hpp"
#include "res.hpp"

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
		pos.x += t;
		transformed();
	});
}

EntityTest::~EntityTest(void)
{
}

}