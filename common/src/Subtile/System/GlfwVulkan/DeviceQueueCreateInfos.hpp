#pragma once

#include <vulkan/vulkan.h>
#include "Device.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {

class DeviceQueueCreateInfos : public std::vector<VkDeviceQueueCreateInfo>
{
public:
	DeviceQueueCreateInfos(Device &device);
	~DeviceQueueCreateInfos(void);

	std::vector<std::vector<float>> priorities;

private:
};

}
}
}