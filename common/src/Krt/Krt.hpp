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

class Instance : public sb::Instance<Instance>
{
	static inline constexpr auto m_graphics_family = sb::Queue::Flag::Graphics | sb::Queue::Flag::Present;

public:
	Instance(bool isDebug, const std::vector<std::string> &args);
	~Instance(void);

	void run(void);

	sb::Queue::Handle<m_graphics_family> graphics;
	sb::Swapchain::Handle swapchain;
};

}