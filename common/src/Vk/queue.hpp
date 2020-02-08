#pragma once

#include <vector>
#include <vulkan/vulkan.h>
#include "Vk/Device.hpp"

#include "Dep/Device.hpp"

namespace Vk {

class Queue : public Dep::Device
{
public:
	Queue(::Vk::Device &dev, uint32_t queueFamilyIndex);
	~Queue(void);

	uint32_t queueFamilyIndex;

	VkQueue queue;
	VkCommandPool commandPool;

private:
	VkCommandPool createCommandPool(void);
};

class Queues
{
public:
	Queues(Device &dev);
	~Queues(void);

	Queue present;
	Queue graphics;
	Queue transfer;
};

}