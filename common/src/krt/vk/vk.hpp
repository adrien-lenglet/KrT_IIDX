
#pragma once

#include <vector>

#include <vulkan/vulkan.h>

class Vk;

#include "glfw.hpp"
#include "queue.hpp"

void vkAssert_real(VkResult res, const char *file, int line, const char *fun);
#define vkAssert(res) vkAssert_real(res, __FILE__, __LINE__, __func__)

class VkInstanceCreateInfo_data
{
public:
	VkInstanceCreateInfo_data(void);
	~VkInstanceCreateInfo_data(void);

	std::vector<const char*> layers;
	std::vector<const char*> extensions;
	VkApplicationInfo applicationInfo;
	VkInstanceCreateInfo createInfo;

private:
};

class vec_VkDeviceQueueCreateInfo : public std::vector<VkDeviceQueueCreateInfo>
{
public:
	vec_VkDeviceQueueCreateInfo(Vk &vk);
	~vec_VkDeviceQueueCreateInfo(void);
	std::vector<std::vector<float>> priorities;

private:
};

class Vk
{
public:
	Vk(void);
	~Vk(void);

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
