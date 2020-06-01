#pragma once

#include <map>
#include <functional>
#include "GLFW/glfw3.h"
#include "../../Input/IKeyboard.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {
namespace Input {

class Keyboard : public System::Input::IKeyboard
{
public:
	Keyboard(GLFWwindow *window);
	~Keyboard(void) override;

	void update(void) override;

	const std::string& getName(void) const override;
	double getActivity(void) const override;

	std::vector<uint32_t> poll(void) const override;

private:
	std::string m_name;
	GLFWwindow *m_window;
	std::function<void (unsigned int)> m_handler;
	std::vector<uint32_t> m_buffer;

	static std::map<GLFWwindow*, std::function<void (unsigned int)>&> handlerCallbacks;
	static void handler(GLFWwindow*, unsigned int);
};

}
}
}
}