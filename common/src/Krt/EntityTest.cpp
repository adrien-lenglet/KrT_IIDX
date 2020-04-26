#include "EntityTest.hpp"

#include <iostream>

namespace Krt {

EntityTest::EntityTest(void) :
	entity1(add<EntityTest2>()),
	entity2(add<EntityTest2>())
{
	/*listen(events.input.button("quit"), [this](auto value){
		std::cout << value << std::endl;
	});*/

	listen(events.input.button.pressed("quit"), [this](){
		std::cout << "quit pressed" << std::endl;
	});

	listen(events.input.button.released("quit"), [this](){
		std::cout << "quit released" << std::endl;
		events.system.quit();
	});
}

EntityTest::~EntityTest(void)
{
}

}