
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
	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;
	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	QueueFamilies queueFamilies;
	VkDevice device;
	Queues queues;

	VkQueue getDeviceQueue(uint32_t familyIndex, uint32_t index);

private:
	void init(void);
	VkInstance createInstance(void);
	VkDebugUtilsMessengerEXT createDebugMessenger(void);
	VkSurfaceKHR createSurface(void);
	VkPhysicalDevice createPhysicalDevice(void);
	VkPhysicalDeviceProperties getPhysicalDeviceProperties(void);
	VkPhysicalDeviceFeatures getPhysicalDeviceFeatures(void);
	VkDevice createDevice(void);
};
