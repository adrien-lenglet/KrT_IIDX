
#include "krt/krt.hpp"

Krt::Krt(std::vector<std::string> args) : config(Config(args)), vk(Vk(*this))
{
}

Krt::~Krt(void)
{
}

void Krt::run(void)
{
}

static bool areArgsContainingString(std::vector<std::string> &args, std::string str)
{
	for (auto arg : args)
		if (arg == str)
			return true;
	return false;
}

Krt::Config::Config(std::vector<std::string> &args)
{
	isProfile = areArgsContainingString(args, "profile");
}

Krt::Config::~Config(void)
{
}
