
#include <iostream>
#include <exception>

#include "krt/krt.hpp"

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	(void)messageType;
	(void)pUserData;

	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
		std::cerr << "[VERBOSE]: ";
	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
		std::cerr << "[INFO]: ";
	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		std::cerr << "[WARNING]: ";
	if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
		std::cerr << "[ERROR]: ";
	std::cerr << pCallbackData->pMessage << std::endl;
	return VK_FALSE;
}

static std::vector<const char*> getLayers(bool isProfile)
{
	std::vector<const char*> res;

	#ifdef DEBUG
	uint32_t layerCount = 0;
	vkAssert(vkEnumerateInstanceLayerProperties(&layerCount, nullptr));
	std::vector<VkLayerProperties> layers(layerCount);
	vkAssert(vkEnumerateInstanceLayerProperties(&layerCount, layers.data()));

	res.push_back("VK_LAYER_KHRONOS_validation");
	res.push_back("VK_LAYER_LUNARG_monitor");
	#endif // DEBUG
	if (isProfile)
		res.push_back("VK_LAYER_RENDERDOC_Capture");
	return res;
}

static std::vector<const char*> getExtensions(void)
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
	#endif // DEBUG
	return res;
}

static VkApplicationInfo getApplicationInfo(void)
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

static VkInstanceCreateInfo getInstanceCreateInfo(const VkApplicationInfo *applicationInfo, std::vector<const char*> &layers, std::vector<const char*> &extensions)
{
	VkInstanceCreateInfo res;

	res.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	res.pNext = nullptr;
	res.flags = 0;
	res.pApplicationInfo = applicationInfo;
	res.enabledLayerCount = layers.size();
	res.ppEnabledLayerNames = layers.data();
	res.enabledExtensionCount = extensions.size();
	res.ppEnabledExtensionNames = extensions.data();

	return res;
}

class VkInstanceCreateInfo_data
{
public:
	VkInstanceCreateInfo_data(bool isProfile);
	~VkInstanceCreateInfo_data(void);

	bool isProfile;
	std::vector<const char*> layers;
	std::vector<const char*> extensions;
	VkApplicationInfo applicationInfo;
	VkInstanceCreateInfo createInfo;

private:
};

VkInstanceCreateInfo_data::VkInstanceCreateInfo_data(bool isProfile) :
	isProfile(isProfile),
	layers(getLayers(isProfile)),
	extensions(getExtensions()),
	applicationInfo(getApplicationInfo()),
	createInfo(getInstanceCreateInfo(&this->applicationInfo, this->layers, this->extensions))
{
}

VkInstanceCreateInfo_data::~VkInstanceCreateInfo_data(void)
{
}

void Vk::initInstance(void)
{
	VkInstanceCreateInfo_data data(krt.config.isProfile);

	printf("Used layers:\n");
	for (auto layer : data.layers)
		printf("	%s\n", layer);
	vkAssert(vkCreateInstance(&data.createInfo, nullptr, &this->instance));
}

VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

	if (func != nullptr)
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	else
		return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

	if (func != nullptr)
		func(instance, debugMessenger, pAllocator);
}

void Vk::initValidationLayers(void)
{
	#ifndef DEBUG
	return;
	#endif // DEBUG
	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
	createInfo.pUserData = nullptr;

	vkAssert(vkCreateDebugUtilsMessengerEXT(this->instance, &createInfo, nullptr, &this->debugMessenger));
}
