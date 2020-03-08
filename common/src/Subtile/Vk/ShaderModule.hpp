#pragma once

#include <string>
#include "Dep/Device.hpp"

namespace Subtile {
namespace Vk {

class ShaderModule : Dep::Device
{
public:
	ShaderModule(VkDevice dev, std::string path);
	~ShaderModule(void);

	VkShaderModule module;
};

}
}