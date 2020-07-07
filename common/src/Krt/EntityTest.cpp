#include "EntityTest.hpp"
#include "res.resdecl.hpp"
//#include "../../res/shaders/diffuse.hpp"

#include <iostream>

#include "Subtile/Cache.hpp"

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

	//std::cout << &res.models().npc().gordon() << std::endl;
}

EntityTest::~EntityTest(void)
{
}

}