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

Glfw::Window Glfw::createWindow(void) const
{
	if (glfwInit() == GLFW_FALSE)
		throw Error("Can't initialize GLFW");

	return Window(1600, 900, "SUBTILE® Application");
}

std::vector<std::unique_ptr<System::IInput>> Glfw::createInputs(void)
{
	std::vector<std::unique_ptr<System::IInput>> res;

	res.emplace_back(new GlfwVulkan::Input::AButton("close_window", [this](){
		return m_window.shouldClose();
	}));
	for (const auto &k : m_keys)
		res.emplace_back(new GlfwVulkan::Input::AButton(k.first, [k, this](){
			return glfwGetKey(m_window, k.second) == GLFW_PRESS;
		}));
	res.emplace_back(new GlfwVulkan::Input::Keyboard(m_window));
	return res;
}

std::map<std::string, System::IInput&> Glfw::createInputsMap(void)
{
	std::map<std::string, System::IInput&> res;

	for (const auto &in : m_inputs)
		res.emplace(in->getName(), *in);
	return res;
}

Glfw::Glfw(void) :
	m_window(createWindow()),
	m_inputs(createInputs()),
	m_inputs_map(createInputsMap())
{
}

Glfw::~Glfw(void)
{
	glfwTerminate();
}

void Glfw::scanInputs(void)
{
	glfwPollEvents();
}

const std::map<std::string, System::IInput&>& Glfw::getInputs(void)
{
	return m_inputs_map;
}

}
}