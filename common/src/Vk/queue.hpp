#pragma once

namespace Vk {

class QueueFamilies
{
public:
	QueueFamilies();
	QueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
	QueueFamilies(Instance &vk);
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

class Queue
{
public:
	Queue(Instance &vk, uint32_t queueFamilyIndex);
	~Queue(void);

	Instance &vk;
	uint32_t queueFamilyIndex;

	VkQueue queue;
	VkCommandPool commandPool;

private:
	VkCommandPool createCommandPool(void);
};

class Queues
{
public:
	Queues(Instance &vk);
	~Queues(void);

	Queue present;
	Queue graphics;
	Queue transfer;
};

}