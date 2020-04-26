#include "Track.hpp"

#include <iostream>

namespace Krt {

Track::Track(void) :
	entity(add<EntityTest>())
{
}

Track::~Track(void)
{
}

}