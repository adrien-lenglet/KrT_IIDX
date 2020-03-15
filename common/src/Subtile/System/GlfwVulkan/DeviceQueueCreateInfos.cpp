#include "DeviceQueueCreateInfos.hpp"

namespace Subtile {
namespace Vk {

DeviceQueueCreateInfos::DeviceQueueCreateInfos(Device &device)
{
	for (size_t i = 0; i < device.queueFamilies.families.size(); i++) {
		VkDeviceQueueCreateInfo to_push;

		to_push.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		to_push.pNext = nullptr;
		to_push.flags = 0;
		to_push.queueFamilyIndex = i;
		to_push.queueCount = 1;
		priorities.push_back(std::vector<float>{1.0f});
		to_push.pQueuePriorities = priorities.back().data();
		push_back(to_push);
	}
}

DeviceQueueCreateInfos::~DeviceQueueCreateInfos(void)
{
}

}
}