#pragma once

#include <vulkan/vulkan.h>

#include "Dep/VulkanDevice.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {

class Fence : public Dep::VulkanDevice
{
public:
	Fence(VkDevice dev);
	Fence(Fence &&other);
	~Fence(void);

	VkFence fence;

private:
	VkFence createFence(void);
};

}
}
}