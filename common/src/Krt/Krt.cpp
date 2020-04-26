#include "Krt.hpp"
#include "Krt/EntityTest.hpp"
#include "Krt/Track.hpp"
#include "util.hpp"

#include <iostream>

namespace Krt {

Instance::Instance(std::vector<std::string> args, bool isDebug) :
	config(args),
	subtile(1600, 900, isDebug, config.isProfile)
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

	auto world = subtile.add<Track>();
	subtile.run();
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