#pragma once

#include "Track.hpp"

namespace Krt {

class EntityTest2 : public Track::Entity
{
public:
	EntityTest2(void);
	~EntityTest2(void) override;
};

}