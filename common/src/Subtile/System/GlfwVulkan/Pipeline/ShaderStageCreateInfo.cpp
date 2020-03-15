#include "../Pipeline.hpp"

namespace Subtile {
namespace Vk {

Pipeline::ShaderStageCreateInfo::ShaderStageCreateInfo(VkShaderStageFlagBits stage, std::string path, std::string entryPoint) :
	stage(stage),
	path(path),
	entryPoint(entryPoint)
{
}

Pipeline::ShaderStageCreateInfo::~ShaderStageCreateInfo(void)
{
}



Pipeline::ShaderStages::ShaderStages(VkDevice dev, std::vector<ShaderStageCreateInfo> &createInfos) :
	createInfos(getCreateInfos(dev, createInfos))
{
}

std::vector<VkPipelineShaderStageCreateInfo> Pipeline::ShaderStages::getCreateInfos(VkDevice dev, std::vector<ShaderStageCreateInfo> &createInfos)
{
	std::vector<VkPipelineShaderStageCreateInfo> res;

	reserve(createInfos.size());
	for (auto &createInfo : createInfos)
		emplace_back(dev, createInfo.stage, createInfo.path, createInfo.entryPoint);
	for (auto &stage : *this)
		res.push_back(stage.createInfo);
	return res;
}

}
}