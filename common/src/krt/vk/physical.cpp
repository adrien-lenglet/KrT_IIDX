
#include <iostream>
#include <exception>
#include <tuple>

#include <cstring>

#include "vk.hpp"

static std::vector<VkPhysicalDevice> getDevices(VkInstance instance)
{
	uint32_t count = 0;

	vkAssert(vkEnumeratePhysicalDevices(instance, &count, nullptr));
	std::vector<VkPhysicalDevice> res(count);
	vkAssert(vkEnumeratePhysicalDevices(instance, &count, res.data()));
	return res;
}

static bool areExtensionsSupported(VkPhysicalDevice device)
{
	std::vector<const char*> desiredExt = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
	std::vector<bool> extAvailable(desiredExt.size(), false);

	uint32_t count = 0;
	vkAssert(vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr));
	std::vector<VkExtensionProperties> ext(count);
	vkAssert(vkEnumerateDeviceExtensionProperties(device, nullptr, &count, ext.data()));

	for (size_t i = 0; i < desiredExt.size(); i++)
		for (uint32_t j = 0; j < count; j++)
			if (strcmp(desiredExt[i], ext[j].extensionName) == 0)
				extAvailable[i] = true;
	for (auto avail : extAvailable)
		if (!avail)
			return false;
	return true;
}

static VkPhysicalDevice findBestPhysicalDevice(VkSurfaceKHR surface, VkInstance instance)
{
	std::vector<VkPhysicalDevice> devices = getDevices(instance);
	VkPhysicalDevice res = VK_NULL_HANDLE;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	QueueFamilies queueFamilies;

	for (auto device : devices) {
		vkGetPhysicalDeviceProperties(device, &properties);
		vkGetPhysicalDeviceFeatures(device, &features);
		queueFamilies = QueueFamilies(device, surface);
		if (areExtensionsSupported(device) && queueFamilies.areQueuesSupported() && Swapchain(device, surface).isValid()) {
			res = device;
			if (properties.deviceType & VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
				return res;
		}
	}
	if (res == VK_NULL_HANDLE)
		throw std::runtime_error("Cannot find any compatible GPU on this system");
	return res;
}

VkPhysicalDevice Device::createPhysicalDevice(Context &context)
{
	return findBestPhysicalDevice(context.surface, context.instance);
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
