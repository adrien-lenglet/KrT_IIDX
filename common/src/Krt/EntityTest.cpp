#include "EntityTest.hpp"

namespace Krt {

EntityTest::EntityTest(Subtile::World &world) :
	Entity(world)
{
	add<Subtile::Entity>();
	add<Subtile::Entity>();
}

EntityTest::~EntityTest(void)
{
}

}