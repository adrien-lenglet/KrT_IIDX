#include "Track.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

namespace Krt {

Track::Track(void) :
	entity(add<EntityTest>())
{
	/*listen(entity.just_died(), [](const double &val){
		std::cout << "Just died event: " << val << std::endl;
	});

	listen(entity.got_score(), [this](const size_t &score){
		std::cout << "Got score event: " << score << std::endl;
		//events.system.quit();
	});*/
}

Track::~Track(void)
{
}

}