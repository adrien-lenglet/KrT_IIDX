#include "EntityTest.hpp"

#include <iostream>

namespace Krt {

EntityTest::EntityTest(const Subtile::Entity::Context &ctx) :
	Entity(ctx),
	entity1(add<Subtile::Entity>()),
	entity2(add<Subtile::Entity>())
{
	/*listen(events.input.analog("up"), [this](double value){
		std::cout << value << std::endl;
	});
	listen(events.input.button("A"), [this](bool value){
		std::cout << value << std::endl;
	});*/
	listen(events.input.button("quit"), [this](bool value){
		std::cout << value << std::endl;
	});
}

EntityTest::~EntityTest(void)
{
}

}