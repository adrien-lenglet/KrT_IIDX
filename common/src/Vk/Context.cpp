#include <exception>
#include <stdexcept>
#include <iostream>
#include <vector>

#include "Context.hpp"
#include "InstanceCreateInfo.hpp"
#include "Misc.hpp"
#include "util.hpp"

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

namespace Vk {

VkInstance Context::createInstance(bool doProfile)
{
	VkInstance res;
	InstanceCreateInfo data(doProfile);

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