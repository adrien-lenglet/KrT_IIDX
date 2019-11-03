
#pragma once

class QueueFamilies
{
public:
	QueueFamilies();
	QueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
	QueueFamilies(Vk &vk);
	~QueueFamilies(void);

	VkQueueFlags getSupportedFlags(void);
	int isPresentationSupported(void);
	int areQueuesSupported(void);
	uint32_t getIndex(VkQueueFlags flags);
	uint32_t getIndexPresent(void);
private:
	VkPhysicalDevice physicalDevice;
	VkSurfaceKHR surface;
	std::vector<VkQueueFamilyProperties> families;
	void updateFamilies(void);
};
