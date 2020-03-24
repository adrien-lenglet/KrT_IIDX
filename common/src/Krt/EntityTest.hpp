#pragma once

#include "Subtile/Entity.hpp"

namespace Krt {

class EntityTest : public Subtile::Entity
{
public:
	EntityTest(const Subtile::Entity::Context &ctx);
	~EntityTest(void) override;

private:
	Subtile::Entity &entity1;
	Subtile::Entity &entity2;
};

}