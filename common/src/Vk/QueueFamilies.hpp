#pragma once

#include <vector>
#include <vulkan/vulkan.h>

namespace Vk {

class QueueFamilies
{
public:
	QueueFamilies(void);
	QueueFamilies(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice);
	~QueueFamilies(void);

	std::vector<VkQueueFamilyProperties> families;

	VkQueueFlags getSupportedFlags(void);
	int isPresentationSupported(void);
	int areQueuesSupported(void);
	uint32_t getIndex(VkQueueFlags flags);
	uint32_t getIndexPresent(void);

private:
	VkSurfaceKHR surface;
	VkPhysicalDevice physicalDevice;
};

}