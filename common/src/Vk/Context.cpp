#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>

#include "Context.hpp"
#include "Misc.hpp"
#include "util/algo.hpp"
#include "util/func.hpp"

VkResult vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));

	if (func != nullptr)
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	else
		return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
	auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));

	if (func != nullptr)
		func(instance, debugMessenger, pAllocator);
}

namespace Vk {

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData)
{
	static_cast<void>(messageType);
	static_cast<void>(pUserData);

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

	std::vector<std::string> not_present;
	for (const auto &w : wanted)
		if (!util::contains(layers, w))
			not_present.push_back(w);
	if (!not_present.empty())
		throw std::runtime_error(std::string("Layers not found: " + util::join(not_present, std::string(", "))));

	return wanted;
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

VkInstance Context::createInstance(bool doProfile)
{
	VkInstance res;
	VkInstanceCreateInfo_data data(doProfile);

	printf("Used layers:\n");
	for (auto layer : data.layers)
		printf("	%s\n", layer);
	vkAssert(vkCreateInstance(&data.createInfo, nullptr, &res));

	return res;
}

VkDebugUtilsMessengerEXT Context::createDebugMessenger(void)
{
	VkDebugUtilsMessengerEXT res;
	#ifndef DEBUG
	return VK_NULL_HANDLE;
	#endif // DEBUG
	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
	createInfo.pUserData = nullptr;

	vkAssert(vkCreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &res));
	return res;
}

GLFWwindow* Context::createWindow(void)
{
	GLFWwindow* res;

	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	res = glfwCreateWindow(w, h, "KrT_IIDX", nullptr, nullptr);
	if (res == nullptr)
		throw std::runtime_error("Can't initialize GLFW window");

	return res;
}

Context::Context(int32_t w, int32_t h, bool doProfile) :
	w(w),
	h(h),
	window(createWindow()),
	instance(createInstance(doProfile)),
	debugMessenger(createDebugMessenger()),
	surface(createSurface())
{
}

Context::~Context(void)
{
	#ifdef DEBUG
	vkDestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	#endif

	vkDestroySurfaceKHR(instance, surface, nullptr);
	printf("Vk destr done.\n");
	vkDestroyInstance(instance, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
}

int Context::shouldClose(void)
{
	return glfwWindowShouldClose(window);
}

VkSurfaceKHR Context::createSurface(void)
{
	VkSurfaceKHR res;

	vkAssert(glfwCreateWindowSurface(instance, window, nullptr, &res));

	return res;
}

}