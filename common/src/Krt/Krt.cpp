#include "Krt.hpp"
#include "Krt/EntityTest.hpp"
#include "Krt/Track.hpp"
#include "Krt/Race.hpp"
#include "util.hpp"

#include <iostream>

namespace Krt {

Instance::Instance(bool isDebug, const std::vector<std::string> &args) :
	sb::Instance<Instance>("SUNREN®", isDebug, Config(args).isProfile, {
		{sb::Queue::Flag::Graphics | sb::Queue::Flag::Present | sb::Queue::Flag::Transfer, {1.0f}}
	})
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

Config::Config(const std::vector<std::string> &argsRo)
{
	auto args = argsRo;

	if (util::erase_if_contains(args, "-p"))
		isProfile = true;
	if (util::erase_if_contains(args, "--profile"))
		isProfile = true;

	if (!args.empty())
		throw std::runtime_error(std::string("Unknown argument(s): " + util::join(args, std::string(", "))));
}

Config::~Config(void)
{
}

}