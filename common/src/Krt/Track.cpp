#include "Track.hpp"

#include <iostream>

namespace Krt {

Track::Track(void) :
	entity(add<EntityTest>())
{
	listen(entity.just_died(), [this](const double &val){
		std::cout << "Just died event: " << val << std::endl;
		events.system.quit();
	});

	listen(entity.got_score(), [](const size_t &score){
		std::cout << "Got score event: " << score << std::endl;
	});
}

Track::~Track(void)
{
}

}