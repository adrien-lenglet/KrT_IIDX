#pragma once

#include "Track.hpp"

namespace Krt {

class OtherWorld : public Instance::World<OtherWorld>
{
public:
	OtherWorld(void) = default;

	int lol = 5;
};

class EntityTest3 : public Track::Entity
{
public:
	EntityTest3(void);
	~EntityTest3(void) override;
};

}