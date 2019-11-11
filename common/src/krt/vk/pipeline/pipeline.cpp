
#include "../vk.hpp"

VkPipelineVertexInputStateCreateInfo Pipeline::createVertexInputState(void)
{
	VkPipelineVertexInputStateCreateInfo res;

	res.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	res.pNext = nullptr;
	res.flags = 0;
	res.vertexBindingDescriptionCount = 0;
	res.pVertexBindingDescriptions = nullptr;
	res.vertexAttributeDescriptionCount = 0;
	res.pVertexAttributeDescriptions = nullptr;

	return res;
}

VkPipelineInputAssemblyStateCreateInfo Pipeline::createInputAssemblyState(void)
{
	VkPipelineInputAssemblyStateCreateInfo res;

	res.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	res.pNext = nullptr;
	res.flags = 0;
	res.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	res.primitiveRestartEnable = VK_FALSE;

	return res;
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

VkPipelineRasterizationStateCreateInfo Pipeline::createRasterizationState(void)
{
	VkPipelineRasterizationStateCreateInfo res;

	res.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	res.pNext = nullptr;
	res.flags = 0;
	res.depthClampEnable = VK_FALSE;
	res.rasterizerDiscardEnable = VK_FALSE;
	res.polygonMode = VK_POLYGON_MODE_FILL;
	res.cullMode = VK_CULL_MODE_BACK_BIT;
	res.frontFace = VK_FRONT_FACE_CLOCKWISE;
	res.depthBiasEnable = VK_FALSE;
	res.depthBiasConstantFactor = 0.0f;
	res.depthBiasClamp = 0.0f;
	res.depthBiasSlopeFactor = 0.0f;
	res.lineWidth = 1.0f;

	return res;
}

VkPipelineMultisampleStateCreateInfo Pipeline::createMultisampleState(void)
{
	VkPipelineMultisampleStateCreateInfo res;

	res.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	res.pNext = nullptr;
	res.flags = 0;
	res.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	res.sampleShadingEnable = VK_FALSE;
	res.minSampleShading = 1.0f;
	res.pSampleMask = nullptr;
	res.alphaToCoverageEnable = VK_FALSE;
	res.alphaToOneEnable = VK_FALSE;

	return res;
}

VkPipelineColorBlendAttachmentState Pipeline::createColorBlendAttachmentState(void)
{
	VkPipelineColorBlendAttachmentState res;

	res.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	res.blendEnable = VK_FALSE;
	res.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
	res.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	res.colorBlendOp = VK_BLEND_OP_ADD;
	res.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	res.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	res.alphaBlendOp = VK_BLEND_OP_ADD;

	return res;
}

VkPipelineColorBlendStateCreateInfo Pipeline::createColorBlendState(std::vector<VkPipelineColorBlendAttachmentState> &colorBlendAttachmentStates)
{
	VkPipelineColorBlendStateCreateInfo res;

	res.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	res.pNext = nullptr;
	res.flags = 0;
	res.logicOpEnable = VK_FALSE;
	res.logicOp = VK_LOGIC_OP_COPY;
	res.attachmentCount = colorBlendAttachmentStates.size();
	res.pAttachments = colorBlendAttachmentStates.data();
	for (size_t i = 0; i < 4; i++)
		res.blendConstants[i] = 0.0f;

	return res;
}

VkPipelineDynamicStateCreateInfo Pipeline::createDynamicState(std::vector<VkDynamicState> &dynamicStates)
{
	VkPipelineDynamicStateCreateInfo res;

	res.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	res.pNext = nullptr;
	res.flags = 0;
	res.dynamicStateCount = dynamicStates.size();
	res.pDynamicStates = dynamicStates.data();

	return res;
}

VkPipelineLayout Pipeline::createLayout(void)
{
	VkPipelineLayout res;
	VkPipelineLayoutCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.setLayoutCount = 0;
	createInfo.pSetLayouts = nullptr;
	createInfo.pushConstantRangeCount = 0;
	createInfo.pPushConstantRanges = nullptr;

	vkAssert(vkCreatePipelineLayout(vk.device.device, &createInfo, nullptr, &res));

	return res;
}

VkPipeline Pipeline::createPipeline(std::vector<ShaderStageCreateInfo> &stages)
{
	VkPipeline res;
	VkGraphicsPipelineCreateInfo createInfo;

	Pipeline::ShaderStages shaderStages(vk, stages);
	createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.stageCount = shaderStages.createInfos.size();
	createInfo.pStages = shaderStages.createInfos.data();
	auto vertexInputState = createVertexInputState();
	createInfo.pVertexInputState = &vertexInputState;
	auto inputAssemblyState = createInputAssemblyState();
	createInfo.pInputAssemblyState = &inputAssemblyState;
	createInfo.pTessellationState = nullptr;
	auto viewports = std::vector<VkViewport>{createViewport()};
	auto scissors = std::vector<VkRect2D>{createScissor()};
	auto viewportState = createViewportState(viewports, scissors);
	createInfo.pViewportState = &viewportState;
	auto rasterizationState = createRasterizationState();
	createInfo.pRasterizationState = &rasterizationState;
	auto multisampleState = createMultisampleState();
	createInfo.pMultisampleState = &multisampleState;
	createInfo.pDepthStencilState = nullptr;
	auto colorBlendAttachmentStates = std::vector<VkPipelineColorBlendAttachmentState>{createColorBlendAttachmentState()};
	auto colorBlendState = createColorBlendState(colorBlendAttachmentStates);
	createInfo.pColorBlendState = &colorBlendState;
	auto dynamicStates = std::vector<VkDynamicState>{VK_DYNAMIC_STATE_VIEWPORT};
	auto dynamicState = createDynamicState(dynamicStates);
	createInfo.pDynamicState = &dynamicState;
	createInfo.layout = layout;
	createInfo.renderPass = vk.swapchain.renderPass;
	createInfo.subpass = 0;
	createInfo.basePipelineHandle = VK_NULL_HANDLE;
	createInfo.basePipelineIndex = -1;

	vkAssert(vkCreateGraphicsPipelines(vk.device.device, VK_NULL_HANDLE, 1, &createInfo, nullptr, &res));

	return res;
}

Pipeline::Pipeline(Vk &vk, std::vector<ShaderStageCreateInfo> &&stages) :
	vk(vk),
	layout(createLayout()),
	pipeline(createPipeline(stages))
{
}

Pipeline::~Pipeline(void)
{
	vkDestroyPipeline(vk.device.device, pipeline, nullptr);
	vkDestroyPipelineLayout(vk.device.device, layout, nullptr);
}
