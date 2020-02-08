#include <algorithm>
#include "krt/krt.hpp"

Krt::Krt(std::vector<std::string> args) :
	config(args),
	vk(config.isProfile),
	renderer(vk)
{
}

Krt::~Krt(void)
{
}

void Krt::run(void)
{
}

Krt::Config::Config(std::vector<std::string> &args)
{
	isProfile = std::find(args.begin(), args.end(), "profile") != args.end();
}

Krt::Config::~Config(void)
{
}
