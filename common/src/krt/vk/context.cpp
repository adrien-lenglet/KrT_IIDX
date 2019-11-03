
#include <exception>
#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "vk.hpp"

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

Context::Context(Vk &vk, int32_t w, int32_t h) :
	vk(vk),
	w(w),
	h(h),
	window(createWindow()),
	instance(createInstance()),
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
