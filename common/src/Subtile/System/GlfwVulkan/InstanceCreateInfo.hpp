#pragma once

#include <vector>
#include <vulkan/vulkan.h>

namespace Subtile {
namespace System {
namespace GlfwVulkan {

class InstanceCreateInfo
{
public:
	InstanceCreateInfo(bool isDebug, bool isProfile);
	~InstanceCreateInfo(void);

	bool isProfile;
	std::vector<const char*> layers;
	std::vector<const char*> extensions;
	VkApplicationInfo applicationInfo;
	VkInstanceCreateInfo createInfo;

private:
	std::vector<const char*> getLayers(bool isDebug, bool isProfile);
	std::vector<const char*> getExtensions(bool isDebug);
	VkApplicationInfo getApplicationInfo(void);
	VkInstanceCreateInfo getInstanceCreateInfo(const VkApplicationInfo &applicationInfo, std::vector<const char*> &layers, std::vector<const char*> &extensions);
};

}
}
}