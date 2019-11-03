
#include <iostream>
#include <exception>

#include <cstdio>

#include "vk.hpp"

void vkAssert_real(VkResult res, const char *file, int line, const char *fun)
{
	if (res != VK_SUCCESS)
		throw std::runtime_error(std::string(file) + "("+ std::to_string(line) + ") in " + std::string(fun) + "() got VkResult: " + std::to_string(res));
}

VkSurfaceKHR Vk::createSurface(void)
{
	VkSurfaceKHR res;

	vkAssert(glfwCreateWindowSurface(instance, glfw.window, nullptr, &res));
	return res;
}

Vk::Vk(Krt &krt) :
	krt(krt),
	glfw(Glfw(1600, 900)),
	instance(createInstance()),
	debugMessenger(createDebugMessenger()),
	surface(createSurface()),
	physicalDevice(createPhysicalDevice()),
	properties(getPhysicalDeviceProperties()),
	features(getPhysicalDeviceFeatures()),
	queueFamilies(QueueFamilies(*this)),
	device(createDevice()),
	queues(Queues(*this))
{
	printf("Vk init done.\n");
}

Vk::~Vk(void)
{
	vkDestroyDevice(device, nullptr);
	#ifdef DEBUG
	vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	#endif
	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkDestroyInstance(instance, nullptr);
	printf("Vk destr done.\n");
}

VkQueue Vk::getDeviceQueue(uint32_t familyIndex, uint32_t index)
{
	VkQueue res;

	vkGetDeviceQueue(device, familyIndex, index, &res);
	return res;
}
