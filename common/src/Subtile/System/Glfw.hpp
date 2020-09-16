#pragma once

#include <memory>
#include <GLFW/glfw3.h>
#include "../System.hpp"
#include "Subtile/Math/Size.hpp"

namespace Subtile {

class Glfw
{
	class Ctx;

public:
	class Window;

	Glfw(uint32_t api);

	void scanInputs(void);

	util::svec getRequiredVkInstanceExts(void) const;
	Window& getWindow(void) const;

	class Window
	{
	public:
		Window(const svec2 &size, const std::string &title = "SUBTILE® Application");
		Window(Window &&other);
		~Window(void);

		bool shouldClose(void) const;
		operator GLFWwindow*(void) const;
		svec2 getSize(void) const;

	private:
		GLFWwindow *m_window;
	};

private:
	class Error : public std::runtime_error
	{
	public:
		Error(const std::string &msg);
		~Error(void);
	};

	class Ctx
	{
	public:
		Ctx(uint32_t api);
		Ctx(Ctx &&other);
		~Ctx(void);

	private:
		bool m_moved = false;
	};

	Ctx m_ctx;

	static std::string getError(void);
};

}