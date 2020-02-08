#pragma once

namespace Vk {

class Device
{
public:
	Device(Instance &vk);
	~Device(void);

	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	QueueFamilies queueFamilies;
	VkDevice device;
	VmaAllocator allocator;

	VkQueue getQueue(uint32_t familyIndex, uint32_t index);

private:
	VkPhysicalDevice createPhysicalDevice(Instance &vk);
	VkPhysicalDeviceProperties getPhysicalDeviceProperties(void);
	VkPhysicalDeviceFeatures getPhysicalDeviceFeatures(void);
	VkDevice createDevice(void);
	VmaAllocator createAllocator(void);
};

}