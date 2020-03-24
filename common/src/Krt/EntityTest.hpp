#pragma once

#include "Subtile/Entity.hpp"

namespace Krt {

class EntityTest : public Subtile::Entity
{
public:
	EntityTest(Subtile::World &world);
	~EntityTest(void) override;
};

}