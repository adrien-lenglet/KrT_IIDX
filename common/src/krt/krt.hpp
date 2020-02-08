
#pragma once

#include <string>
#include <vector>

#include "Vk/Instance.hpp"

class Krt
{
	class Config {
	public:
		Config(std::vector<std::string> &args);
		~Config(void);

		bool isProfile;
	};

	public:
	Krt(void);
	Krt(std::vector<std::string> args);
	~Krt(void);

	void run(void);

	Config config;
	Vk::Instance vk;
	//Renderer renderer;
	private:
};
