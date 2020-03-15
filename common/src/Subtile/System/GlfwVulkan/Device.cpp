#include "Device.hpp"
#include "Swapchain.hpp"
#include "DeviceQueueCreateInfos.hpp"
#include "Misc.hpp"
#include "util.hpp"

namespace Subtile {
namespace Vk {

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

Device::Device(VkInstance instance, VkSurfaceKHR surface) :
	physicalDevice(createPhysicalDevice(instance, surface)),
	properties(getPhysicalDeviceProperties()),
	features(getPhysicalDeviceFeatures()),
	queueFamilies(surface, physicalDevice),
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
	DeviceQueueCreateInfos queueCreateInfos(*this);
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

bool Device::areExtensionsSupported(VkPhysicalDevice device)
{
	std::vector<std::string> desiredExt = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
	auto ext = Vk::retrieve(vkEnumerateDeviceExtensionProperties, device, static_cast<const char*>(nullptr));

	for (const auto &e : ext)
		util::remove(desiredExt, e.extensionName);
	return desiredExt.empty();
}

VkPhysicalDevice Device::createPhysicalDevice(VkInstance instance, VkSurfaceKHR surface)
{
	auto devices = Vk::retrieve(vkEnumeratePhysicalDevices, instance);
	VkPhysicalDevice res = VK_NULL_HANDLE;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	QueueFamilies queueFamilies;

	for (auto device : devices) {
		vkGetPhysicalDeviceProperties(device, &properties);
		vkGetPhysicalDeviceFeatures(device, &features);
		queueFamilies = QueueFamilies(surface, device);
		if (areExtensionsSupported(device) && queueFamilies.areQueuesSupported() && Swapchain(surface, device).isValid()) {
			res = device;
			if (properties.deviceType & VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
				return res;
		}
	}
	if (res == VK_NULL_HANDLE)
		throw std::runtime_error("Cannot find any compatible GPU on this system");
	return res;
}

VkPhysicalDeviceProperties Device::getPhysicalDeviceProperties(void)
{
	VkPhysicalDeviceProperties res;

	vkGetPhysicalDeviceProperties(physicalDevice, &res);
	return res;
}

VkPhysicalDeviceFeatures Device::getPhysicalDeviceFeatures(void)
{
	VkPhysicalDeviceFeatures res;

	vkGetPhysicalDeviceFeatures(physicalDevice, &res);
	return res;
}

VkQueue Device::getQueue(uint32_t familyIndex, uint32_t index)
{
	VkQueue res;

	vkGetDeviceQueue(device, familyIndex, index, &res);
	return res;
}

}
}