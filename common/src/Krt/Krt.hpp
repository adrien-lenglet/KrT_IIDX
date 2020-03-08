
#pragma once

#include <vector>
#include <string>

#include "Subtile/Instance.hpp"

#ifdef DEBUG
#define IS_DEBUG true
#else
#define IS_DEBUG false
#endif

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
	Instance(std::vector<std::string> args, bool isDebug = IS_DEBUG);
	~Instance(void);

	void run(void);

private:
	Config config;
	Subtile::Instance subtile;
};

}