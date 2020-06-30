#pragma once

#include <memory>
#include <GLFW/glfw3.h>
#include "../ISystem.hpp"

namespace Subtile {
namespace System {

class Glfw
{
public:
	template <typename ...Args>
	Glfw(uint32_t ctx, Args &&...args) :
		m_window(createWindow(ctx, std::forward<Args>(args)...)),
		m_inputs(createInputs()),
		m_inputs_map(createInputsMap())
	{
	}

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
		Window(const std::string &title = "SUBTILE® Application", size_t w = 1600, size_t h = 900);
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

	template <typename ...Args>
	Window createWindow(uint32_t ctx, Args &&...args) const
	{
		if (glfwInit() == GLFW_FALSE)
			throw Error("Can't initialize GLFW");

		glfwWindowHint(GLFW_CLIENT_API, ctx);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		return Window(std::forward<Args>(args)...);
	}

	std::vector<std::unique_ptr<System::IInput>> createInputs(void);
	std::map<std::string, System::IInput&> createInputsMap(void);
};

}
}