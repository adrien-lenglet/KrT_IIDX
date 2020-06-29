#include "Krt.hpp"
#include "Krt/EntityTest.hpp"
#include "Krt/Track.hpp"
#include "Krt/Race.hpp"
#include "util.hpp"

#include <iostream>

#ifdef DEBUG
#define IS_DEBUG true
#else
#define IS_DEBUG false
#endif

namespace Krt {

Instance::Instance(std::vector<std::string> args, bool) :
	config(args),
	subtile(IS_DEBUG)
{
}

Instance::~Instance(void)
{
}

void Instance::run(void)
{
	subtile.setInputs([](const auto &s){
		s.addButton("quit");
	});

	auto race = subtile.createSession<Race>();
	race->run();
}

Instance::Config::Config(std::vector<std::string> args)
{
	isProfile = util::erase_if_contains(args, "profile");

	if (!args.empty())
		throw std::runtime_error(std::string("Unknown argument(s): " + util::join(args, std::string(", "))));
}

Instance::Config::~Config(void)
{
}

}