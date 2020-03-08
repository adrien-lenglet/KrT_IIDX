#include <limits>
#include <algorithm>
#include <set>

#include "Swapchain.hpp"
#include "Misc.hpp"
#include "util.hpp"

namespace Subtile {
namespace Vk {

VkSurfaceCapabilitiesKHR Swapchain::getCapabilities(void)
{
	VkSurfaceCapabilitiesKHR res;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &res);
	return res;
}

Swapchain::Swapchain(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice) :
	Dep::Device(VK_NULL_HANDLE),
	physicalDevice(physicalDevice),
	surface(surface),
	capabilities(getCapabilities()),
	surfaceFormats(Vk::retrieve(vkGetPhysicalDeviceSurfaceFormatsKHR, physicalDevice, surface)),
	presentModes(Vk::retrieve(vkGetPhysicalDeviceSurfacePresentModesKHR, physicalDevice, surface)),
	extent(getExtent2D()),
	surfaceFormat(getSurfaceFormat()),
	presentMode(getPresentMode()),
	swapchain(VK_NULL_HANDLE),
	renderPass(VK_NULL_HANDLE),
	m_queue(nullptr)
{
}

Swapchain::Swapchain(VkSurfaceKHR surface, Vk::Device &dev, Queue &queue) :
	Dep::Device(dev.device),
	physicalDevice(dev.physicalDevice),
	surface(surface),
	capabilities(getCapabilities()),
	surfaceFormats(Vk::retrieve(vkGetPhysicalDeviceSurfaceFormatsKHR, physicalDevice, surface)),
	presentModes(Vk::retrieve(vkGetPhysicalDeviceSurfacePresentModesKHR, physicalDevice, surface)),
	extent(getExtent2D()),
	surfaceFormat(getSurfaceFormat()),
	presentMode(getPresentMode()),
	swapchain(createSwapchain(dev)),
	renderPass(createRenderPass()),
	images(fetchImages()),
	m_queue(&queue)
{
}

std::vector<Swapchain::Image> Swapchain::fetchImages(void)
{
	return util::map(Vk::retrieve(vkGetSwapchainImagesKHR, getDevice(), swapchain),
	std::function([this](const VkImage &img) { return Swapchain::Image(*this, img); }));
}

VkRenderPass Swapchain::createRenderPass(void)
{
	VkRenderPass res;

	std::vector<VkAttachmentDescription> attachments;
	std::vector<VkSubpassDescription> subpasses;
	std::vector<VkSubpassDependency> dependencies;

	VkAttachmentDescription attachment;
	attachment.flags = 0;
	attachment.format = surfaceFormat.format;
	attachment.samples = VK_SAMPLE_COUNT_1_BIT;
	attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	attachments.push_back(attachment);

	std::vector<VkAttachmentReference> colorAttachments;
	VkAttachmentReference attachmentReference;
	attachmentReference.attachment = 0;
	attachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	colorAttachments.push_back(attachmentReference);

	VkSubpassDescription subpass;
	subpass.flags = 0;
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.inputAttachmentCount = 0;
	subpass.pInputAttachments = nullptr;
	subpass.colorAttachmentCount = colorAttachments.size();
	subpass.pColorAttachments = colorAttachments.data();
	subpass.pResolveAttachments = nullptr;
	subpass.pDepthStencilAttachment = nullptr;
	subpass.preserveAttachmentCount = 0;
	subpass.pPreserveAttachments = nullptr;
	subpasses.push_back(subpass);

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	dependency.dependencyFlags = 0;
	dependencies.push_back(dependency);

	VkRenderPassCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.attachmentCount = attachments.size();
	createInfo.pAttachments = attachments.data();
	createInfo.subpassCount = subpasses.size();
	createInfo.pSubpasses = subpasses.data();
	createInfo.dependencyCount = dependencies.size();
	createInfo.pDependencies = dependencies.data();

	vkAssert(vkCreateRenderPass(getDevice(), &createInfo, nullptr, &res));

	return res;
}

Swapchain::~Swapchain(void)
{
	if (renderPass != VK_NULL_HANDLE)
		vkDestroyRenderPass(getDevice(), renderPass, nullptr);
	if (swapchain != VK_NULL_HANDLE)
		vkDestroySwapchainKHR(getDevice(), swapchain, nullptr);
}

bool Swapchain::isValid(void)
{
	return surfaceFormats.size() > 0 && presentModes.size() > 0;
}

Queue& Swapchain::getQueue(void) const
{
	if (m_queue == nullptr)
		throw std::runtime_error("No queue attached to swapchain");
	return *m_queue;
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
	for (auto surfaceFormat : surfaceFormats)
		if ((surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM) &&
		(surfaceFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR))
			return surfaceFormat;
	return surfaceFormats.at(0);
}

VkPresentModeKHR Swapchain::getPresentMode(void)
{
	for (const auto &mode : std::vector<VkPresentModeKHR>{VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR})
		if (util::contains(presentModes, mode))
			return mode;
	return presentModes.at(0);
}

uint32_t Swapchain::getMinImageCount(void)
{
	uint32_t res = capabilities.minImageCount + 1;

	if ((res > capabilities.maxImageCount) && (capabilities.maxImageCount > 0))
		res = capabilities.maxImageCount;
	return res;
}

VkSwapchainKHR Swapchain::createSwapchain(Vk::Device &device)
{
	VkSwapchainKHR res;
	VkSwapchainCreateInfoKHR createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.surface = surface;
	createInfo.minImageCount = getMinImageCount();
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	std::set<uint32_t> familyIndices = {device.queueFamilies.getIndex(VK_QUEUE_GRAPHICS_BIT), device.queueFamilies.getIndexPresent()};
	createInfo.imageSharingMode = familyIndices.size() > 1 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
	createInfo.queueFamilyIndexCount = familyIndices.size();
	createInfo.pQueueFamilyIndices = std::vector<uint32_t>(familyIndices.begin(), familyIndices.end()).data();
	createInfo.preTransform = capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	vkAssert(vkCreateSwapchainKHR(getDevice(), &createInfo, nullptr, &res));
	return res;
}

}
}