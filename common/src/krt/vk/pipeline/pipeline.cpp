
#include "../vk.hpp"

VkPipelineVertexInputStateCreateInfo Pipeline::createVertexInput(void)
{
	VkPipelineVertexInputStateCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.vertexBindingDescriptionCount = 0;
	createInfo.pVertexBindingDescriptions = nullptr;
	createInfo.vertexAttributeDescriptionCount = 0;
	createInfo.pVertexAttributeDescriptions = nullptr;

	return createInfo;
}

VkPipelineInputAssemblyStateCreateInfo Pipeline::createInputAssembly(void)
{
	VkPipelineInputAssemblyStateCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	createInfo.primitiveRestartEnable = VK_FALSE;

	return createInfo;
}

VkViewport Pipeline::createViewport(void)
{
	VkViewport res;

	res.x = 0.0f;
	res.y = 0.0f;
	res.width = (float)vk.swapchain.extent.width;
	res.height = (float)vk.swapchain.extent.height;
	res.minDepth = 0.0f;
	res.maxDepth = 1.0f;

	return res;
}

VkRect2D Pipeline::createScissor(void)
{
	VkRect2D res;

	res.offset.x = 0;
	res.offset.y = 0;
	res.extent = vk.swapchain.extent;

	return res;
}

VkPipelineViewportStateCreateInfo Pipeline::createViewportState(std::vector<VkViewport> &viewports, std::vector<VkRect2D> &scissors)
{
	VkPipelineViewportStateCreateInfo res;

	res.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	res.pNext = nullptr;
	res.flags = 0;
	res.viewportCount = viewports.size();
	res.pViewports = viewports.data();
	res.scissorCount = scissors.size();
	res.pScissors = scissors.data();

	return res;
}

Pipeline::Pipeline(Vk &vk) :
	vk(vk)
{
}

Pipeline::~Pipeline(void)
{
}
