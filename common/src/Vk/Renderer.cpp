#include "Renderer.hpp"
#include "Vk/Misc.hpp"

namespace Vk {

VkCommandBuffer Renderer::Image::createCommandBuffer(void)
{
	VkCommandBuffer res;
	VkCommandBufferAllocateInfo allocInfo;

	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.commandPool = swapchainImage.swapchain.getQueue().commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	vkAssert(vkAllocateCommandBuffers(swapchainImage.swapchain.getDevice(), &allocInfo, &res));

	return res;
}

Renderer::Image::Image(Swapchain::Image &swapchainImage) :
	swapchainImage(swapchainImage),
	commandBuffer(createCommandBuffer()),
	imageAvailable(swapchainImage.swapchain.getDevice()),
	renderFinished(swapchainImage.swapchain.getDevice()),
	inFlight(swapchainImage.swapchain.getDevice()),
	imageInFlight(VK_NULL_HANDLE)
{
}

Renderer::Image::Image(Renderer::Image &&that) :
	swapchainImage(that.swapchainImage),
	commandBuffer(that.commandBuffer),
	imageAvailable(std::move(that.imageAvailable)),
	renderFinished(std::move(that.renderFinished)),
	inFlight(std::move(that.inFlight)),
	imageInFlight(that.imageInFlight)
{
	that.commandBuffer = VK_NULL_HANDLE;
}

Renderer::Image::~Image(void)
{
	vkFreeCommandBuffers(swapchainImage.swapchain.getDevice(), swapchainImage.swapchain.getQueue().commandPool, 1, &commandBuffer);
}

std::vector<Renderer::Image> Renderer::createImages(void)
{
	std::vector<Renderer::Image> res;

	for (auto &swapchainImage : swapchain.images)
		res.push_back(Renderer::Image(swapchainImage));
	return res;
}

Renderer::Renderer(Swapchain &swapchain, Queue &presentationQueue) :
	swapchain(swapchain),
	presentationQueue(presentationQueue),
	pipeline(swapchain, std::vector<Pipeline::ShaderStageCreateInfo>{
		{VK_SHADER_STAGE_VERTEX_BIT, "common/shaders/vert.spv"},
		{VK_SHADER_STAGE_FRAGMENT_BIT, "common/shaders/frag.spv"}
	}),
	images(createImages()),
	currentImage(0)
{
}

Renderer::~Renderer(void)
{
}

uint32_t Renderer::nextImage(void)
{
	uint32_t index;

	vkAssert(vkAcquireNextImageKHR(swapchain.getDevice(), swapchain.swapchain, UINT64_MAX, images[currentImage].imageAvailable.semaphore, VK_NULL_HANDLE, &index));
	return index;
}

void Renderer::render(void)
{
	vkWaitForFences(swapchain.getDevice(), 1, &images[currentImage].inFlight.fence, VK_TRUE, UINT64_MAX);

	auto imageIndex = nextImage();
	auto &image = images[currentImage];

	if (images[imageIndex].imageInFlight != VK_NULL_HANDLE)
		vkWaitForFences(swapchain.getDevice(), 1, &images[imageIndex].imageInFlight, VK_TRUE, UINT64_MAX);
	images[imageIndex].imageInFlight = images[currentImage].inFlight.fence;

	VkCommandBufferBeginInfo beginInfo;
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.pNext = nullptr;
	beginInfo.flags = 0;
	beginInfo.pInheritanceInfo = nullptr;
	vkAssert(vkBeginCommandBuffer(image.commandBuffer, &beginInfo));

	VkRenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.pNext = nullptr;
	renderPassInfo.renderPass = swapchain.renderPass;
	renderPassInfo.framebuffer = image.swapchainImage.framebuffer;
	renderPassInfo.renderArea.offset = {0, 0};
	renderPassInfo.renderArea.extent = swapchain.extent;
	VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	vkCmdBeginRenderPass(image.commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	vkCmdBindPipeline(image.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.pipeline);
	vkCmdDraw(image.commandBuffer, 3, 1, 0, 0);
	vkCmdEndRenderPass(image.commandBuffer);
	vkAssert(vkEndCommandBuffer(image.commandBuffer));

	VkSubmitInfo submitInfo;
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pNext = nullptr;
	VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &image.imageAvailable.semaphore;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &image.commandBuffer;
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &image.renderFinished.semaphore;
	vkResetFences(swapchain.getDevice(), 1, &images[currentImage].inFlight.fence);
	vkAssert(vkQueueSubmit(swapchain.getQueue().queue, 1, &submitInfo, image.inFlight.fence));

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pNext = nullptr;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &image.renderFinished.semaphore;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &swapchain.swapchain;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr;
	vkAssert(vkQueuePresentKHR(presentationQueue.queue, &presentInfo));

	currentImage = (currentImage + 1) % images.size();
}

}