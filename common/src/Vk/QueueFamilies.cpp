#include <optional>
#include <bitset>
#include <iostream>
#include <exception>

#include "Queue.hpp"
#include "Misc.hpp"

namespace Vk {

QueueFamilies::QueueFamilies(void)
{
}

void QueueFamilies::updateFamilies(void)
{
	uint32_t count = 0;

	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);
	this->families.resize(count);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, this->families.data());
}

QueueFamilies::QueueFamilies(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice) :
	surface(surface),
	physicalDevice(physicalDevice)
{
	updateFamilies();
}

QueueFamilies::~QueueFamilies(void)
{
}

VkQueueFlags QueueFamilies::getSupportedFlags(void)
{
	VkQueueFlags res = 0;

	for (auto family : this->families)
		res |= family.queueFlags;
	return res;
}

int QueueFamilies::isPresentationSupported(void)
{
	for (size_t i = 0; i < families.size(); i++)
		if (families[i].queueCount > 0) {
			VkBool32 res;
			vkAssert(vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &res));
			if (res)
				return 1;
		}
	return 0;
}

int QueueFamilies::areQueuesSupported(void)
{
	VkQueueFlags supported = getSupportedFlags();

	return (supported & VK_QUEUE_GRAPHICS_BIT) && (supported & VK_QUEUE_TRANSFER_BIT) && isPresentationSupported();
}

uint32_t QueueFamilies::getIndex(VkQueueFlags flags)
{
	std::optional<uint32_t> res;
	std::optional<uint32_t> bestCount;

	for (size_t i = 0; i < this->families.size(); i++) {
		if (this->families[i].queueFlags & flags) {
			size_t bitCount = std::bitset<32>(this->families[i].queueFlags).count();
			if (!bestCount.has_value() || (bitCount < bestCount)) {
				res = i;
				bestCount = bitCount;
			}
		}
	}
	if (!res.has_value())
		throw std::runtime_error("Can't find any queue family matching these flags: " + std::to_string(flags));
	return *res;
}


uint32_t QueueFamilies::getIndexPresent(void)
{
	for (size_t i = 0; i < families.size(); i++)
		if (families[i].queueCount > 0) {
			VkBool32 res;
			vkAssert(vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &res));
			if (res)
				return i;
		}
	throw std::runtime_error("Can't find any queue family for presentation");
}

}