
#include <iostream>
#include <exception>

#include <cstdio>

#include "vk.hpp"

void vkAssert_real(VkResult res, const char *file, int line, const char *fun)
{
	if (res != VK_SUCCESS)
		throw std::runtime_error(std::string(file) + "("+ std::to_string(line) + ") in " + std::string(fun) + "() got VkResult: " + std::to_string(res));
}

Vk::Vk(Krt &krt) :
	krt(krt),
	context(Context(*this, 1600, 900)),
	device(Device(*this)),
	queues(Queues(*this)),
	swapchain(Swapchain(*this))
{
	printf("Vk init done.\n");
}

Vk::~Vk(void)
{
}
