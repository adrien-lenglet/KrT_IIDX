#pragma once

#include <vulkan/vulkan.h>

namespace Subtile {
namespace Vk {
namespace Dep {

class Device {
public:
	Device(VkDevice device);
	~Device(void) = default;

	VkDevice getDevice(void) const;

private:
	VkDevice m_device;
};

}
}
}