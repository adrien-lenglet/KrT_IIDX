#include <iostream>
#include "CGlfwVulkan.hpp"
#include "GlfwVulkan/Input/AButton.hpp"

namespace Subtile {
namespace System {

CGlfwVulkan::CGlfwVulkan(size_t w, size_t h, bool isDebug, bool doProfile) :
	m_vk(w, h, isDebug, doProfile)
{
	m_inputs.emplace_back(new GlfwVulkan::Input::AButton("close_window", [this](){ return m_vk.shouldClose(); }));

	for (const auto &in : m_inputs)
		m_inputs_map.emplace(in->getName(), *in);
}

CGlfwVulkan::~CGlfwVulkan(void)
{
}

void CGlfwVulkan::scanInputs(void)
{
	glfwPollEvents();
	for (auto &input : m_inputs) {
		try {
			dynamic_cast<GlfwVulkan::Input::AButton&>(*input).scan();
		} catch (std::bad_cast&) {
			throw std::runtime_error("Unknown input type for scanning");
		}
	}
}

const std::map<std::string, System::IInput&> CGlfwVulkan::getInputs(void)
{
	return m_inputs_map;
}

void CGlfwVulkan::render(void)
{
	m_vk.render();
}

}
}