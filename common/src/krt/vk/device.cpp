
#include <iostream>
#include <exception>
#include <set>

#include "vk.hpp"

class vec_VkDeviceQueueCreateInfo : public std::vector<VkDeviceQueueCreateInfo>
{
public:
	vec_VkDeviceQueueCreateInfo(Vk &vk);
	~vec_VkDeviceQueueCreateInfo(void);
	std::vector<std::vector<float>> priorities;

private:
};

vec_VkDeviceQueueCreateInfo::vec_VkDeviceQueueCreateInfo(Vk &vk)
{
	for (size_t i = 0; i < vk.queueFamilies.families.size(); i++) {
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

vec_VkDeviceQueueCreateInfo::~vec_VkDeviceQueueCreateInfo(void)
{
}

VkDevice Vk::createDevice(void)
{
	VkDevice res;
	VkDeviceCreateInfo createInfo;
	vec_VkDeviceQueueCreateInfo queueCreateInfos(*this);
	std::vector<const char*> extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.queueCreateInfoCount = queueCreateInfos.size();
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;
	createInfo.enabledExtensionCount = extensions.size();
	createInfo.ppEnabledExtensionNames = extensions.data();
	createInfo.pEnabledFeatures = &this->features;

	vkAssert(vkCreateDevice(this->physicalDevice, &createInfo, nullptr, &res));
	return res;
}
