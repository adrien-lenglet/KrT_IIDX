#pragma once

#include <vector>
#include <string>

#include "Subtile/Instance.hpp"

namespace Krt {

class Config {
public:
	Config(const std::vector<std::string> &args);
	~Config(void);

	bool isProfile = false;
};

class Instance : private Config, public sb::Instance<Instance>
{
public:
	Instance(bool isDebug, const std::vector<std::string> &args);
	~Instance(void);

	void run(void);
};

}