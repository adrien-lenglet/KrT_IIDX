#pragma once

#include <vulkan/vulkan.h>
#include "vk_mem_alloc.h"
#include "QueueFamilies.hpp"

namespace Subtile {
namespace Vk {

class Device
{
public:
	Device(VkInstance instance, VkSurfaceKHR surface);
	~Device(void);

	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	QueueFamilies queueFamilies;
	VkDevice device;
	VmaAllocator allocator;

	VkQueue getQueue(uint32_t familyIndex, uint32_t index);

private:
	static bool areExtensionsSupported(VkPhysicalDevice device);
	VkPhysicalDevice createPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
	VkPhysicalDeviceProperties getPhysicalDeviceProperties(void);
	VkPhysicalDeviceFeatures getPhysicalDeviceFeatures(void);
	VkDevice createDevice(void);
	VmaAllocator createAllocator(void);
};

}
}