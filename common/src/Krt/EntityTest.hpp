#pragma once

#include "Subtile/Entity.hpp"
#include "EntityTest2.hpp"

namespace Krt {

class EntityTest : public Subtile::Entity
{
public:
	EntityTest(void);
	~EntityTest(void) override;

	Subtile::Entity::Event<double> just_died;
	Subtile::Entity::Event<size_t> got_score;

private:
	EntityTest2 &entity1;
	EntityTest2 &entity2;
};

}