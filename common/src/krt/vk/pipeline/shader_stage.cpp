
#include "../vk.hpp"

Pipeline::ShaderStage::ShaderStage(Vk &vk, std::string path, VkShaderStageFlagBits stage) :
	name(path),
	module(ShaderModule(vk, path))
{
	VkPipelineShaderStageCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.stage = stage;
	createInfo.module = module.module;
	createInfo.pName = name.c_str();
	createInfo.pSpecializationInfo = nullptr;
}

Pipeline::ShaderStage::~ShaderStage(void)
{
}
