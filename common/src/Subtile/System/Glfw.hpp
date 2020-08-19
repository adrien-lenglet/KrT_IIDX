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

private:
	Glfw(Ctx &&ctx, std::unique_ptr<Window> &&window);

	struct construct_window_t {};

	template <typename ...Args>
	Glfw(construct_window_t, Ctx &&ctx, Args &&...args) :
		Glfw(std::move(ctx), std::make_unique<Window>(std::forward<Args>(args)...))
	{
	}

	class AButton : public System::Input::Button
	{
	public:
		AButton(const std::string &name, std::function<bool (void)> read_fun);
		~AButton(void) override;

		const std::string& getName(void) const override;
		double getActivity(void) const override;

		bool getState(void) const override;

		void update(void) override;

	protected:
		std::string m_name;
		std::function<bool (void)> m_read_fun;
		bool m_last_state;
		bool m_state;
	};

	class Keyboard : public System::Input::Keyboard
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

	class Inputs
	{
	public:
		using input_map_type = std::map<std::string, System::Input&>;

		static const std::map<std::string, int> m_keys;

		Inputs(Window &window);

		const input_map_type& getMap(void) const;

	private:
		std::vector<std::unique_ptr<System::Input>> m_inputs;
		input_map_type m_inputs_map;

		std::vector<std::unique_ptr<System::Input>> create(Window &window);
		input_map_type createMap(void);
	};

public:
	template <typename ...Args>
	Glfw(uint32_t api, Args &&...args) :
		Glfw(construct_window_t(), Ctx(api), std::forward<Args>(args)...)
	{
	}

	void scanInputs(void);
	const Inputs::input_map_type& getInputs(void);

	util::svec getRequiredVkInstanceExts(void) const;
	Window& getWindow(void) const;

	class Window
	{
	public:
		Window(const std::string &title = "SUBTILE® Application", size_t w = 1600, size_t h = 900);
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
	std::unique_ptr<Window> m_window;
	Inputs m_inputs;

	static std::string getError(void);
};

}