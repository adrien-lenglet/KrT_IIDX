
#pragma once

#include <string>
#include <vector>

#include "vk/vk.hpp"
#include "renderer/renderer.hpp"

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
	Vk vk;
	Renderer renderer;
	private:
};
