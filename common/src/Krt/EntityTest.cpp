#include "EntityTest.hpp"

#include <iostream>

namespace Krt {

EntityTest::EntityTest(const Subtile::Entity::Context &ctx) :
	Entity(ctx),
	entity1(add<Subtile::Entity>()),
	entity2(add<Subtile::Entity>())
{
	/*listenInput("forward", std::function<void (double)>([](double val) {
		std::cout << val << std::endl;
	}));*/
}

EntityTest::~EntityTest(void)
{
}

}