#include <iostream>
#include "Glfw.hpp"

namespace Subtile {

const std::map<std::string, int> Glfw::Inputs::m_keys = {
	{"KEY_SPACE", GLFW_KEY_SPACE},
	{"KEY_APOSTROPHE", GLFW_KEY_APOSTROPHE},
	{"KEY_COMMA", GLFW_KEY_COMMA},
	{"KEY_MINUS", GLFW_KEY_MINUS},
	{"KEY_PERIOD", GLFW_KEY_PERIOD},
	{"KEY_SLASH", GLFW_KEY_SLASH},
	{"KEY_0", GLFW_KEY_0},
	{"KEY_1", GLFW_KEY_1},
	{"KEY_2", GLFW_KEY_2},
	{"KEY_3", GLFW_KEY_3},
	{"KEY_4", GLFW_KEY_4},
	{"KEY_5", GLFW_KEY_5},
	{"KEY_6", GLFW_KEY_6},
	{"KEY_7", GLFW_KEY_7},
	{"KEY_8", GLFW_KEY_8},
	{"KEY_9", GLFW_KEY_9},
	{"KEY_SEMICOLON", GLFW_KEY_SEMICOLON},
	{"KEY_EQUAL", GLFW_KEY_EQUAL},
	{"KEY_A", GLFW_KEY_A},
	{"KEY_B", GLFW_KEY_B},
	{"KEY_C", GLFW_KEY_C},
	{"KEY_D", GLFW_KEY_D},
	{"KEY_E", GLFW_KEY_E},
	{"KEY_F", GLFW_KEY_F},
	{"KEY_G", GLFW_KEY_G},
	{"KEY_H", GLFW_KEY_H},
	{"KEY_I", GLFW_KEY_I},
	{"KEY_J", GLFW_KEY_J},
	{"KEY_K", GLFW_KEY_K},
	{"KEY_L", GLFW_KEY_L},
	{"KEY_M", GLFW_KEY_M},
	{"KEY_N", GLFW_KEY_N},
	{"KEY_O", GLFW_KEY_O},
	{"KEY_P", GLFW_KEY_P},
	{"KEY_Q", GLFW_KEY_Q},
	{"KEY_R", GLFW_KEY_R},
	{"KEY_S", GLFW_KEY_S},
	{"KEY_T", GLFW_KEY_T},
	{"KEY_U", GLFW_KEY_U},
	{"KEY_V", GLFW_KEY_V},
	{"KEY_W", GLFW_KEY_W},
	{"KEY_X", GLFW_KEY_X},
	{"KEY_Y", GLFW_KEY_Y},
	{"KEY_Z", GLFW_KEY_Z},
	{"KEY_LEFT_BRACKET", GLFW_KEY_LEFT_BRACKET},
	{"KEY_BACKSLASH", GLFW_KEY_BACKSLASH},
	{"KEY_RIGHT_BRACKET", GLFW_KEY_RIGHT_BRACKET},
	{"KEY_GRAVE_ACCENT", GLFW_KEY_GRAVE_ACCENT},
	{"KEY_WORLD_1", GLFW_KEY_WORLD_1},
	{"KEY_WORLD_2", GLFW_KEY_WORLD_2},
	{"KEY_ESCAPE", GLFW_KEY_ESCAPE},
	{"KEY_ENTER", GLFW_KEY_ENTER},
	{"KEY_TAB", GLFW_KEY_TAB},
	{"KEY_BACKSPACE", GLFW_KEY_BACKSPACE},
	{"KEY_INSERT", GLFW_KEY_INSERT},
	{"KEY_DELETE", GLFW_KEY_DELETE},
	{"KEY_RIGHT", GLFW_KEY_RIGHT},
	{"KEY_LEFT", GLFW_KEY_LEFT},
	{"KEY_DOWN", GLFW_KEY_DOWN},
	{"KEY_UP", GLFW_KEY_UP},
	{"KEY_PAGE_UP", GLFW_KEY_PAGE_UP},
	{"KEY_PAGE_DOWN", GLFW_KEY_PAGE_DOWN},
	{"KEY_HOME", GLFW_KEY_HOME},
	{"KEY_END", GLFW_KEY_END},
	{"KEY_CAPS_LOCK", GLFW_KEY_CAPS_LOCK},
	{"KEY_SCROLL_LOCK", GLFW_KEY_SCROLL_LOCK},
	{"KEY_NUM_LOCK", GLFW_KEY_NUM_LOCK},
	{"KEY_PRINT_SCREEN", GLFW_KEY_PRINT_SCREEN},
	{"KEY_PAUSE", GLFW_KEY_PAUSE},
	{"KEY_F1", GLFW_KEY_F1},
	{"KEY_F2", GLFW_KEY_F2},
	{"KEY_F3", GLFW_KEY_F3},
	{"KEY_F4", GLFW_KEY_F4},
	{"KEY_F5", GLFW_KEY_F5},
	{"KEY_F6", GLFW_KEY_F6},
	{"KEY_F7", GLFW_KEY_F7},
	{"KEY_F8", GLFW_KEY_F8},
	{"KEY_F9", GLFW_KEY_F9},
	{"KEY_F10", GLFW_KEY_F10},
	{"KEY_F11", GLFW_KEY_F11},
	{"KEY_F12", GLFW_KEY_F12},
	{"KEY_F13", GLFW_KEY_F13},
	{"KEY_F14", GLFW_KEY_F14},
	{"KEY_F15", GLFW_KEY_F15},
	{"KEY_F16", GLFW_KEY_F16},
	{"KEY_F17", GLFW_KEY_F17},
	{"KEY_F18", GLFW_KEY_F18},
	{"KEY_F19", GLFW_KEY_F19},
	{"KEY_F20", GLFW_KEY_F20},
	{"KEY_F21", GLFW_KEY_F21},
	{"KEY_F22", GLFW_KEY_F22},
	{"KEY_F23", GLFW_KEY_F23},
	{"KEY_F24", GLFW_KEY_F24},
	{"KEY_F25", GLFW_KEY_F25},
	{"KEY_KP_0", GLFW_KEY_KP_0},
	{"KEY_KP_1", GLFW_KEY_KP_1},
	{"KEY_KP_2", GLFW_KEY_KP_2},
	{"KEY_KP_3", GLFW_KEY_KP_3},
	{"KEY_KP_4", GLFW_KEY_KP_4},
	{"KEY_KP_5", GLFW_KEY_KP_5},
	{"KEY_KP_6", GLFW_KEY_KP_6},
	{"KEY_KP_7", GLFW_KEY_KP_7},
	{"KEY_KP_8", GLFW_KEY_KP_8},
	{"KEY_KP_9", GLFW_KEY_KP_9},
	{"KEY_KP_DECIMAL", GLFW_KEY_KP_DECIMAL},
	{"KEY_KP_DIVIDE", GLFW_KEY_KP_DIVIDE},
	{"KEY_KP_MULTIPLY", GLFW_KEY_KP_MULTIPLY},
	{"KEY_KP_SUBTRACT", GLFW_KEY_KP_SUBTRACT},
	{"KEY_KP_ADD", GLFW_KEY_KP_ADD},
	{"KEY_KP_ENTER", GLFW_KEY_KP_ENTER},
	{"KEY_KP_EQUAL", GLFW_KEY_KP_EQUAL},
	{"KEY_LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT},
	{"KEY_LEFT_CONTROL", GLFW_KEY_LEFT_CONTROL},
	{"KEY_LEFT_ALT", GLFW_KEY_LEFT_ALT},
	{"KEY_LEFT_SUPER", GLFW_KEY_LEFT_SUPER},
	{"KEY_RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT},
	{"KEY_RIGHT_CONTROL", GLFW_KEY_RIGHT_CONTROL},
	{"KEY_RIGHT_ALT", GLFW_KEY_RIGHT_ALT},
	{"KEY_RIGHT_SUPER", GLFW_KEY_RIGHT_SUPER},
	{"KEY_MENU", GLFW_KEY_MENU}
};

Glfw::AButton::AButton(const std::string &name, std::function<bool (void)> read_fun) :
	m_name(name),
	m_read_fun(read_fun),
	m_last_state(false),
	m_state(false)
{
}

Glfw::AButton::~AButton(void)
{
}

const std::string& Glfw::AButton::getName(void) const
{
	return m_name;
}

double Glfw::AButton::getActivity(void) const
{
	return m_last_state != m_state ? 1.0 : 0.0;
}

bool Glfw::AButton::getState(void) const
{
	return m_state;
}

void Glfw::AButton::update(void)
{
	m_last_state = m_state;
	m_state = m_read_fun();
}

std::map<GLFWwindow*, std::function<void (unsigned int)>&> Glfw::Keyboard::handlerCallbacks;

void Glfw::Keyboard::handler(GLFWwindow *window, unsigned int codepoint)
{
	handlerCallbacks.at(window)(codepoint);
}

Glfw::Keyboard::Keyboard(GLFWwindow *window) :
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

Glfw::Keyboard::~Keyboard(void)
{
	glfwSetCharCallback(m_window, nullptr);
	handlerCallbacks.erase(m_window);
}

const std::string& Glfw::Keyboard::getName(void) const
{
	return m_name;
}

double Glfw::Keyboard::getActivity(void) const
{
	return 0.0;
}

std::vector<uint32_t> Glfw::Keyboard::poll(void) const
{
	std::vector<uint32_t> res = m_buffer;

	const_cast<Keyboard*>(this)->m_buffer.clear();
	return res;
}

void Glfw::Keyboard::update(void)
{
}

std::string Glfw::getError(void)
{
	const char *desc;
	int code = glfwGetError(&desc);

	if (code == GLFW_NO_ERROR)
		return "[no error]";
	else
		return desc;
}

std::vector<std::unique_ptr<System::Input>> Glfw::Inputs::create(/*Glfw::Window &window*/)
{
	std::vector<std::unique_ptr<System::Input>> res;

	/*res.emplace_back(new AButton("close_window", [&window](){
		return window.shouldClose();
	}));
	for (const auto &k : m_keys)
		res.emplace_back(new AButton(k.first, [k, &window](){
			return glfwGetKey(window, k.second) == GLFW_PRESS;
		}));
	res.emplace_back(new Keyboard(window));*/
	return res;
}

std::map<std::string, System::Input&> Glfw::Inputs::createMap(void)
{
	std::map<std::string, System::Input&> res;

	for (const auto &in : m_inputs)
		res.emplace(in->getName(), *in);
	return res;
}

Glfw::Inputs::Inputs(/*Glfw::Window &window*/) :
	m_inputs(create()),
	m_inputs_map(createMap())
{
}

const Glfw::Inputs::input_map_type& Glfw::Inputs::getMap(void) const
{
	return m_inputs_map;
}

Glfw::Glfw(uint32_t api) :
	m_ctx(api)
{
}

void Glfw::scanInputs(void)
{
	glfwPollEvents();
}

const std::map<std::string, System::Input&>& Glfw::getInputs(void)
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

Glfw::Window::Window(const svec2 &size, const std::string &title) :
	m_window(glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr))
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