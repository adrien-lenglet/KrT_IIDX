#include "VulkanDevice.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {
namespace Dep {

VulkanDevice::VulkanDevice(VkDevice device) :
	m_device(device)
{
}

VkDevice VulkanDevice::getDevice(void) const
{
	return m_device;
}

}
}
}
}