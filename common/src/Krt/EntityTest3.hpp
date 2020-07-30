#pragma once

#include "Track.hpp"

namespace Krt {

class OtherWorld : public sb::World
{
public:
	OtherWorld(void) = default;

	int lol = 5;
};

class EntityTest3 : public sb::Entity<sb::World>
{
public:
	EntityTest3(void);
	~EntityTest3(void) override;
};

}