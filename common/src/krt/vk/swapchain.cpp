
#include <limits>
#include <algorithm>
#include <set>

#include "vk.hpp"

void Swapchain::updateCapabilities(void)
{
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities);
	uint32_t count;
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, nullptr);
	formats.resize(count);
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, formats.data());
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, nullptr);
	presentModes.resize(count);
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, presentModes.data());
}

Swapchain::Swapchain(Vk &vk, VkPhysicalDevice physicalDevice) :
	vk(vk),
	swapchain(VK_NULL_HANDLE),
	physicalDevice(physicalDevice),
	surface(vk.context.surface)
{
	updateCapabilities();
}

Swapchain::Swapchain(Vk &vk) :
	vk(vk),
	physicalDevice(vk.device.physicalDevice),
	surface(vk.context.surface)
{
	updateCapabilities();
	extent = getExtent2D();
	format = getSurfaceFormat();
	presentMode = getPresentMode();
	swapchain = createSwapchain();
}

Swapchain::~Swapchain(void)
{
	if (swapchain != VK_NULL_HANDLE)
		vkDestroySwapchainKHR(vk.device.device, swapchain, nullptr);
}

bool Swapchain::isValid(void)
{
	return formats.size() > 0 && presentModes.size() > 0;
}

VkExtent2D Swapchain::getExtent2D(void)
{
	if (capabilities.currentExtent.width != UINT32_MAX)
		return capabilities.currentExtent;
	else {
		VkExtent2D res = {1600, 900};

		res.width = std::clamp(res.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		res.height = std::clamp(res.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return res;
	}
}

VkSurfaceFormatKHR Swapchain::getSurfaceFormat(void)
{
	for (auto format : formats)
		if ((format.format == VK_FORMAT_B8G8R8A8_UNORM) &&
		(format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR))
			return format;
	return formats.at(0);
}

VkPresentModeKHR Swapchain::getPresentMode(void)
{
	for (auto presentMode : presentModes)
		if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			return presentMode;
	for (auto presentMode : presentModes)
		if (presentMode == VK_PRESENT_MODE_FIFO_KHR)
			return presentMode;
	return presentModes.at(0);
}

uint32_t Swapchain::getMinImageCount(void)
{
	uint32_t res = capabilities.minImageCount + 1;

	if ((res > capabilities.maxImageCount) && (capabilities.maxImageCount > 0))
		res = capabilities.maxImageCount;
	return res;
}

VkSwapchainKHR Swapchain::createSwapchain(void)
{
	VkSwapchainKHR res;
	VkSwapchainCreateInfoKHR createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.surface = surface;
	createInfo.minImageCount = getMinImageCount();
	createInfo.imageFormat = format.format;
	createInfo.imageColorSpace = format.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	std::set<uint32_t> familyIndices = {vk.device.queueFamilies.getIndex(VK_QUEUE_GRAPHICS_BIT), vk.device.queueFamilies.getIndexPresent()};
	createInfo.imageSharingMode = familyIndices.size() > 1 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
	createInfo.queueFamilyIndexCount = familyIndices.size();
	createInfo.pQueueFamilyIndices = std::vector<uint32_t>(familyIndices.begin(), familyIndices.end()).data();
	createInfo.preTransform = capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	vkAssert(vkCreateSwapchainKHR(vk.device.device, &createInfo, nullptr, &res));
	return res;
}
