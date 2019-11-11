
#include "../vk.hpp"

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

Pipeline::ShaderStage::ShaderStage(Vk &vk, VkShaderStageFlagBits stage, std::string path, std::string entryPoint) :
	name(entryPoint),
	stage(stage),
	module(ShaderModule(vk, path)),
	createInfo(initCreateInfo())
{
}

Pipeline::ShaderStage::~ShaderStage(void)
{
}

Pipeline::ShaderStageCreateInfo::ShaderStageCreateInfo(VkShaderStageFlagBits stage, std::string path, std::string entryPoint) :
	stage(stage),
	path(path),
	entryPoint(entryPoint)
{
}

Pipeline::ShaderStageCreateInfo::~ShaderStageCreateInfo(void)
{
}



Pipeline::ShaderStages::ShaderStages(Vk &vk, std::vector<ShaderStageCreateInfo> &createInfos) :
	createInfos(getCreateInfos(vk, createInfos))
{
}

std::vector<VkPipelineShaderStageCreateInfo> Pipeline::ShaderStages::getCreateInfos(Vk &vk, std::vector<ShaderStageCreateInfo> &createInfos)
{
	std::vector<VkPipelineShaderStageCreateInfo> res;

	reserve(createInfos.size());
	for (auto &createInfo : createInfos)
		emplace_back(vk, createInfo.stage, createInfo.path, createInfo.entryPoint);
	for (auto &stage : *this)
		res.push_back(stage.createInfo);

	return res;
}
