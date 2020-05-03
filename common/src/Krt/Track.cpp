#include "Track.hpp"
#include "Subtile/Binding.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <array>

namespace Krt {

Track::Track(void) :
	entity(add<EntityTest>())
{
	bind(entity.just_died(), [](const double &val){
		std::cout << "Just died event: " << val << std::endl;
	});

	bind(entity.got_score(), [this](const size_t &score){
		std::cout << "Got score event: " << score << std::endl;
		//events.system.quit();
	});

	std::cout << sizeof(Subtile::Binding::Strong<int>) << std::endl;
	std::cout << sizeof(Subtile::Binding::Strong<int, true>) << std::endl;

	/*Subtile::Binding::Strong<int>::Multiple socket;
	Subtile::Binding::Dependency::Socket deps, deps2;

	socket.bind({deps, deps2}, 56);
	std::cout << "Size of collection: " << sizeof(socket) << std::endl;
	for (auto &i : socket)
		std::cout << "Entry: " << i << std::endl;*/

	/*util::stack<int> stack;

	std::cout << stack.top() << std::endl;*/
}

Track::~Track(void)
{
}

}