#include "Vk/Pipeline.hpp"

namespace Vk {

VkPipelineShaderStageCreateInfo Pipeline::ShaderStage::initCreateInfo(void)
{
	VkPipelineShaderStageCreateInfo res;

	res.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	res.pNext = nullptr;
	res.flags = 0;
	res.stage = stage;
	res.module = module.module;
	res.pName = name.c_str();
	res.pSpecializationInfo = nullptr;

	return res;
}

Pipeline::ShaderStage::ShaderStage(VkDevice dev, VkShaderStageFlagBits stage, std::string path, std::string entryPoint) :
	name(entryPoint),
	stage(stage),
	module(dev, path),
	createInfo(initCreateInfo())
{
}

Pipeline::ShaderStage::~ShaderStage(void)
{
}

}