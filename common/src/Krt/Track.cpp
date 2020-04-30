#include "Track.hpp"
#include "Subtile/Binding.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

namespace Krt {

Track::Track(void) :
	entity(add<EntityTest>())
{
	listen(entity.just_died(), [](const double &val){
		std::cout << "Just died event: " << val << std::endl;
	});

	listen(entity.got_score(), [this](const size_t &score){
		std::cout << "Got score event: " << score << std::endl;
		events.system.quit();
	});

	/*std::cout << sizeof(Subtile::Binding::Source::Weak<int>) << std::endl;
	std::cout << sizeof(util::unique_set<int>) << std::endl;
	std::cout << sizeof(Subtile::Binding::Source::Weak<int>::Element) << std::endl;*/

	Subtile::Binding::Source::Weak<int> socket;
	Subtile::Binding::Dependency::Socket deps;

	socket.bind(deps, 10);

}

Track::~Track(void)
{
}

}