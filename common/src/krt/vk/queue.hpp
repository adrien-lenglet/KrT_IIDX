
#pragma once

class QueueFamilies
{
public:
	QueueFamilies();
	QueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
	QueueFamilies(Vk &vk);
	~QueueFamilies(void);

	std::vector<VkQueueFamilyProperties> families;

	VkQueueFlags getSupportedFlags(void);
	int isPresentationSupported(void);
	int areQueuesSupported(void);
	uint32_t getIndex(VkQueueFlags flags);
	uint32_t getIndexPresent(void);

private:
	VkPhysicalDevice physicalDevice;
	VkSurfaceKHR surface;
	void updateFamilies(void);
};

class Queues
{
public:
	Queues(Vk &vk);
	~Queues(void);

	VkQueue present;
	VkQueue graphics;
	VkQueue transfer;
};
