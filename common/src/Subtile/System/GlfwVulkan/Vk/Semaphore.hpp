#pragma once

#include <vulkan/vulkan.h>

#include "Dep/VulkanDevice.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {

class Semaphore : public Dep::VulkanDevice
{
public:
	Semaphore(VkDevice dev);
	Semaphore(Semaphore &&other);
	~Semaphore(void);

	VkSemaphore semaphore;

private:
	VkSemaphore createSemaphore(void);
};

}
}
}