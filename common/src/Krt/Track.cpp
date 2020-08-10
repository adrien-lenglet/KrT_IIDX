#include "Track.hpp"
#include "Subtile/Binding.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <array>

namespace Krt {

Track::Track(void) :
	render(instance),
	entity(add<EntityTest>())
{
	bind(entity.just_died, [](const double &){
		//std::cout << "Just died event: " << val << std::endl;
	});

	bind(entity.got_score, [this](const size_t &){
		//std::cout << "Got score event: " << score << std::endl;
		trigger(done);
	});
}

Track::~Track(void)
{
	destroy_children();
}

}