#include "Krt.hpp"
#include "util.hpp"

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