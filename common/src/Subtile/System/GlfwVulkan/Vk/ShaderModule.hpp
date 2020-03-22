#pragma once

#include <string>
#include "Dep/VulkanDevice.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {

class ShaderModule : Dep::VulkanDevice
{
public:
	ShaderModule(VkDevice dev, std::string path);
	~ShaderModule(void);

	VkShaderModule module;
};

}
}
}