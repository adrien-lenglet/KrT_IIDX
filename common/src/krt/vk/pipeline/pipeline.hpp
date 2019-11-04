
#pragma once

#include "../vk.hpp"

#include "shader_module.hpp"

class Pipeline
{
public:
	class ShaderStage {
	public:
		ShaderStage(Vk &vk, std::string path, VkShaderStageFlagBits stage);
		~ShaderStage(void);

	private:
		std::string name;
		ShaderModule module;
	};

	Pipeline(Vk &vk);
	~Pipeline(void);

private:
	Vk &vk;

	VkPipelineVertexInputStateCreateInfo createVertexInput(void);
	VkPipelineInputAssemblyStateCreateInfo createInputAssembly(void);
	VkViewport createViewport(void);
	VkRect2D createScissor(void);
	VkPipelineViewportStateCreateInfo createViewportState(std::vector<VkViewport> &viewports, std::vector<VkRect2D> &scissors);
};
