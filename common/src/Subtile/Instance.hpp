#pragma once

#include "Vk/Instance.hpp"

namespace Subtile {

class Instance
{
public:
	Instance(size_t w, size_t h, bool isDebug, bool isProfile);
	~Instance(void);

	void run(void);

private:
	Vk::Instance vk;
};

}