#include <iostream>
#include "Glfw.hpp"
#include "Glfw/Input/AButton.hpp"
#include "Glfw/Input/Keyboard.hpp"

namespace Subtile {
namespace System {

std::string Glfw::getError(void)
{
	const char *desc;
	int code = glfwGetError(&desc);

	if (code == GLFW_NO_ERROR)
		return "[no error]";
	else
		return desc;
}

std::vector<std::unique_ptr<System::IInput>> Glfw::Inputs::create(Glfw::Window &window)
{
	std::vector<std::unique_ptr<System::IInput>> res;

	res.emplace_back(new GlfwVulkan::Input::AButton("close_window", [&window](){
		return window.shouldClose();
	}));
	for (const auto &k : m_keys)
		res.emplace_back(new GlfwVulkan::Input::AButton(k.first, [k, &window](){
			return glfwGetKey(window, k.second) == GLFW_PRESS;
		}));
	res.emplace_back(new GlfwVulkan::Input::Keyboard(window));
	return res;
}

std::map<std::string, System::IInput&> Glfw::Inputs::createMap(void)
{
	std::map<std::string, System::IInput&> res;

	for (const auto &in : m_inputs)
		res.emplace(in->getName(), *in);
	return res;
}

Glfw::Inputs::Inputs(Glfw::Window &window) :
	m_inputs(create(window)),
	m_inputs_map(createMap())
{
}

const Glfw::Inputs::input_map_type& Glfw::Inputs::getMap(void) const
{
	return m_inputs_map;
}

Glfw::Glfw(Glfw::Ctx &&ctx, std::unique_ptr<Glfw::Window> &&window) :
	m_ctx(std::move(ctx)),
	m_window(std::move(window)),
	m_inputs(*m_window)
{
}

void Glfw::scanInputs(void)
{
	glfwPollEvents();
}

const std::map<std::string, System::IInput&>& Glfw::getInputs(void)
{
	return m_inputs.getMap();
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

Glfw::Window& Glfw::getWindow(void) const
{
	return *m_window;
}

svec2 Glfw::Window::getSize(void) const
{
	int w, h;

	glfwGetWindowSize(*this, &w, &h);
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
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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

Glfw::Window::Window(const std::string &title, size_t w, size_t h) :
	m_window(glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr))
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
}