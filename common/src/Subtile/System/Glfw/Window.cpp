#include "../Glfw.hpp"

namespace Subtile {
namespace System {

Glfw::Window::Window(const std::string &title, size_t w, size_t h) :
	m_window(glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr))
{
	if (m_window == nullptr)
		throw Glfw::Error("Can't create GLFWwindow");
}

Glfw::Window::~Window(void)
{
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
}