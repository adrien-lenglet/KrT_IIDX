#include <fstream>
#include "ShaderModule.hpp"
#include "Misc.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {

ShaderModule::ShaderModule(VkDevice dev, std::string path) :
	Dep::VulkanDevice(dev)
{
	auto file = std::ifstream(path, std::ios::ate | std::ios::binary);
	file.exceptions(std::ifstream::failbit);

	size_t size = file.tellg();
	file.seekg(0);
	std::vector<char> buf(size);
	file.read(buf.data(), size);
	file.close();

	VkShaderModuleCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.codeSize = buf.size();
	createInfo.pCode = (const uint32_t*)buf.data();

	vkAssert(vkCreateShaderModule(getDevice(), &createInfo, nullptr, &module));
}

ShaderModule::~ShaderModule(void)
{
	vkDestroyShaderModule(getDevice(), module, nullptr);
}

}
}
}