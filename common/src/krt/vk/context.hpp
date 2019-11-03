
#pragma once

#include <GLFW/glfw3.h>

class Context
{
public:
	Context(Vk &vk, int32_t w, int32_t h);
	~Context(void);

	Vk &vk;

	int32_t w;
	int32_t h;

	GLFWwindow *window;
	VkInstance instance;
	VkDebugUtilsMessengerEXT debugMessenger;
	VkSurfaceKHR surface;

	int shouldClose(void);

private:
	GLFWwindow* createWindow(void);
	VkInstance createInstance(void);
	VkDebugUtilsMessengerEXT createDebugMessenger(void);
	VkSurfaceKHR createSurface(void);
};
