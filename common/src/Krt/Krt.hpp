#pragma once

#include <vector>
#include <string>

#include "Subtile/Instance.hpp"

namespace Krt {

class Instance : public sb::Instance
{
	class Config {
	public:
		Config(std::vector<std::string> args);
		~Config(void);

		bool isProfile;
	};

public:
	Instance(std::vector<std::string> args, bool isDebug);
	~Instance(void);

	void run(void);

	using World = sb::World<Instance>;
	using Session = sb::Session;

private:
	Config config;
};

}