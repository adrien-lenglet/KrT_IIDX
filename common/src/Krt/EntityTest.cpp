#include "EntityTest.hpp"

namespace Krt {

EntityTest::EntityTest(const Subtile::Entity::Context &ctx) :
	Entity(ctx),
	entity1(add<Subtile::Entity>()),
	entity2(add<Subtile::Entity>())
{
}

EntityTest::~EntityTest(void)
{
}

}