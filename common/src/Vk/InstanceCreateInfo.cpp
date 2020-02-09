#include <GLFW/glfw3.h>
#include "InstanceCreateInfo.hpp"
#include "Misc.hpp"
#include "util.hpp"

namespace Vk {

std::vector<const char*> InstanceCreateInfo::getLayers(bool isProfile)
{
	std::vector<const char*> wanted;
	auto layers = util::map(
		Vk::retrieve(vkEnumerateInstanceLayerProperties),
		std::function([](const VkLayerProperties &layer) -> std::string { return layer.layerName; }));

	#ifdef DEBUG
	wanted.push_back("VK_LAYER_KHRONOS_validation");
	wanted.push_back("VK_LAYER_LUNARG_monitor");
	#endif
	if (isProfile)
		wanted.push_back("VK_LAYER_RENDERDOC_Capture");

	auto not_present = util::not_contained(layers, wanted);
	if (!not_present.empty())
		throw std::runtime_error(std::string("Layers not found: " + util::join(not_present, std::string(", "))));

	return wanted;
}

std::vector<const char*> InstanceCreateInfo::getExtensions(void)
{
	std::vector<const char*> res;
	uint32_t extCount = 0;
	const char **ext = glfwGetRequiredInstanceExtensions(&extCount);

	if (ext == nullptr)
		throw std::runtime_error("Vulkan not supported");
	for (uint32_t i = 0; i < extCount; i++)
		res.push_back(ext[i]);
	#ifdef DEBUG
	res.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	#endif

	return res;
}

VkApplicationInfo InstanceCreateInfo::getApplicationInfo(void)
{
	VkApplicationInfo res;

	res.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	res.pNext = nullptr;
	res.pApplicationName = "KrT_IIDX";
	res.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
	res.pEngineName = "SUBtire";
	res.engineVersion = VK_MAKE_VERSION(0, 1, 0);
	res.apiVersion = VK_API_VERSION_1_1;

	return res;
}

VkInstanceCreateInfo InstanceCreateInfo::getInstanceCreateInfo(const VkApplicationInfo &applicationInfo, std::vector<const char*> &layers, std::vector<const char*> &extensions)
{
	VkInstanceCreateInfo res;

	res.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	res.pNext = nullptr;
	res.flags = 0;
	res.pApplicationInfo = &applicationInfo;
	res.enabledLayerCount = layers.size();
	res.ppEnabledLayerNames = layers.data();
	res.enabledExtensionCount = extensions.size();
	res.ppEnabledExtensionNames = extensions.data();

	return res;
}

InstanceCreateInfo::InstanceCreateInfo(bool isProfile) :
	isProfile(isProfile),
	layers(getLayers(isProfile)),
	extensions(getExtensions()),
	applicationInfo(getApplicationInfo()),
	createInfo(getInstanceCreateInfo(applicationInfo, layers, extensions))
{
}

InstanceCreateInfo::~InstanceCreateInfo(void)
{
}

}