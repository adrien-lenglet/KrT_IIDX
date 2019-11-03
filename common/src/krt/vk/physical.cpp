
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
	std::vector<bool> extAvailable(desiredExt.size(), 0);

	uint32_t count = 0;
	vkAssert(vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr));
	std::vector<VkExtensionProperties> ext(count);
	vkAssert(vkEnumerateDeviceExtensionProperties(device, nullptr, &count, ext.data()));

	for (size_t i = 0; i < desiredExt.size(); i++)
		for (uint32_t j = 0; j < count; j++)
			if (strcmp(desiredExt[i], ext[j].extensionName) == 0)
				extAvailable[i] = 1;
	for (auto avail : extAvailable)
		if (!avail)
			return 0;
	return 1;
}

static bool isPhysicalDeviceCapable(VkPhysicalDevice device)
{
	if (!areExtensionsSupported(device))
		return 0;
	return 1;
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
		if (isPhysicalDeviceCapable(device) && queueFamilies.areQueuesSupported()) {
			res = device;
			if (properties.deviceType & VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
				return res;
		}
	}
	if (res == VK_NULL_HANDLE)
		throw std::runtime_error("Cannot find any compatible GPU on this system");
	return res;
}

VkPhysicalDevice Vk::createPhysicalDevice(void)
{
	return findBestPhysicalDevice(surface, instance);
}

VkPhysicalDeviceProperties Vk::getPhysicalDeviceProperties(void)
{
	VkPhysicalDeviceProperties res;

	vkGetPhysicalDeviceProperties(physicalDevice, &res);
	return res;
}

VkPhysicalDeviceFeatures Vk::getPhysicalDeviceFeatures(void)
{
	VkPhysicalDeviceFeatures res;

	vkGetPhysicalDeviceFeatures(physicalDevice, &res);
	return res;
}
