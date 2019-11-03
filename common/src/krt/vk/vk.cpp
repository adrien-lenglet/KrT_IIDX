
#include <iostream>
#include <exception>

#include <cstdio>

#include "vk.hpp"

void vkAssert_real(VkResult res, const char *file, int line, const char *fun)
{
	if (res != VK_SUCCESS)
		throw std::runtime_error(std::string(file) + "("+ std::to_string(line) + ") in " + std::string(fun) + "() got VkResult: " + std::to_string(res));
}

void Vk::initSurface(void)
{
	vkAssert(glfwCreateWindowSurface(this->instance, this->glfw.window, nullptr, &this->surface));
}

Vk::Vk(Krt &krt) : krt(krt), glfw(Glfw(1600, 900))
{
	initInstance();
	initValidationLayers();
	initSurface();
	initPhysicalDevice();
	initDevice();

	printf("Vk init done.\n");
}

Vk::~Vk(void)
{
	vkDestroyDevice(this->device, nullptr);
	#ifdef DEBUG
	vkDestroyDebugUtilsMessengerEXT(this->instance, this->debugMessenger, nullptr);
	#endif
	vkDestroyInstance(this->instance, nullptr);
	printf("Vk destr done.\n");
}
