#pragma once

#include <vulkan/vulkan.h>

namespace Subtile {
namespace System {
namespace GlfwVulkan {
namespace Dep {

class VulkanDevice
{
public:
	VulkanDevice(VkDevice device);
	~VulkanDevice(void) = default;

	VkDevice getDevice(void) const;

private:
	VkDevice m_device;
};

}
}
}
}