#pragma once

#include <memory>
#include <GLFW/glfw3.h>
#include "../ISystem.hpp"

namespace Subtile {
namespace System {

class Glfw
{
public:
	Glfw(uint32_t ctx = GLFW_NO_API);
	~Glfw(void);

	void scanInputs(void);
	const std::map<std::string, System::IInput&>& getInputs(void);

	util::svec getRequiredVkInstanceExts(void) const;

private:
	class Error : public std::runtime_error
	{
	public:
		Error(const std::string &msg);
		~Error(void);
	};

	class Window
	{
	public:
		Window(size_t w, size_t h, const std::string &title);
		~Window(void);

		bool shouldClose(void) const;
		operator GLFWwindow*(void) const;

	private:
		GLFWwindow *m_window;
	};

	Window m_window;

	static const std::map<std::string, int> m_keys;
	static std::string getError(void);

	std::vector<std::unique_ptr<System::IInput>> m_inputs;
	std::map<std::string, System::IInput&> m_inputs_map;

	Window createWindow(uint32_t) const;
	std::vector<std::unique_ptr<System::IInput>> createInputs(void);
	std::map<std::string, System::IInput&> createInputsMap(void);
};

}
}