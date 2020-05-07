#pragma once

#include "Subtile/Entity.hpp"
#include "EntityTest2.hpp"

namespace Krt {

class EntityTest : public sb::Entity
{
public:
	EntityTest(void);
	~EntityTest(void) override;

	Event<double> just_died;
	Event<size_t> got_score;

private:
	EntityTest2 &entity1;
	EntityTest2 &entity2;
};

}