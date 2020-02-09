#include <exception>
#include <string>

#include "Device.hpp"
#include "Misc.hpp"
#include "Swapchain.hpp"
#include "util/algo.hpp"

namespace Vk {

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
	std::vector<std::string> desiredExt = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	uint32_t count = 0;
	vkAssert(vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr));
	std::vector<VkExtensionProperties> ext(count);
	vkAssert(vkEnumerateDeviceExtensionProperties(device, nullptr, &count, ext.data()));

	for (const auto &e : ext)
		util::remove(desiredExt, e.extensionName);
	return desiredExt.empty();
}

static VkPhysicalDevice findBestPhysicalDevice(VkInstance instance, VkSurfaceKHR surface)
{
	std::vector<VkPhysicalDevice> devices = getDevices(instance);
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

VkPhysicalDevice Device::createPhysicalDevice(VkInstance instance, VkSurfaceKHR surface)
{
	return findBestPhysicalDevice(instance, surface);
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

}