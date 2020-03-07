#include "Renderer.hpp"
#include "Vk/Misc.hpp"

namespace Vk {

VkCommandBuffer Renderer::Image::createCommandBuffer(void)
{
	VkCommandBuffer res;
	VkCommandBufferAllocateInfo allocInfo;

	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.commandPool = swapchainImage.swapchain.getCommandPool();
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	vkAssert(vkAllocateCommandBuffers(swapchainImage.swapchain.getDevice(), &allocInfo, &res));

	return res;
}

Renderer::Image::Image(Swapchain::Image &swapchainImage) :
	swapchainImage(swapchainImage),
	commandBuffer(createCommandBuffer()),
	imageAvailable(swapchainImage.swapchain.getDevice()),
	renderFinished(swapchainImage.swapchain.getDevice())
{
}

Renderer::Image::Image(Renderer::Image &&that) :
	swapchainImage(that.swapchainImage),
	commandBuffer(that.commandBuffer),
	imageAvailable(std::move(that.imageAvailable)),
	renderFinished(std::move(that.renderFinished))
{
	that.commandBuffer = VK_NULL_HANDLE;
}

Renderer::Image::~Image(void)
{
	vkFreeCommandBuffers(swapchainImage.swapchain.getDevice(), swapchainImage.swapchain.getCommandPool(), 1, &commandBuffer);
}

std::vector<Renderer::Image> Renderer::Images::createImages(void)
{
	std::vector<Renderer::Image> res;

	for (auto &swapchainImage : swapchain.images)
		res.push_back(Renderer::Image(swapchainImage));
	return res;
}

Renderer::Images::Images(Swapchain &swapchain) :
	swapchain(swapchain),
	images(createImages())
{
}

Renderer::Images::~Images(void)
{
}

/*Renderer::Image& Renderer::Images::nextImage(void)
{
	uint32_t index;

	//vkAssert(vkAcquireNextImageKHR(swapchain.vk.device.device, swapchain.swapchain, UINT64_MAX, images, VK_NULL_HANDLE, &index));
}*/

Renderer::Renderer(Swapchain &swapchain) :
	pipeline(swapchain, std::vector<Pipeline::ShaderStageCreateInfo>{
		{VK_SHADER_STAGE_VERTEX_BIT, "common/shaders/vert.spv"},
		{VK_SHADER_STAGE_FRAGMENT_BIT, "common/shaders/frag.spv"}
	}),
	images(swapchain)
{
}

}