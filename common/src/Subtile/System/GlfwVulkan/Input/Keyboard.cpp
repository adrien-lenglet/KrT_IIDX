#include "Keyboard.hpp"
#include "util.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {
namespace Input {

std::map<GLFWwindow*, std::function<void (unsigned int)>&> Keyboard::handlerCallbacks;

void Keyboard::handler(GLFWwindow *window, unsigned int codepoint)
{
	handlerCallbacks.at(window)(codepoint);
}

Keyboard::Keyboard(GLFWwindow *window) :
	m_name("keyboard"),
	m_window(window),
	m_handler([this](unsigned int codepoint) {
		if (m_buffer.size() < 8192)
			m_buffer.push_back(codepoint);
	})
{
	if (handlerCallbacks.find(window) != handlerCallbacks.end())
		throw std::runtime_error("Duplicated keyboard callbacks.");
	handlerCallbacks.emplace(window, m_handler);
	glfwSetCharCallback(m_window, Keyboard::handler);
}

Keyboard::~Keyboard(void)
{
	glfwSetCharCallback(m_window, nullptr);
	handlerCallbacks.erase(m_window);
}

const std::string& Keyboard::getName(void) const
{
	return m_name;
}

double Keyboard::getActivity(void) const
{
	return 0.0;
}

std::vector<uint32_t> Keyboard::poll(void) const
{
	std::vector<uint32_t> res = m_buffer;

	const_cast<Keyboard*>(this)->m_buffer.clear();
	return res;
}

void Keyboard::update(void)
{
}

}
}
}
}