#include <limits>
#include <algorithm>
#include <set>

#include "../Swapchain.hpp"
#include "../Misc.hpp"
#include "util.hpp"

namespace Subtile {
namespace Vk {

VkImageView Swapchain::Image::createImageView(void)
{
	VkImageView res;
	VkImageViewCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.image = image;
	createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	createInfo.format = swapchain.surfaceFormat.format;
	createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	createInfo.subresourceRange.baseMipLevel = 0;
	createInfo.subresourceRange.levelCount = 1;
	createInfo.subresourceRange.baseArrayLayer = 0;
	createInfo.subresourceRange.layerCount = 1;

	vkAssert(vkCreateImageView(getDevice(), &createInfo, nullptr, &res));
	return res;
}

VkFramebuffer Swapchain::Image::createFramebuffer(void)
{
	VkFramebuffer res;
	VkFramebufferCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.renderPass = swapchain.renderPass;
	auto attachments = std::vector<VkImageView>{view};
	createInfo.attachmentCount = attachments.size();
	createInfo.pAttachments = attachments.data();
	createInfo.width = swapchain.extent.width;
	createInfo.height = swapchain.extent.height;
	createInfo.layers = 1;

	vkAssert(vkCreateFramebuffer(getDevice(), &createInfo, nullptr, &res));
	return res;
}

Swapchain::Image::Image(Swapchain &swapchain, VkImage image) :
	Dep::Device(swapchain.getDevice()),
	swapchain(swapchain),
	image(image),
	view(createImageView()),
	framebuffer(createFramebuffer())
{
}

Swapchain::Image::Image(Swapchain::Image &&other) :
	Dep::Device(other.getDevice()),
	swapchain(other.swapchain),
	image(other.image),
	view(other.view),
	framebuffer(other.framebuffer)
{
	other.image = VK_NULL_HANDLE;
	other.view = VK_NULL_HANDLE;
	other.framebuffer = VK_NULL_HANDLE;
}

Swapchain::Image::~Image(void)
{
	vkDestroyFramebuffer(getDevice(), framebuffer, nullptr);
	vkDestroyImageView(getDevice(), view, nullptr);
}

}
}