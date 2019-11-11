
#pragma once

#include "../vk.hpp"

#include "shader_module.hpp"

class Pipeline
{
public:
	class ShaderStage {
	public:
		ShaderStage(Vk &vk, VkShaderStageFlagBits stage, std::string path, std::string entryPoint = "main");
		~ShaderStage(void);

		std::string name;
		VkShaderStageFlagBits stage;
		ShaderModule module;
		VkPipelineShaderStageCreateInfo createInfo;

	private:
		VkPipelineShaderStageCreateInfo initCreateInfo(void);
	};

	class ShaderStageCreateInfo {
	public:
		ShaderStageCreateInfo(VkShaderStageFlagBits stage, std::string path, std::string entryPoint = "main");
		~ShaderStageCreateInfo(void);

		VkShaderStageFlagBits stage;
		std::string path;
		std::string entryPoint;
	};

	class ShaderStages : public std::vector<ShaderStage>
	{
	public:
		ShaderStages(Vk &vk, std::vector<ShaderStageCreateInfo> &createInfos);

		std::vector<VkPipelineShaderStageCreateInfo> createInfos;

	private:
		std::vector<VkPipelineShaderStageCreateInfo> getCreateInfos(Vk &vk, std::vector<ShaderStageCreateInfo> &createInfos);
	};

	Pipeline(Vk &vk, std::vector<ShaderStageCreateInfo> &&stages);
	~Pipeline(void);

	Vk &vk;

	VkPipelineLayout layout;
	VkPipeline pipeline;

private:
	VkPipelineVertexInputStateCreateInfo createVertexInputState(void);
	VkPipelineInputAssemblyStateCreateInfo createInputAssemblyState(void);
	VkViewport createViewport(void);
	VkRect2D createScissor(void);
	VkPipelineViewportStateCreateInfo createViewportState(std::vector<VkViewport> &viewports, std::vector<VkRect2D> &scissors);
	VkPipelineRasterizationStateCreateInfo createRasterizationState(void);
	VkPipelineMultisampleStateCreateInfo createMultisampleState(void);
	VkPipelineColorBlendAttachmentState createColorBlendAttachmentState(void);
	VkPipelineColorBlendStateCreateInfo createColorBlendState(std::vector<VkPipelineColorBlendAttachmentState> &colorBlendAttachmentStates);
	VkPipelineDynamicStateCreateInfo createDynamicState(std::vector<VkDynamicState> &dynamicStates);
	VkPipelineLayout createLayout(void);
	VkPipeline createPipeline(std::vector<ShaderStageCreateInfo> &stages);
};
