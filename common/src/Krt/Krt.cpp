#include "Krt.hpp"
#include "Krt/EntityTest.hpp"
#include "Krt/Track.hpp"
#include "Krt/Race.hpp"
#include "util.hpp"

#include <iostream>

namespace Krt {

Instance::Instance(std::vector<std::string> args, bool isDebug) :
	sb::Instance<Instance>(isDebug, "SUNREN®"),
	config(args)
{
}

Instance::~Instance(void)
{
}

void Instance::run(void)
{
	setInputs([](const auto &s){
		s.addButton("quit");
	});

	auto race = create<Race>();
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