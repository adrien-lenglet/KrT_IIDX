
#pragma once

#include <vector>

#include <vulkan/vulkan.h>

class Vk;
class Krt;

#include "glfw.hpp"
#include "queue.hpp"

void vkAssert_real(VkResult res, const char *file, int line, const char *fun);
#define vkAssert(res) vkAssert_real(res, __FILE__, __LINE__, __func__)

class Vk
{
public:
	Vk(Krt &krt);
	~Vk(void);

	Krt &krt;

	Glfw glfw;

	VkInstance instance;
	VkSurfaceKHR surface;
	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	QueueFamilies queueFamilies;
	VkDevice device;

private:
	void initInstance(void);
	void initValidationLayers(void);
	void initSurface(void);
	void initPhysicalDevice(void);
	void initDevice(void);

	VkDebugUtilsMessengerEXT debugMessenger;
};
