#pragma once

#include <vulkan/vulkan.h>
#include "Device.hpp"

namespace Subtile {
namespace Vk {

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