#pragma once

#include <vulkan/vulkan.h>
#include "Device.hpp"

#include "Dep/VulkanDevice.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {

class Queue : public Dep::VulkanDevice
{
public:
	Queue(Device &dev, uint32_t queueFamilyIndex);
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
}
}