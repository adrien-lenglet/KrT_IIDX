
#include <exception>
#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "glfw.hpp"

Glfw::Glfw(int32_t w, int32_t h)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	this->window = glfwCreateWindow(w, h, "SUNREN", nullptr, nullptr);
	if (this->window == nullptr)
		throw std::runtime_error("Can't initialize GLFW window");
}

Glfw::~Glfw(void)
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

int Glfw::shouldClose(void)
{
	return glfwWindowShouldClose(this->window);
}
