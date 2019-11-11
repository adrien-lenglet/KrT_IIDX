
#include <iostream>
#include <exception>
#include <set>

#include "vk.hpp"

class VkDeviceQueueCreateInfos : public std::vector<VkDeviceQueueCreateInfo>
{
public:
	VkDeviceQueueCreateInfos(Device &device);
	~VkDeviceQueueCreateInfos(void);
	std::vector<std::vector<float>> priorities;

private:
};

VkDeviceQueueCreateInfos::VkDeviceQueueCreateInfos(Device &device)
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

VmaAllocator Device::createAllocator(void)
{
	VmaAllocator res;
	VmaAllocatorCreateInfo createInfo;

	createInfo.flags = 0;
	createInfo.physicalDevice = physicalDevice;
	createInfo.device = device;
	createInfo.preferredLargeHeapBlockSize = 0;
	createInfo.pAllocationCallbacks = nullptr;
	createInfo.pDeviceMemoryCallbacks = nullptr;
	createInfo.frameInUseCount = 0;
	createInfo.pHeapSizeLimit = nullptr;
	createInfo.pVulkanFunctions = nullptr;
	createInfo.pRecordSettings = nullptr;

	vkAssert(vmaCreateAllocator(&createInfo, &res));

	return res;
}

VkDeviceQueueCreateInfos::~VkDeviceQueueCreateInfos(void)
{
}

Device::Device(Vk &vk) :
	physicalDevice(createPhysicalDevice(vk)),
	properties(getPhysicalDeviceProperties()),
	features(getPhysicalDeviceFeatures()),
	queueFamilies(QueueFamilies(vk)),
	device(createDevice()),
	allocator(createAllocator())
{
}

Device::~Device(void)
{
	vmaDestroyAllocator(allocator);
	vkDestroyDevice(device, nullptr);
}

VkDevice Device::createDevice(void)
{
	VkDevice res;
	VkDeviceCreateInfo createInfo;
	VkDeviceQueueCreateInfos queueCreateInfos(*this);
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
	createInfo.pEnabledFeatures = &features;

	vkAssert(vkCreateDevice(physicalDevice, &createInfo, nullptr, &res));
	return res;
}

VkQueue Device::getQueue(uint32_t familyIndex, uint32_t index)
{
	VkQueue res;

	vkGetDeviceQueue(device, familyIndex, index, &res);
	return res;
}
