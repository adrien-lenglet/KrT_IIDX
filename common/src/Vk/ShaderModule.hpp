
#pragma once

namespace Vk {

class ShaderModule
{
public:
	ShaderModule(Instance &vk, std::string path);
	~ShaderModule(void);

	VkShaderModule module;

private:
	Instance &vk;
};

}