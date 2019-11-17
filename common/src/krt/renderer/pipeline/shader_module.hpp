
#pragma once

class ShaderModule
{
public:
	ShaderModule(Vk &vk, std::string path);
	~ShaderModule(void);

	VkShaderModule module;

private:
	Vk &vk;
};
