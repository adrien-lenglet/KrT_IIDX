#pragma once

#include <string>
#include "Dep/Device.hpp"

namespace Vk {

class ShaderModule : Dep::Device
{
public:
	ShaderModule(VkDevice dev, std::string path);
	~ShaderModule(void);

	VkShaderModule module;
};

}