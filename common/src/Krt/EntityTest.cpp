#include "EntityTest.hpp"

#include <iostream>

namespace Krt {

EntityTest::EntityTest(const Subtile::Entity::Context &ctx) :
	Entity(ctx),
	entity1(add<Subtile::Entity>()),
	entity2(add<Subtile::Entity>())
{
	/*listen(events.input.button("quit"), [this](auto value){
		std::cout << value << std::endl;
	});*/

	listen(events.input.button.pressed("quit"), [this](){
		std::cout << "quit pressed" << std::endl;
	});

	listen(events.input.button.released("quit"), [this](){
		std::cout << "quit released" << std::endl;
	});
}

EntityTest::~EntityTest(void)
{
}

}