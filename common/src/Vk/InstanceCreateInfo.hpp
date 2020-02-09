#pragma once

#include <vector>
#include <vulkan/vulkan.h>

namespace Vk {

class InstanceCreateInfo
{
public:
	InstanceCreateInfo(bool isProfile);
	~InstanceCreateInfo(void);

	bool isProfile;
	std::vector<const char*> layers;
	std::vector<const char*> extensions;
	VkApplicationInfo applicationInfo;
	VkInstanceCreateInfo createInfo;

private:
	std::vector<const char*> getLayers(bool isProfile);
	std::vector<const char*> getExtensions(void);
	VkApplicationInfo getApplicationInfo(void);
	VkInstanceCreateInfo getInstanceCreateInfo(const VkApplicationInfo &applicationInfo, std::vector<const char*> &layers, std::vector<const char*> &extensions);
};

}