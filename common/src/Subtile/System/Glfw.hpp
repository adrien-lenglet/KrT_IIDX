#pragma once

#include <memory>
#include <GLFW/glfw3.h>
#include "../ISystem.hpp"

namespace Subtile {
namespace System {

class Glfw : public ISystem
{
public:
	Glfw(void);
	~Glfw(void) override;

	void scanInputs(void) override;
	const std::map<std::string, System::IInput&>& getInputs(void) override;

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

	Window createWindow(void) const;
	std::vector<std::unique_ptr<System::IInput>> createInputs(void);
	std::map<std::string, System::IInput&> createInputsMap(void);
};

}
}