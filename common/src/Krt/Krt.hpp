
#pragma once

#include <vector>
#include <string>

#include "Vk/Instance.hpp"

namespace Krt {

class Instance
{
	class Config {
	public:
		Config(std::vector<std::string> args);
		~Config(void);

		bool isProfile;
	};

public:
	Instance(std::vector<std::string> args);
	~Instance(void);

	void run(void);

	Config config;
	Vk::Instance vk;

private:
};

}