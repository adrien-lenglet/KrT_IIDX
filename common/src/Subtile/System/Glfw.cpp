#include <iostream>
#include "Glfw.hpp"

namespace Subtile {

std::string Glfw::getError(void)
{
	const char *desc;
	int code = glfwGetError(&desc);

	if (code == GLFW_NO_ERROR)
		return "[no error]";
	else
		return desc;
}

Glfw::Glfw(uint32_t api) :
	m_ctx(api)
{
}

void Glfw::scanInputs(void)
{
	glfwPollEvents();
}

util::svec Glfw::getRequiredVkInstanceExts(void) const
{
	uint32_t size;
	auto cstrs = glfwGetRequiredInstanceExtensions(&size);
	util::svec res;
	for (size_t i = 0; i < size; i++)
		res.emplace_back(cstrs[i]);
	return res;
}

svec2 Glfw::Window::getSize(void) const
{
	int w, h;

	glfwGetFramebufferSize(*this, &w, &h);
	return svec2(w, h);
}

Glfw::Error::Error(const std::string &msg) :
	std::runtime_error(std::string("GLFW Error: ") + msg + std::string(": ") + Glfw::getError())
{
}

Glfw::Error::~Error(void)
{
}

Glfw::Ctx::Ctx(uint32_t api)
{
	if (glfwInit() == GLFW_FALSE)
		throw Error("Can't initialize GLFW");

	glfwWindowHint(GLFW_CLIENT_API, api);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
}

Glfw::Ctx::Ctx(Ctx &&other)
{
	other.m_moved = true;
}

Glfw::Ctx::~Ctx(void)
{
	if (!m_moved)
		glfwTerminate();
}

Glfw::Window::Window(const svec2 &size, const std::string &title) :
	m_window(glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr))
{
	if (m_window == nullptr)
		throw Glfw::Error("Can't create GLFWwindow");
}

Glfw::Window::Window(Window &&other) :
	m_window(other.m_window)
{
	other.m_window = nullptr;
}

Glfw::Window::~Window(void)
{
	if (m_window)
		glfwDestroyWindow(m_window);
}

bool Glfw::Window::shouldClose(void) const
{
	return glfwWindowShouldClose(m_window);
}

Glfw::Window::operator GLFWwindow*(void) const
{
	return m_window;
}

}