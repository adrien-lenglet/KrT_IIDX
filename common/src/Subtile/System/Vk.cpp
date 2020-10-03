#include <iostream>
#include <set>
#include <cstring>
#include <sstream>
#include "util/enum_class_bitmask.hpp"
#include "Vk.hpp"

namespace Subtile {

static std::map<GLFWwindow*, Vk::Surface*> windowToSurface;
static std::set<Vk*> vk_instances;

static void framebufferResizeCallback(GLFWwindow *window, int width, int height)
{
	windowToSurface.at(window)->resized({width, height});
}

static void monitorCallback(GLFWmonitor *monitor, int event)
{
	static_cast<void>(monitor);
	static_cast<void>(event);
	for (auto &vk : vk_instances)
		vk->m_monitors = vk->queryMonitors();
}

Vk::Vk(bool validate, bool isRenderDoc, bool isMonitor) :
	m_glfw(GLFW_NO_API),
	m_is_debug(validate),
	m_instance(createInstance(isRenderDoc, isMonitor)),
	m_debug_messenger(createDebugMessenger()),
	m_monitors(queryMonitors())
{
	vk_instances.emplace(this);
	glfwSetMonitorCallback(monitorCallback);
}

Vk::~Vk(void)
{
	auto got = vk_instances.find(this);
	if (got == vk_instances.end())
		util::fatal_throw([](){
			throw std::runtime_error("Can't find current Vk instance for destruction");
		});
	vk_instances.erase(got);
}

void Vk::scanInputs(void)
{
	for (auto &wp : windowToSurface)
		wp.second->resetResized();
	m_glfw.scanInputs();
}

const VkAllocationCallbacks* Vk::getAllocator(void) const
{
	return nullptr;
}

const std::string& Vk::resultToString(VkResult res)
{
	static const std::map<VkResult, std::string> table {
		{VK_SUCCESS, "VK_SUCCESS"},
		{VK_NOT_READY, "VK_NOT_READY"},
		{VK_TIMEOUT, "VK_TIMEOUT"},
		{VK_EVENT_SET, "VK_EVENT_SET"},
		{VK_EVENT_RESET, "VK_EVENT_RESET"},
		{VK_INCOMPLETE, "VK_INCOMPLETE"},
		{VK_ERROR_OUT_OF_HOST_MEMORY, "VK_ERROR_OUT_OF_HOST_MEMORY"},
		{VK_ERROR_OUT_OF_DEVICE_MEMORY, "VK_ERROR_OUT_OF_DEVICE_MEMORY"},
		{VK_ERROR_INITIALIZATION_FAILED, "VK_ERROR_INITIALIZATION_FAILED"},
		{VK_ERROR_DEVICE_LOST, "VK_ERROR_DEVICE_LOST"},
		{VK_ERROR_MEMORY_MAP_FAILED, "VK_ERROR_MEMORY_MAP_FAILED"},
		{VK_ERROR_LAYER_NOT_PRESENT, "VK_ERROR_LAYER_NOT_PRESENT"},
		{VK_ERROR_EXTENSION_NOT_PRESENT, "VK_ERROR_EXTENSION_NOT_PRESENT"},
		{VK_ERROR_FEATURE_NOT_PRESENT, "VK_ERROR_FEATURE_NOT_PRESENT"},
		{VK_ERROR_INCOMPATIBLE_DRIVER, "VK_ERROR_INCOMPATIBLE_DRIVER"},
		{VK_ERROR_TOO_MANY_OBJECTS, "VK_ERROR_TOO_MANY_OBJECTS"},
		{VK_ERROR_FORMAT_NOT_SUPPORTED, "VK_ERROR_FORMAT_NOT_SUPPORTED"},
		{VK_ERROR_FRAGMENTED_POOL, "VK_ERROR_FRAGMENTED_POOL"},
		{VK_ERROR_UNKNOWN, "VK_ERROR_UNKNOWN"},
		{VK_ERROR_OUT_OF_POOL_MEMORY, "VK_ERROR_OUT_OF_POOL_MEMORY"},
		{VK_ERROR_INVALID_EXTERNAL_HANDLE, "VK_ERROR_INVALID_EXTERNAL_HANDLE"},
		{VK_ERROR_FRAGMENTATION, "VK_ERROR_FRAGMENTATION"},
		{VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS, "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS"},
		{VK_ERROR_SURFACE_LOST_KHR, "VK_ERROR_SURFACE_LOST_KHR"},
		{VK_ERROR_NATIVE_WINDOW_IN_USE_KHR, "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR"},
		{VK_SUBOPTIMAL_KHR, "VK_SUBOPTIMAL_KHR"},
		{VK_ERROR_OUT_OF_DATE_KHR, "VK_SUBOPTIMAL_KHR"},
		{VK_ERROR_INCOMPATIBLE_DISPLAY_KHR, "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR"},
		{VK_ERROR_VALIDATION_FAILED_EXT, "VK_ERROR_VALIDATION_FAILED_EXT"},
		{VK_ERROR_INVALID_SHADER_NV, "VK_ERROR_INVALID_SHADER_NV"},
		{VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT, "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT"},
		{VK_ERROR_NOT_PERMITTED_EXT, "VK_ERROR_NOT_PERMITTED_EXT"},
		{VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT, "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT"}
	};

	return table.at(res);
}

void Vk::assert(VkResult res)
{
	if (res == VK_SUCCESS)
		return;
	throw std::runtime_error(std::string("Vk::assert failed: ") + resultToString(res));
}

Vk::Instance::Instance(Vk &vk, VkInstance instance) :
	Vk::Handle<VkInstance>(instance),
	m_vk(vk)
{
}

template <>
void Vk::Handle<VkInstance>::destroy(VkInstance handle)
{
	vkDestroyInstance(handle, static_cast<Instance&>(*this).m_vk.getAllocator());
}

Vk::PhysicalDevices Vk::Instance::enumerateDevices(void)
{
	return PhysicalDevices(*this);
}

Vk::Instance Vk::createInstance(bool isRenderDoc, bool isMonitor)
{
	util::svec layers;
	util::svec exts = m_glfw.getRequiredVkInstanceExts();

	if (m_is_debug) {
		layers.emplace_back("VK_LAYER_KHRONOS_validation");
		exts.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}
	if (isRenderDoc)
		layers.emplace_back("VK_LAYER_RENDERDOC_Capture");
	if (isMonitor)
		layers.emplace_back("VK_LAYER_LUNARG_monitor");

	std::cout << "Enabled Vulkan layers: ";
	auto comma = "";
	for (auto &l : layers) {
		std::cout << comma << l;
		comma = ", ";
	}
	if (layers.size() == 0)
		std::cout << "[NONE]";
	std::cout << std::endl;

	VkApplicationInfo ai {};

	ai.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ai.pApplicationName = "SUBTILE® Application";
	ai.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	ai.pEngineName = "SUBTILE®";
	ai.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	ai.apiVersion = VK_API_VERSION_1_1;

	VkInstanceCreateInfo createInfo {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &ai;
	auto clayers = layers.c_strs();
	createInfo.enabledLayerCount = clayers.size();
	createInfo.ppEnabledLayerNames = clayers.data();
	auto cexts = exts.c_strs();
	createInfo.enabledExtensionCount = cexts.size();
	createInfo.ppEnabledExtensionNames = cexts.data();

	return Vk::Instance(*this, create<VkInstance>(vkCreateInstance, &createInfo, getAllocator()));
}

Vk::DebugMessenger::DebugMessenger(Instance &instance, VkDebugUtilsMessengerEXT messenger) :
	Instance::Handle<VkDebugUtilsMessengerEXT>(instance, messenger)
{
}

template <>
void Vk::Instance::Handle<VkDebugUtilsMessengerEXT>::destroy(Instance &instance, VkDebugUtilsMessengerEXT handle)
{
	instance.destroy(instance.getProcAddr<PFN_vkDestroyDebugUtilsMessengerEXT>("vkDestroyDebugUtilsMessengerEXT"), handle);
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debug_messenger_cb(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void*)
{
	static const std::map<VkDebugUtilsMessageSeverityFlagBitsEXT, std::string> sever_table {
		{VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT, "VERBOSE"},
		{VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT, "INFO"},
		{VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT, "WARNING"},
		{VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, "ERROR"}
	};

	static const std::map<VkDebugUtilsMessageTypeFlagBitsEXT, std::string> type_table {
		{VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT, "General"},
		{VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT, "Validation"},
		{VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT, "Performance"}
	};

	if (messageSeverity != VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT &&
	messageSeverity != VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
		auto comma = "";
		std::cerr << "[";
		for (auto &p : sever_table)
			if (p.first & messageSeverity) {
				std::cerr << p.second;
				comma = ", ";
			}
		std::cerr << "] -> {";
		comma = "";
		for (auto &p : type_table)
			if (p.first & messageType) {
				std::cerr << p.second;
				comma = ", ";
			}
		std::cerr << "}" << std::endl;

		std::cerr << pCallbackData->pMessage << std::endl;
	}

	return VK_FALSE;
}

std::optional<Vk::DebugMessenger> Vk::createDebugMessenger(void)
{
	if (!m_is_debug)
		return std::nullopt;

	VkDebugUtilsMessengerCreateInfoEXT ci {};
	ci.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	ci.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	ci.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	ci.pfnUserCallback = debug_messenger_cb;

	return m_instance.create<DebugMessenger>(m_instance.getProcAddr<PFN_vkCreateDebugUtilsMessengerEXT>("vkCreateDebugUtilsMessengerEXT"), ci);
}

static const std::map<std::string, int> glfw_keys = {
	{"KB_SPACE", GLFW_KEY_SPACE},
	{"KB_APOSTROPHE", GLFW_KEY_APOSTROPHE},
	{"KB_COMMA", GLFW_KEY_COMMA},
	{"KB_MINUS", GLFW_KEY_MINUS},
	{"KB_PERIOD", GLFW_KEY_PERIOD},
	{"KB_SLASH", GLFW_KEY_SLASH},
	{"KB_0", GLFW_KEY_0},
	{"KB_1", GLFW_KEY_1},
	{"KB_2", GLFW_KEY_2},
	{"KB_3", GLFW_KEY_3},
	{"KB_4", GLFW_KEY_4},
	{"KB_5", GLFW_KEY_5},
	{"KB_6", GLFW_KEY_6},
	{"KB_7", GLFW_KEY_7},
	{"KB_8", GLFW_KEY_8},
	{"KB_9", GLFW_KEY_9},
	{"KB_SEMICOLON", GLFW_KEY_SEMICOLON},
	{"KB_EQUAL", GLFW_KEY_EQUAL},
	{"KB_A", GLFW_KEY_A},
	{"KB_B", GLFW_KEY_B},
	{"KB_C", GLFW_KEY_C},
	{"KB_D", GLFW_KEY_D},
	{"KB_E", GLFW_KEY_E},
	{"KB_F", GLFW_KEY_F},
	{"KB_G", GLFW_KEY_G},
	{"KB_H", GLFW_KEY_H},
	{"KB_I", GLFW_KEY_I},
	{"KB_J", GLFW_KEY_J},
	{"KB_K", GLFW_KEY_K},
	{"KB_L", GLFW_KEY_L},
	{"KB_M", GLFW_KEY_M},
	{"KB_N", GLFW_KEY_N},
	{"KB_O", GLFW_KEY_O},
	{"KB_P", GLFW_KEY_P},
	{"KB_Q", GLFW_KEY_Q},
	{"KB_R", GLFW_KEY_R},
	{"KB_S", GLFW_KEY_S},
	{"KB_T", GLFW_KEY_T},
	{"KB_U", GLFW_KEY_U},
	{"KB_V", GLFW_KEY_V},
	{"KB_W", GLFW_KEY_W},
	{"KB_X", GLFW_KEY_X},
	{"KB_Y", GLFW_KEY_Y},
	{"KB_Z", GLFW_KEY_Z},
	{"KB_LEFT_BRACKET", GLFW_KEY_LEFT_BRACKET},
	{"KB_BACKSLASH", GLFW_KEY_BACKSLASH},
	{"KB_RIGHT_BRACKET", GLFW_KEY_RIGHT_BRACKET},
	{"KB_GRAVE_ACCENT", GLFW_KEY_GRAVE_ACCENT},
	{"KB_WORLD_1", GLFW_KEY_WORLD_1},
	{"KB_WORLD_2", GLFW_KEY_WORLD_2},
	{"KB_ESCAPE", GLFW_KEY_ESCAPE},
	{"KB_ENTER", GLFW_KEY_ENTER},
	{"KB_TAB", GLFW_KEY_TAB},
	{"KB_BACKSPACE", GLFW_KEY_BACKSPACE},
	{"KB_INSERT", GLFW_KEY_INSERT},
	{"KB_DELETE", GLFW_KEY_DELETE},
	{"KB_RIGHT", GLFW_KEY_RIGHT},
	{"KB_LEFT", GLFW_KEY_LEFT},
	{"KB_DOWN", GLFW_KEY_DOWN},
	{"KB_UP", GLFW_KEY_UP},
	{"KB_PAGE_UP", GLFW_KEY_PAGE_UP},
	{"KB_PAGE_DOWN", GLFW_KEY_PAGE_DOWN},
	{"KB_HOME", GLFW_KEY_HOME},
	{"KB_END", GLFW_KEY_END},
	{"KB_CAPS_LOCK", GLFW_KEY_CAPS_LOCK},
	{"KB_SCROLL_LOCK", GLFW_KEY_SCROLL_LOCK},
	{"KB_NUM_LOCK", GLFW_KEY_NUM_LOCK},
	{"KB_PRINT_SCREEN", GLFW_KEY_PRINT_SCREEN},
	{"KB_PAUSE", GLFW_KEY_PAUSE},
	{"KB_F1", GLFW_KEY_F1},
	{"KB_F2", GLFW_KEY_F2},
	{"KB_F3", GLFW_KEY_F3},
	{"KB_F4", GLFW_KEY_F4},
	{"KB_F5", GLFW_KEY_F5},
	{"KB_F6", GLFW_KEY_F6},
	{"KB_F7", GLFW_KEY_F7},
	{"KB_F8", GLFW_KEY_F8},
	{"KB_F9", GLFW_KEY_F9},
	{"KB_F10", GLFW_KEY_F10},
	{"KB_F11", GLFW_KEY_F11},
	{"KB_F12", GLFW_KEY_F12},
	{"KB_F13", GLFW_KEY_F13},
	{"KB_F14", GLFW_KEY_F14},
	{"KB_F15", GLFW_KEY_F15},
	{"KB_F16", GLFW_KEY_F16},
	{"KB_F17", GLFW_KEY_F17},
	{"KB_F18", GLFW_KEY_F18},
	{"KB_F19", GLFW_KEY_F19},
	{"KB_F20", GLFW_KEY_F20},
	{"KB_F21", GLFW_KEY_F21},
	{"KB_F22", GLFW_KEY_F22},
	{"KB_F23", GLFW_KEY_F23},
	{"KB_F24", GLFW_KEY_F24},
	{"KB_F25", GLFW_KEY_F25},
	{"KB_KP_0", GLFW_KEY_KP_0},
	{"KB_KP_1", GLFW_KEY_KP_1},
	{"KB_KP_2", GLFW_KEY_KP_2},
	{"KB_KP_3", GLFW_KEY_KP_3},
	{"KB_KP_4", GLFW_KEY_KP_4},
	{"KB_KP_5", GLFW_KEY_KP_5},
	{"KB_KP_6", GLFW_KEY_KP_6},
	{"KB_KP_7", GLFW_KEY_KP_7},
	{"KB_KP_8", GLFW_KEY_KP_8},
	{"KB_KP_9", GLFW_KEY_KP_9},
	{"KB_KP_DECIMAL", GLFW_KEY_KP_DECIMAL},
	{"KB_KP_DIVIDE", GLFW_KEY_KP_DIVIDE},
	{"KB_KP_MULTIPLY", GLFW_KEY_KP_MULTIPLY},
	{"KB_KP_SUBTRACT", GLFW_KEY_KP_SUBTRACT},
	{"KB_KP_ADD", GLFW_KEY_KP_ADD},
	{"KB_KP_ENTER", GLFW_KEY_KP_ENTER},
	{"KB_KP_EQUAL", GLFW_KEY_KP_EQUAL},
	{"KB_LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT},
	{"KB_LEFT_CONTROL", GLFW_KEY_LEFT_CONTROL},
	{"KB_LEFT_ALT", GLFW_KEY_LEFT_ALT},
	{"KB_LEFT_SUPER", GLFW_KEY_LEFT_SUPER},
	{"KB_RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT},
	{"KB_RIGHT_CONTROL", GLFW_KEY_RIGHT_CONTROL},
	{"KB_RIGHT_ALT", GLFW_KEY_RIGHT_ALT},
	{"KB_RIGHT_SUPER", GLFW_KEY_RIGHT_SUPER},
	{"KB_MENU", GLFW_KEY_MENU}
};

std::vector<std::unique_ptr<Button>> Vk::Surface::createUniqueButtons(void)
{
	std::vector<std::unique_ptr<Button>> res;

	for (const auto &k : glfw_keys)
		res.emplace_back(new GlfwButton(k.first, m_window, k.second));
	return res;
}

Vk::Surface::GlfwButton::GlfwButton(const std::string &id, GLFWwindow *window, int key_id) :
	m_id(id),
	m_window(window),
	m_key_id(key_id)
{
}

Vk::Surface::GlfwButton::~GlfwButton(void)
{
}

void Vk::Surface::GlfwButton::update(void)
{
	m_last_state = m_state;
	m_state = glfwGetKey(m_window, m_key_id) == GLFW_PRESS ? true : false;
}

const std::string& Vk::Surface::GlfwButton::id(void) const
{
	return m_id;
}

bool Vk::Surface::GlfwButton::active(void) const
{
	return m_last_state != m_state;
}

bool Vk::Surface::GlfwButton::state(void) const
{
	return m_state;
}

bool Vk::Surface::GlfwButton::pressed(void) const
{
	return !m_last_state && m_state;
}

bool Vk::Surface::GlfwButton::released(void) const
{
	return m_last_state && !m_state;
}

Vk::Surface::Surface(Instance &instance, const svec2 &extent, const std::string &title) :
	m_window(extent, title),
	m_surface(instance, instance.createVk(glfwCreateWindowSurface, m_window)),
	m_extent(m_window.getSize()),
	m_unique_buttons(createUniqueButtons()),
	m_buttons(getButtons()),
	m_buttons_id(getButtonsId()),
	m_inputs(getInputs()),
	m_inputs_id(getInputsId())
{
	auto [it, suc] = windowToSurface.emplace(static_cast<GLFWwindow*>(m_window), this);
	if (!suc)
		throw std::runtime_error("Can't emplace window surface in table");
	glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}

Vk::Surface::~Surface(void)
{
	auto got = windowToSurface.find(static_cast<GLFWwindow*>(m_window));
	if (got == windowToSurface.end())
		util::fatal_throw([](){
			throw std::runtime_error("Can't remove window surface in table");
		});
	windowToSurface.erase(got);
}

template <>
void Vk::Instance::Handle<VkSurfaceKHR>::destroy(Vk::Instance &instance, VkSurfaceKHR surface)
{
	instance.destroy(vkDestroySurfaceKHR, surface);
}

svec2 Vk::Surface::getExtent(void) const
{
	return m_extent;
}

std::optional<svec2> Vk::Surface::isResized(void) const
{
	return m_is_resized;
}

bool Vk::Surface::shouldClose(void) const
{
	return glfwWindowShouldClose(m_window);
}

void Vk::Surface::setMonitor(sb::Monitor &monitor, const sb::Monitor::VideoMode &videoMode)
{
	glfwSetWindowMonitor(m_window, reinterpret_cast<Monitor&>(monitor), 0, 0, videoMode.width, videoMode.height, videoMode.refresh_rate);
}

void Vk::Surface::setWindowed(void)
{
	auto size = getExtent();
	glfwSetWindowMonitor(m_window, nullptr, 64, 64, size.x, size.y, GLFW_DONT_CARE);
}

const std::vector<Input*>& Vk::Surface::getInputs(void) const
{
	return m_inputs;
}

const std::map<std::string, Input*>&Vk::Surface:: getInputsId(void) const
{
	return m_inputs_id;
}

const std::vector<Button*>& Vk::Surface::getButtons(void) const
{
	return m_buttons;
}

const std::map<std::string, Button*>& Vk::Surface::getButtonsId(void) const
{
	return m_buttons_id;
}

const std::vector<Analog*>& Vk::Surface::getAnalogs(void) const
{
	return m_analogs;
}

const std::map<std::string, Analog*>& Vk::Surface::getAnalogsId(void) const
{
	return m_analogs_id;
}

glm::dvec2 Vk::Surface::cursor(void) const
{
	double x, y;

	glfwGetCursorPos(m_window, &x, &y);
	return {x, y};
}

void Vk::Surface::cursorMode(bool show)
{
	glfwSetInputMode(m_window, GLFW_CURSOR, show ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

std::unique_ptr<sb::Surface> Vk::createSurface(const svec2 &extent, const std::string &title)
{
	return std::make_unique<Surface>(m_instance, extent, title);
}

Vk::Monitor::Monitor(GLFWmonitor *monitor) :
	m_monitor(monitor),
	m_video_modes(queryVideoModes())
{
}

Vk::Monitor::~Monitor(void)
{
}

const std::vector<sb::Monitor::VideoMode>& Vk::Monitor::getVideoModes(void) const
{
	return m_video_modes;
}

std::vector<sb::Monitor::VideoMode> Vk::Monitor::queryVideoModes(void) const
{
	// ratio, refresh_rate, total screen pixels
	std::map<double, std::map<size_t, std::map<size_t, sb::Monitor::VideoMode>>> mres;
	int count;
	auto modes = glfwGetVideoModes(m_monitor, &count);

	for (int i = 0; i < count; i++) {
		auto &cur_mode = modes[i];
		sb::Monitor::VideoMode cur;
		cur.width = cur_mode.width;
		cur.height = cur_mode.height;
		cur.refresh_rate = cur_mode.refreshRate,
		cur.red_bits = cur_mode.redBits;
		cur.green_bits = cur_mode.greenBits;
		cur.blue_bits = cur_mode.blueBits;

		double ratio = std::floor((static_cast<double>(cur.width) / static_cast<double>(cur.height)) * 10.0);
		auto ratio_got = mres.find(ratio);
		if (ratio_got == mres.end()) {
			auto [it, suc] = mres.emplace(std::piecewise_construct, std::forward_as_tuple(ratio), std::forward_as_tuple());
			if (!suc)
				throw std::runtime_error("Can't emplace mode");
			ratio_got = it;
		}

		auto refresh_rate_got = ratio_got->second.find(cur.width * cur.height);
		if (refresh_rate_got == ratio_got->second.end()) {
			auto [it, suc] = ratio_got->second.emplace(std::piecewise_construct, std::forward_as_tuple(cur.width * cur.height), std::forward_as_tuple());
			if (!suc)
				throw std::runtime_error("Can't emplace mode");
			refresh_rate_got = it;
		}

		refresh_rate_got->second.emplace(std::piecewise_construct, std::forward_as_tuple(cur.refresh_rate), std::forward_as_tuple(cur));
	}
	std::vector<sb::Monitor::VideoMode> res;
	{
		auto end = mres.rend();
		for (auto it = mres.rbegin(); it != end; it++) {
			{
				auto end = it->second.rend();
				for (auto it_1 = it->second.rbegin(); it_1 != end; it_1++) {
					{
						auto end = it_1->second.rend();
						for (auto it_2 = it_1->second.rbegin(); it_2 != end; it_2++)
							res.emplace_back(it_2->second);
					}
				}
			}
		}
	}

	for (auto &v : res) {
		std::cout << "MODE: " << v.width << " x " << v.height << " @ " << v.refresh_rate << "Hz" << std::endl;
	}

	return res;
}

std::vector<Monitor::Handle> Vk::queryMonitors(void)
{
	std::vector<Monitor::Handle> res;
	int count;
	auto monitors = glfwGetMonitors(&count);

	for (int i = 0; i < count; i++)
		res.emplace_back(std::make_unique<Monitor>(monitors[i]));
	return res;
}

const std::vector<sb::Monitor::Handle>& Vk::getMonitors(void) const
{
	return m_monitors;
}

Vk::PhysicalDevice::PhysicalDevice(VkPhysicalDevice device) :
	m_device(device),
	m_props(get<VkPhysicalDeviceProperties>(vkGetPhysicalDeviceProperties, m_device)),
	m_features(get<VkPhysicalDeviceFeatures>(vkGetPhysicalDeviceFeatures, m_device)),
	m_queue_families(*this)
{
}

Vk::PhysicalDevice::operator VkPhysicalDevice(void) const
{
	return m_device;
}

Vk::PhysicalDevice::Properties::Properties(const VkPhysicalDeviceProperties &props) :
	VkPhysicalDeviceProperties(props)
{
}

size_t Vk::PhysicalDevice::Properties::getAlignment(sb::Shader::DescriptorType type) const
{
	if (type == sb::Shader::DescriptorType::UniformBuffer)
		return limits.minUniformBufferOffsetAlignment;
	else if (type == sb::Shader::DescriptorType::StorageBuffer)
		return limits.minStorageBufferOffsetAlignment;
	else
		throw std::runtime_error("Can't align such descriptor type");
}

const Vk::PhysicalDevice::Properties& Vk::PhysicalDevice::properties(void) const
{
	return m_props;
}

const VkPhysicalDeviceFeatures& Vk::PhysicalDevice::features(void) const
{
	return m_features;
}

const VkPhysicalDeviceFeatures& Vk::PhysicalDevice::requiredFeatures(void)
{
	static const VkPhysicalDeviceFeatures res {
		.geometryShader = true,
		.vertexPipelineStoresAndAtomics = true,
		.fragmentStoresAndAtomics = true
	};

	return res;
}

bool Vk::PhysicalDevice::isCompetent(const sb::Queue::Set &requiredQueues, Vk::Surface &surface) const
{
	auto &req = requiredFeatures();
	auto req_arr_size = sizeof(VkPhysicalDeviceFeatures) / sizeof(VkBool32);
	for (size_t i = 0; i < req_arr_size; i++)
		if (reinterpret_cast<const VkBool32*>(&req)[i] && !reinterpret_cast<const VkBool32*>(&m_features)[i])
			return false;

	Vk::PhysicalDevice::Surface surf(*this, surface);
	for (auto &qp : requiredQueues)
		if (!m_queue_families.indexOf(surf, qp.first, qp.second.size()))
			return false;
	if (surf.formats().size() == 0)
		return false;
	if (surf.presentModes().size() == 0)
		return false;
	if (!areExtensionsSupported())
		return false;
	return true;
}

const util::svec Vk::PhysicalDevice::required_extensions {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

bool Vk::PhysicalDevice::areExtensionsSupported(void) const
{
	std::map<std::string, bool> avail;
	for (auto &a : enumerate<VkExtensionProperties>(vkEnumerateDeviceExtensionProperties, *this, nullptr))
		avail[a.extensionName] = true;

	for (auto &w : required_extensions)
		if (!avail[w])
			return false;
	return true;
}

size_t Vk::PhysicalDevice::getScore(void) const
{
	size_t res = 0;

	if (m_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		res += 1;
	return res;
}

const Vk::PhysicalDevice::QueueFamilies& Vk::PhysicalDevice::queues(void) const
{
	return m_queue_families;
}

Vk::PhysicalDevice::QueueFamilies::QueueFamilies(Vk::PhysicalDevice &device) :
	m_queues(getCollection<VkQueueFamilyProperties>(vkGetPhysicalDeviceQueueFamilyProperties, device))
{
}

const std::vector<VkQueueFamilyProperties>& Vk::PhysicalDevice::QueueFamilies::properties(void) const
{
	return m_queues;
}

std::optional<uint32_t> Vk::PhysicalDevice::QueueFamilies::indexOf(Vk::PhysicalDevice::Surface &surface, sb::Queue::Flag flags, size_t count) const
{
	VkQueueFlags vkFlags = static_cast<std::underlying_type_t<decltype(flags)>>(flags & ~sb::Queue::Flag::Present);
	bool isPresent = !!(flags & sb::Queue::Flag::Present);
	struct BestAttr {
		uint32_t ndx;
		size_t count;
		size_t flag_count;

		bool isBetterThan(const BestAttr &other, size_t want_count) const
		{
			if (count >= want_count && other.count >= want_count) // irrelevant if derired count is reached on both sides
				return flag_count < other.flag_count; // return most specialized
			else {
				if (count < other.count)
					return false;
				if (count == other.count)
					return flag_count < other.flag_count;
				return true; // more queues than other
			}
		}
	};
	std::optional<BestAttr> best;
	uint32_t n = 0;

	for (auto &q : m_queues) {
		auto ndx = n++;
		auto present_support = surface.getSurfaceSupport(ndx);
		if (q.queueCount > 0 && q.queueFlags & vkFlags && (isPresent && present_support)) {
			BestAttr attr {ndx, q.queueCount, 0};
			for (size_t i = 0; i < 32; i++)
				if (q.queueFlags & static_cast<uint32_t>(1 << i))
					attr.flag_count++;
			if (present_support)
				attr.flag_count++;

			if (best) {
				if (attr.isBetterThan(*best, count))
					best = attr;
			} else
				best = attr;
		}
	}
	if (best)
		return best->ndx;
	else
		return std::nullopt;
}

Vk::PhysicalDevice::Surface::Surface(const PhysicalDevice &device, Vk::Surface &surface) :
	m_capabilities(create<VkSurfaceCapabilitiesKHR>(vkGetPhysicalDeviceSurfaceCapabilitiesKHR, device, surface)),
	m_formats(enumerate<VkSurfaceFormatKHR>(vkGetPhysicalDeviceSurfaceFormatsKHR, device, surface)),
	m_present_modes(enumerate<VkPresentModeKHR>(vkGetPhysicalDeviceSurfacePresentModesKHR, device, surface)),
	m_device(device),
	m_vk_surface(surface)
{
}

const VkSurfaceCapabilitiesKHR& Vk::PhysicalDevice::Surface::capabilities(void) const
{
	return m_capabilities;
}

const std::vector<VkSurfaceFormatKHR>& Vk::PhysicalDevice::Surface::formats(void) const
{
	return m_formats;
}

const std::vector<VkPresentModeKHR>& Vk::PhysicalDevice::Surface::presentModes(void) const
{
	return m_present_modes;
}

const VkSurfaceFormatKHR& Vk::PhysicalDevice::Surface::chooseFormat(void) const
{
	for (auto &f : m_formats)
		if (f.format == VK_FORMAT_B8G8R8A8_SRGB && f.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
			return f;
	return *m_formats.begin();
}

VkPresentModeKHR Vk::PhysicalDevice::Surface::choosePresentMode(void) const
{
	for (auto &p : m_present_modes)
		if (p == VK_PRESENT_MODE_MAILBOX_KHR)
			return p;
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Vk::PhysicalDevice::Surface::chooseExtent(VkExtent2D baseExtent) const
{
	if (m_capabilities.currentExtent.width != UINT32_MAX)
		return m_capabilities.currentExtent;
	else {
		VkExtent2D res = baseExtent;

		res.width = std::clamp(res.width, m_capabilities.minImageExtent.width, m_capabilities.maxImageExtent.width);
		res.height = std::clamp(res.width, m_capabilities.minImageExtent.height, m_capabilities.maxImageExtent.height);

		return res;
	}
}

bool Vk::PhysicalDevice::Surface::getSurfaceSupport(uint32_t queueFamilyIndex) const
{
	return create<VkBool32>(vkGetPhysicalDeviceSurfaceSupportKHR, m_device, queueFamilyIndex, m_vk_surface);
}

Vk::PhysicalDevice::Surface::operator VkSurfaceKHR(void) const
{
	return m_vk_surface;
}

Vk::PhysicalDevices::PhysicalDevices(Vk::Instance &instance) :
	m_devices(enumerate(instance))
{
}

const Vk::PhysicalDevice& Vk::PhysicalDevices::getBest(const sb::Queue::Set &requiredQueues, Vk::Surface &surface) const
{
	std::map<size_t, std::reference_wrapper<const PhysicalDevice>> cands;

	for (auto &p : m_devices)
		if (p.isCompetent(requiredQueues, surface))
			cands.emplace(p.getScore(), p);
	if (cands.size() == 0)
		throw std::runtime_error("No compatible GPU found");
	return cands.rbegin()->second.get();
}

std::vector<Vk::PhysicalDevice> Vk::PhysicalDevices::enumerate(Instance &instance)
{
	auto devices = Vk::enumerate<VkPhysicalDevice>(vkEnumeratePhysicalDevices, instance);

	std::vector<Vk::PhysicalDevice> res;
	res.reserve(devices.size());

	for (auto &d : devices)
		res.emplace_back(d);
	return res;
}

Vk::Allocator::Allocator(Vk::Device &device) :
	Vk::Handle<VmaAllocator>(create(device)),
	m_device(device)
{
}

Vk::VmaBuffer Vk::Allocator::createBuffer(const VkBufferCreateInfo &bufferCreateInfo, const VmaAllocationCreateInfo &allocationCreateInfo)
{
	VmaAllocation resalloc;
	VkBuffer resbuffer;
	Vk::assert(vmaCreateBuffer(*this, &bufferCreateInfo, &allocationCreateInfo, &resbuffer, &resalloc, nullptr));

	return VmaBuffer(m_device, resbuffer, resalloc);
}

VmaAllocator Vk::Allocator::create(Device &device)
{
	VmaAllocatorCreateInfo createInfo {};

	createInfo.physicalDevice = device.physical();
	createInfo.device = device;

	return Vk::create<VmaAllocator>(vmaCreateAllocator, &createInfo);
}

template <>
void Vk::Handle<VmaAllocator>::destroy(VmaAllocator allocator)
{
	vmaDestroyAllocator(allocator);
}

Vk::Device::Device(Instance &instance, const PhysicalDevice &physicalDevice, const sbQueueFamilyMapping& queueFamilyMapping, const sbQueueMapping &queueMapping, VkDevice device) :
	Vk::Handle<VkDevice>(device),
	m_instance(instance),
	m_physical(physicalDevice),
	m_queue_family_mapping(queueFamilyMapping),
	m_queue_mapping(queueMapping),
	m_allocator(*this),
	m_dynamic_formats(getDynamicFormats())
{
}

Vk::Device::~Device(void)
{
}

VkFormat Vk::Device::sbFormatToVk(sb::Format format) const
{
	static const std::map<sb::Format, VkFormat> table {
		{sb::Format::bgra4_unorm_pack16, VK_FORMAT_B4G4R4A4_UNORM_PACK16},
		{sb::Format::r5g6b5_unorm_pack16, VK_FORMAT_R5G6B5_UNORM_PACK16},
		{sb::Format::a1rgb5_unorm_pack16, VK_FORMAT_A1R5G5B5_UNORM_PACK16},

		{sb::Format::r8_unorm, VK_FORMAT_R8_UNORM},
		{sb::Format::r8_snorm, VK_FORMAT_R8_SNORM},
		{sb::Format::r8_uint, VK_FORMAT_R8_UINT},
		{sb::Format::r8_sint, VK_FORMAT_R8_SINT},

		{sb::Format::rg8_unorm, VK_FORMAT_R8G8_UNORM},
		{sb::Format::rg8_snorm, VK_FORMAT_R8G8_SNORM},
		{sb::Format::rg8_uint, VK_FORMAT_R8G8_UINT},
		{sb::Format::rg8_sint, VK_FORMAT_R8G8_SINT},

		{sb::Format::rgba8_unorm, VK_FORMAT_R8G8B8A8_UNORM},
		{sb::Format::rgba8_snorm, VK_FORMAT_R8G8B8A8_SNORM},
		{sb::Format::rgba8_uint, VK_FORMAT_R8G8B8A8_UINT},
		{sb::Format::rgba8_sint, VK_FORMAT_R8G8B8A8_SINT},
		{sb::Format::rgba8_srgb, VK_FORMAT_R8G8B8A8_SRGB},

		{sb::Format::bgra8_unorm, VK_FORMAT_B8G8R8A8_UNORM},
		{sb::Format::bgra8_srgb, VK_FORMAT_B8G8R8A8_SRGB},

		{sb::Format::abgr8_unorm_pack32, VK_FORMAT_A8B8G8R8_UNORM_PACK32},
		{sb::Format::abgr8_snorm_pack32, VK_FORMAT_A8B8G8R8_SNORM_PACK32},
		{sb::Format::abgr8_uint_pack32, VK_FORMAT_A8B8G8R8_UINT_PACK32},
		{sb::Format::abgr8_sint_pack32, VK_FORMAT_A8B8G8R8_SINT_PACK32},
		{sb::Format::abgr8_srgb_pack32, VK_FORMAT_A8B8G8R8_SRGB_PACK32},

		{sb::Format::a2bgr10_unorm_pack32, VK_FORMAT_A2B10G10R10_UNORM_PACK32},
		{sb::Format::a2bgr10_uint_pack32, VK_FORMAT_A2B10G10R10_UINT_PACK32},

		{sb::Format::r16_uint, VK_FORMAT_R16_UINT},
		{sb::Format::r16_sint, VK_FORMAT_R16_SINT},
		{sb::Format::r16_sfloat, VK_FORMAT_R16_SFLOAT},

		{sb::Format::rg16_uint, VK_FORMAT_R16G16_UINT},
		{sb::Format::rg16_sint, VK_FORMAT_R16G16_SINT},
		{sb::Format::rg16_sfloat, VK_FORMAT_R16G16_SFLOAT},

		{sb::Format::rgba16_uint, VK_FORMAT_R16G16B16A16_UINT},
		{sb::Format::rgba16_sint, VK_FORMAT_R16G16B16A16_SINT},
		{sb::Format::rgba16_sfloat, VK_FORMAT_R16G16B16A16_SFLOAT},

		{sb::Format::r32_uint, VK_FORMAT_R32_UINT},
		{sb::Format::r32_sint, VK_FORMAT_R32_SINT},
		{sb::Format::r32_sfloat, VK_FORMAT_R32_SFLOAT},

		{sb::Format::rg32_uint, VK_FORMAT_R32G32_UINT},
		{sb::Format::rg32_sint, VK_FORMAT_R32G32_SINT},
		{sb::Format::rg32_sfloat, VK_FORMAT_R32G32_SFLOAT},

		{sb::Format::rgba32_uint, VK_FORMAT_R32G32B32A32_UINT},
		{sb::Format::rgba32_sint, VK_FORMAT_R32G32B32A32_SINT},
		{sb::Format::rgba32_sfloat, VK_FORMAT_R32G32B32A32_SFLOAT},

		{sb::Format::d16_unorm, VK_FORMAT_D16_UNORM},
		{sb::Format::d32_sfloat, VK_FORMAT_D32_SFLOAT}
	};

	auto got = table.find(format);
	if (got != table.end())
		return got->second;
	return m_dynamic_formats.at(format);
}

bool Vk::Device::isDepthFormatSupportedSplAtt(VkFormat format)
{
	VkImageFormatProperties props;
	auto res = vkGetPhysicalDeviceImageFormatProperties(m_physical, format,
	VK_IMAGE_TYPE_2D, VK_IMAGE_TILING_OPTIMAL,
	VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
	0, &props);

	return res == VK_SUCCESS;
}

std::map<sb::Format, VkFormat> Vk::Device::getDynamicFormats(void)
{
	std::map<sb::Format, VkFormat> res {
		{sb::Format::d24un_or_32sf_spl_att, VK_FORMAT_UNDEFINED},
		{sb::Format::d32sf_or_24un_spl_att, VK_FORMAT_UNDEFINED},
		{sb::Format::d24un_or_32sf_spl_att_sfb, VK_FORMAT_UNDEFINED},
		{sb::Format::d32sf_or_24un_spl_att_sfb, VK_FORMAT_UNDEFINED},
		{sb::Format::d24un_or_32sf_spl_att_s8_uint, VK_FORMAT_UNDEFINED},
		{sb::Format::d32sf_or_24un_spl_att_s8_uint, VK_FORMAT_UNDEFINED}
	};

	auto x8_d24_unorm = isDepthFormatSupportedSplAtt(VK_FORMAT_X8_D24_UNORM_PACK32);
	auto d32_sfloat = isDepthFormatSupportedSplAtt(VK_FORMAT_D32_SFLOAT);
	auto x8_d24_unorm_s8_uint = isDepthFormatSupportedSplAtt(VK_FORMAT_D24_UNORM_S8_UINT);
	auto d32_sfloat_s8_uint = isDepthFormatSupportedSplAtt(VK_FORMAT_D32_SFLOAT_S8_UINT);

	if (x8_d24_unorm)
		res.at(sb::Format::d24un_or_32sf_spl_att) = VK_FORMAT_X8_D24_UNORM_PACK32;
	else if (d32_sfloat)
		res.at(sb::Format::d24un_or_32sf_spl_att) = VK_FORMAT_D32_SFLOAT;

	if (d32_sfloat)
		res.at(sb::Format::d32sf_or_24un_spl_att) = VK_FORMAT_D32_SFLOAT;
	else if (x8_d24_unorm)
		res.at(sb::Format::d32sf_or_24un_spl_att) = VK_FORMAT_X8_D24_UNORM_PACK32;


	if (x8_d24_unorm_s8_uint)
		res.at(sb::Format::d24un_or_32sf_spl_att_s8_uint) = VK_FORMAT_D24_UNORM_S8_UINT;
	else if (d32_sfloat_s8_uint)
		res.at(sb::Format::d24un_or_32sf_spl_att_s8_uint) = VK_FORMAT_D32_SFLOAT_S8_UINT;

	if (d32_sfloat_s8_uint)
		res.at(sb::Format::d32sf_or_24un_spl_att_s8_uint) = VK_FORMAT_D32_SFLOAT_S8_UINT;
	else if (x8_d24_unorm_s8_uint)
		res.at(sb::Format::d32sf_or_24un_spl_att_s8_uint) = VK_FORMAT_D24_UNORM_S8_UINT;


	res.at(sb::Format::d24un_or_32sf_spl_att_sfb) = res.at(sb::Format::d24un_or_32sf_spl_att);
	if (res.at(sb::Format::d24un_or_32sf_spl_att_sfb) == VK_FORMAT_UNDEFINED)
		res.at(sb::Format::d24un_or_32sf_spl_att_sfb) = res.at(sb::Format::d24un_or_32sf_spl_att_s8_uint);

	res.at(sb::Format::d32sf_or_24un_spl_att_sfb) = res.at(sb::Format::d32sf_or_24un_spl_att);
	if (res.at(sb::Format::d32sf_or_24un_spl_att_sfb) == VK_FORMAT_UNDEFINED)
		res.at(sb::Format::d32sf_or_24un_spl_att_sfb) = res.at(sb::Format::d32sf_or_24un_spl_att_s8_uint);

	return res;
}

template <>
void Vk::Handle<VkDevice>::destroy(VkDevice device)
{
	vkDeviceWaitIdle(device);
	vkDestroyDevice(device, static_cast<Device&>(*this).m_instance.m_vk.getAllocator());
}

const Vk::PhysicalDevice& Vk::Device::physical(void) const
{
	return m_physical;
}

Vk::Allocator& Vk::Device::allocator(void)
{
	return m_allocator;
}

void Vk::Device::newSurface(sb::Surface &surface)
{
	auto size = m_physical.queues().properties().size();
	auto surf = Vk::PhysicalDevice::Surface(m_physical, reinterpret_cast<Vk::Surface&>(surface));
	for (size_t i = 0; i < size; i++)
		if (surf.getSurfaceSupport(i))
			return;
	throw std::runtime_error("Device is not compatible with new surface");
}

std::unique_ptr<sb::Queue> Vk::Device::getQueue(Queue::Flag flags, size_t index)
{
	auto queue = m_queue_mapping.at(std::make_pair(flags, index));
	VkQueue res;
	vkGetDeviceQueue(*this, queue.first, queue.second, &res);
	auto got = std::make_pair(queue.first, res);

	return std::make_unique<Queue>(*this, got.first, got.second);
}

std::unique_ptr<sb::Swapchain> Vk::Device::createSwapchain(sb::Surface &surface, const svec2 &extent, size_t desiredImageCount, sb::Image::Usage usage, sb::Queue &queue)
{
	auto &phys = physical();
	auto phys_surface = Vk::PhysicalDevice::Surface(phys, reinterpret_cast<Vk::Surface&>(surface));
	auto &surf_cap = phys_surface.capabilities();
	VkQueueFamilyIndex queueFamilyIndex = reinterpret_cast<Queue&>(queue).getFamilyIndex();
	auto format = phys_surface.chooseFormat();

	VkSwapchainCreateInfoKHR ci {};
	ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	ci.surface = phys_surface;
	ci.minImageCount = std::clamp(static_cast<uint32_t>(desiredImageCount), surf_cap.minImageCount, surf_cap.maxImageCount);
	ci.imageFormat = format.format;
	ci.imageColorSpace = format.colorSpace;
	ci.imageExtent = VkExtent2D{std::clamp(static_cast<uint32_t>(extent.x), std::max(surf_cap.minImageExtent.width, static_cast<uint32_t>(1)), surf_cap.maxImageExtent.width),
		std::clamp(static_cast<uint32_t>(extent.y), std::max(surf_cap.minImageExtent.height, static_cast<uint32_t>(1)), surf_cap.maxImageExtent.height)};
	ci.imageArrayLayers = 1;
	ci.imageUsage = util::enum_underlying(usage);
	ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	ci.queueFamilyIndexCount = 1;
	ci.pQueueFamilyIndices = &queueFamilyIndex;
	ci.preTransform = phys_surface.capabilities().currentTransform;
	ci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	ci.presentMode = phys_surface.choosePresentMode();
	ci.clipped = VK_TRUE;
	ci.oldSwapchain = VK_NULL_HANDLE;

	return std::make_unique<Swapchain>(*this, createVk(vkCreateSwapchainKHR, ci), format, svec2(ci.imageExtent.width, ci.imageExtent.height));
}

std::unique_ptr<sb::Image> Vk::Device::createImage(sb::Image::Type type, Format format, sb::Image::Sample sample, const svec3 &extent, size_t layers, const sb::Image::MipmapLevels &mipLevels, sb::Image::Usage usage, sb::Queue &queue)
{
	VkQueueFamilyIndex queueFamilyIndex = reinterpret_cast<Queue&>(queue).getFamilyIndex();

	VkImageCreateInfo ici {};
	ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	ici.imageType = Vk::Image::sbImageTypeToVk(type);
	ici.format = sbFormatToVk(format);
	ici.extent = VkExtent3D {static_cast<uint32_t>(extent.x), static_cast<uint32_t>(extent.y), static_cast<uint32_t>(extent.z)};
	ici.mipLevels = mipLevels.isFull ? static_cast<uint32_t>(std::floor(std::log2(std::max(std::max(extent.x, extent.y), extent.z))) + 1.0) : static_cast<uint32_t>(mipLevels.levels);
	ici.arrayLayers = layers;
	ici.samples = static_cast<VkSampleCountFlagBits>(util::enum_underlying(sample));
	ici.tiling = VK_IMAGE_TILING_OPTIMAL;
	ici.usage = util::enum_underlying(usage);
	ici.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	ici.queueFamilyIndexCount = 1;
	ici.pQueueFamilyIndices = &queueFamilyIndex;
	ici.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

	VmaAllocationCreateInfo aci {};
	aci.usage = VMA_MEMORY_USAGE_GPU_ONLY;

	VkImage vk_image;
	VmaAllocation allocation;
	Vk::assert(vmaCreateImage(allocator(), &ici, &aci, &vk_image, &allocation, nullptr));

	auto image = Vk::Image(*this, vk_image, allocation);
	auto view = Vk::ImageView(*this, image, ici.format, type, extent, ComponentSwizzle::Identity, Image::sbFormatToImageAspectFlags(format), Range(0, ici.arrayLayers), Range(0, ici.mipLevels));

	return std::make_unique<ImageAllocView>(std::move(image), std::move(view));
}

std::unique_ptr<sb::Semaphore> Vk::Device::createSemaphore(void)
{
	VkSemaphoreCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	return std::make_unique<Semaphore>(*this, createVk(vkCreateSemaphore, ci));
}


std::unique_ptr<sb::Fence> Vk::Device::createFence(bool isSignaled)
{
	VkFenceCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	ci.flags = isSignaled ? VK_FENCE_CREATE_SIGNALED_BIT : 0;

	return std::make_unique<Fence>(*this, createVk(vkCreateFence, ci));
}

std::unique_ptr<sb::Buffer> Vk::Device::createBuffer(size_t size, sb::Buffer::Location location, sb::Buffer::Usage usage, sb::Queue &queue)
{
	VkQueueFamilyIndex familyIndex = reinterpret_cast<Queue&>(queue).getFamilyIndex();

	VkBufferCreateInfo bci {};
	bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bci.size = size;
	bci.usage = util::enum_underlying(usage);
	bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	bci.queueFamilyIndexCount = 1;
	bci.pQueueFamilyIndices = &familyIndex;

	VmaAllocationCreateInfo aci {};
	aci.usage = location == sb::Buffer::Location::Device ? VMA_MEMORY_USAGE_GPU_ONLY : VMA_MEMORY_USAGE_CPU_TO_GPU;
	aci.requiredFlags = location == sb::Buffer::Location::Device ? 0 : (VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);

	return std::make_unique<VmaBuffer>(allocator().createBuffer(bci, aci));
}

std::unique_ptr<sb::Model> Vk::Device::createModel(sb::Buffer &vertexBuffer, size_t vertexCount)
{
	return std::make_unique<Model>(reinterpret_cast<VmaBuffer&>(vertexBuffer), vertexCount);
}

std::unique_ptr<sb::Model> Vk::Device::createModelIndexed(sb::Buffer &vertexBuffer, sb::Buffer &indexBuffer, sb::Model::IndexType indexType, size_t indexCount)
{
	return std::make_unique<ModelIndexed>(reinterpret_cast<VmaBuffer&>(vertexBuffer), reinterpret_cast<VmaBuffer&>(indexBuffer), indexType == sb::Model::IndexType::Uint16 ? VK_INDEX_TYPE_UINT16 : VK_INDEX_TYPE_UINT32, indexCount);
}

std::unique_ptr<sb::Sampler> Vk::Device::createSampler(Filter magFilter, Filter minFilter, bool normalizedCoordinates, const sb::Sampler::AddressModeUVW &addressMode, BorderColor borderColor, const std::optional<CompareOp> &compare, sb::Sampler::MipmapMode mipmapMode, float minLod, float maxLod, float mipLodBias, const std::optional<float> &anisotropy)
{
	VkSamplerCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	ci.magFilter = static_cast<VkFilter>(util::enum_underlying(magFilter));
	ci.minFilter = static_cast<VkFilter>(util::enum_underlying(minFilter));
	ci.mipmapMode = static_cast<VkSamplerMipmapMode>(util::enum_underlying(mipmapMode));
	ci.addressModeU = static_cast<VkSamplerAddressMode>(util::enum_underlying(addressMode.x));
	ci.addressModeV = static_cast<VkSamplerAddressMode>(util::enum_underlying(addressMode.y));
	ci.addressModeW = static_cast<VkSamplerAddressMode>(util::enum_underlying(addressMode.z));
	ci.mipLodBias = mipLodBias;
	ci.anisotropyEnable = anisotropy.has_value();
	ci.maxAnisotropy = *anisotropy;
	ci.compareEnable = compare.has_value();
	ci.compareOp = static_cast<VkCompareOp>(util::enum_underlying(*compare));
	ci.minLod = minLod;
	ci.maxLod = maxLod;
	ci.borderColor = static_cast<VkBorderColor>(util::enum_underlying(borderColor));
	ci.unnormalizedCoordinates = !normalizedCoordinates;

	return std::make_unique<Sampler>(*this, createVk(vkCreateSampler, ci));
}

std::unique_ptr<sb::RenderPass> Vk::Device::createRenderPass(sb::rs::RenderPass &renderpass)
{
	return std::make_unique<RenderPass>(*this, renderpass);
}

std::unique_ptr<sb::Shader> Vk::Device::createShader(rs::Shader &shader)
{
	return std::make_unique<Shader>(*this, shader);
}

std::unique_ptr<sb::Shader::DescriptorSet::Layout> Vk::Device::createDescriptorSetLayout(const sb::Shader::DescriptorSet::Layout::Description &desc)
{
	return std::make_unique<DescriptorSetLayout>(*this, desc);
}

std::unique_ptr<sb::Device> Vk::createDevice(sb::Surface &surface, const sb::Queue::Set &requiredQueues)
{
	auto &vk_surf = reinterpret_cast<Surface&>(surface);
	auto devs = m_instance.enumerateDevices();
	auto &phys = devs.getBest(requiredQueues, vk_surf);
	auto surf_prop = Vk::PhysicalDevice::Surface(phys, vk_surf);

	sbQueueFamilyMapping queueFamilyMapping;
	sbQueueMapping queueMapping;
	struct QueueAlloc {
		size_t count = 0;
		std::vector<float> prios;
		bool is_saturated = false;
	};
	std::map<VkQueueFamilyIndex, QueueAlloc> allocated;

	for (auto &qp : requiredQueues) {
		auto family_ndx = *phys.queues().indexOf(surf_prop, qp.first, qp.second.size());
		auto &alloc = allocated[family_ndx];
		auto &qf_prop = phys.queues().properties().at(family_ndx);
		queueFamilyMapping.emplace(std::piecewise_construct, std::forward_as_tuple(qp.first), std::forward_as_tuple(family_ndx));
		sbQueueIndex n = 0;
		for (auto &prio : qp.second) {
			auto sb_ndx = n++;
			auto vk_ndx = alloc.count++;
			if (!alloc.is_saturated)
				alloc.prios.emplace_back(prio);
			if (alloc.count == qf_prop.queueCount) {
				alloc.count = 0;
				alloc.is_saturated = true;
			}
			queueMapping.emplace(std::piecewise_construct, std::forward_as_tuple(qp.first, sb_ndx), std::forward_as_tuple(family_ndx, vk_ndx));
		}
	}

	std::vector<VkDeviceQueueCreateInfo> queues;
	for (auto &ap : allocated) {
		VkDeviceQueueCreateInfo ci {};
		ci.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		ci.queueFamilyIndex = ap.first;
		ci.queueCount = ap.second.prios.size();
		ci.pQueuePriorities = ap.second.prios.data();
		queues.emplace_back(ci);
	}

	VkDeviceCreateInfo createInfo {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = queues.size();
	createInfo.pQueueCreateInfos = queues.data();
	createInfo.pEnabledFeatures = &Vk::PhysicalDevice::requiredFeatures();

	auto cexts = PhysicalDevice::required_extensions.c_strs();
	createInfo.enabledExtensionCount = cexts.size();
	createInfo.ppEnabledExtensionNames = cexts.data();

	return std::make_unique<Device>(m_instance, phys, queueFamilyMapping, queueMapping, Vk::create<VkDevice>(vkCreateDevice, phys, &createInfo, getAllocator()));
}

Vk::Allocation::Allocation(Allocator &allocator, VmaAllocation alloc) :
	Allocator::Handle<VmaAllocation>(allocator, alloc)
{
}

template <>
void Vk::Allocator::Handle<VmaAllocation>::destroy(Allocator &allocator, VmaAllocation alloc)
{
	vmaFreeMemory(allocator, alloc);
}

void* Vk::Allocation::map(void)
{
	void *res;

	Vk::assert(vmaMapMemory(static_cast<Allocator&>(*this), *this, &res));
	return res;
}

void Vk::Allocation::unmap(void)
{
	vmaUnmapMemory(static_cast<Allocator&>(*this), *this);
}

Vk::Buffer::Buffer(Vk::Device &dev, VkBuffer buffer) :
	Device::Handle<VkBuffer>(dev, buffer)
{
}

template <>
void Vk::Device::Handle<VkBuffer>::destroy(Vk::Device &device, VkBuffer buffer)
{
	device.destroy(vkDestroyBuffer, buffer);
}

Vk::VmaBuffer::VmaBuffer(Device &dev, VkBuffer buffer, VmaAllocation allocation) :
	Allocation(dev.allocator(), allocation),
	Vk::Buffer(dev, buffer)
{
}

Vk::VmaBuffer::~VmaBuffer(void)
{
}

void Vk::VmaBuffer::write(size_t off, size_t size, const void *data)
{
	auto mapped = map();
	std::memcpy(static_cast<char*>(mapped) + off, data, size);
	unmap();
}

Vk::Image::Image(Device &dev, VkImage image, VmaAllocation allocation) :
	Allocation(dev.allocator(), allocation),
	Device::Handle<VkImage>(dev, image)
{
}

template <>
void Vk::Device::Handle<VkImage>::destroy(Vk::Device &device, VkImage image)
{
	device.destroy(vkDestroyImage, image);
}

sb::Image::Aspect Vk::Image::sbFormatToImageAspectFlags(sb::Format format)
{
	static const std::set<sb::Format> depthTable {
		sb::Format::d16_unorm,
		sb::Format::d32_sfloat,
		sb::Format::d24un_or_32sf_spl_att,
		sb::Format::d32sf_or_24un_spl_att,
		sb::Format::d24un_or_32sf_spl_att_sfb,
		sb::Format::d32sf_or_24un_spl_att_sfb
	};
	static const std::set<sb::Format> stencilTable {
	};
	static const std::set<sb::Format> depthStencilTable {
		sb::Format::d24un_or_32sf_spl_att_s8_uint,
		sb::Format::d32sf_or_24un_spl_att_s8_uint
	};

	if (depthTable.find(format) != depthTable.end())
		return sb::Image::Aspect::Depth;
	if (stencilTable.find(format) != stencilTable.end())
		return sb::Image::Aspect::Stencil;
	if (depthStencilTable.find(format) != depthStencilTable.end())
		return sb::Image::Aspect::Depth | sb::Image::Aspect::Stencil;
	return sb::Image::Aspect::Color;
}

VkImageType Vk::Image::sbImageTypeToVk(sb::Image::Type type)
{
	static const std::map<sb::Image::Type, VkImageType> table {
		{sb::Image::Type::Image1D, VK_IMAGE_TYPE_1D},
		{sb::Image::Type::Image2D, VK_IMAGE_TYPE_2D},
		{sb::Image::Type::Image3D, VK_IMAGE_TYPE_3D},
		{sb::Image::Type::Cube, VK_IMAGE_TYPE_2D},
		{sb::Image::Type::Image1DArray, VK_IMAGE_TYPE_1D},
		{sb::Image::Type::Image2DArray, VK_IMAGE_TYPE_2D},
		{sb::Image::Type::CubeArray, VK_IMAGE_TYPE_2D}
	};

	return table.at(type);
}

Vk::ImageView::ImageView(Device &dev, VkImage image, VkFormat imageFormat, sb::Image::Type type, const svec3 &extent, const ComponentMapping &components, Aspect aspect, const Range &arrayRange, const Range &mipRange) :
	Device::Handle<VkImageView>(dev, create(dev, image, imageFormat, type, components, aspect, arrayRange, mipRange)),
	m_image(image),
	m_image_format(imageFormat),
	m_extent(extent),
	m_components(components),
	m_aspect(aspect),
	m_array_range(arrayRange),
	m_mip_range(mipRange)
{
}

Vk::ImageView::~ImageView(void)
{
}

VkImageView Vk::ImageView::create(Device &dev, VkImage image, VkFormat imageFormat, sb::Image::Type type, const ComponentMapping &components, Aspect aspect, const Range &arrayRange, const Range &mipRange)
{
	VkImageViewCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	ci.image = image;
	ci.viewType = static_cast<VkImageViewType>(util::enum_underlying(type));
	ci.format = imageFormat;
	ci.components.r = static_cast<VkComponentSwizzle>(util::enum_underlying(components.r));
	ci.components.g = static_cast<VkComponentSwizzle>(util::enum_underlying(components.g));
	ci.components.b = static_cast<VkComponentSwizzle>(util::enum_underlying(components.b));
	ci.components.a = static_cast<VkComponentSwizzle>(util::enum_underlying(components.a));
	ci.subresourceRange.aspectMask = util::enum_underlying(aspect);
	ci.subresourceRange.baseArrayLayer = arrayRange.off;
	ci.subresourceRange.layerCount = arrayRange.size;
	ci.subresourceRange.baseMipLevel = mipRange.off;
	ci.subresourceRange.levelCount = mipRange.size;

	return dev.createVk(vkCreateImageView, ci);
}

template <>
void Vk::Device::Handle<VkImageView>::destroy(Vk::Device &device, VkImageView imageView)
{
	device.destroy(vkDestroyImageView, imageView);
}

std::unique_ptr<sb::Image> Vk::ImageView::createView(sb::Image::Type type, const ComponentMapping &components, Aspect aspect, const Range &arrayRange, const Range &mipRange) const
{
	return std::make_unique<Vk::ImageView>(getDep(), m_image, m_image_format, type, deriveExtent(mipRange.off), deriveComponents(components), deriveAspect(aspect), deriveRange(m_array_range, arrayRange), deriveRange(m_mip_range, mipRange));
}

size_t Vk::ImageView::getArrayLayers(void) const
{
	return m_array_range.size;
}

size_t Vk::ImageView::getMipLevels(void) const
{
	return m_mip_range.size;
}

const svec3& Vk::ImageView::getExtent(void) const
{
	return m_extent;
}

svec3 Vk::ImageView::deriveExtent(size_t mipmapOff) const
{
	auto nextDim = [](size_t curDim) {
		return std::max(curDim / static_cast<size_t>(2), static_cast<size_t>(1));
	};
	auto res = m_extent;
	for (size_t i = 0; i < mipmapOff; i++) {
		res.x = nextDim(res.x);
		res.y = nextDim(res.y);
		res.z = nextDim(res.z);
	}
	return res;
}

ComponentMapping Vk::ImageView::deriveComponents(const ComponentMapping &newMapping) const
{
	return ComponentMapping(
		deriveComponent(&ComponentMapping::x, newMapping),
		deriveComponent(&ComponentMapping::y, newMapping),
		deriveComponent(&ComponentMapping::z, newMapping),
		deriveComponent(&ComponentMapping::w, newMapping)
	);
}

ComponentSwizzle Vk::ImageView::deriveComponent(ComponentSwizzle ComponentMapping::* baseLoc, const ComponentMapping &newMapping) const
{
	static const std::map<ComponentSwizzle, ComponentSwizzle ComponentMapping::*> table {
		{ComponentSwizzle::R, &ComponentMapping::x},
		{ComponentSwizzle::G, &ComponentMapping::y},
		{ComponentSwizzle::B, &ComponentMapping::z},
		{ComponentSwizzle::A, &ComponentMapping::w}
	};

	auto newComp = newMapping.*baseLoc;
	if (newComp == ComponentSwizzle::Identity)
		return m_components.*baseLoc;
	else if (newComp == ComponentSwizzle::Zero || newComp == ComponentSwizzle::One)
		return newComp;
	else
		return m_components.*table.at(newComp);
}

sb::Image::Aspect Vk::ImageView::deriveAspect(Aspect newAspect) const
{
	return m_aspect | newAspect;
}

Range Vk::ImageView::deriveRange(const Range &baseRange, const Range &newRange)
{
	if (newRange.isWhole)
		return Range(baseRange.off + newRange.off, baseRange.size - newRange.off);
	else
		return Range(baseRange.off + newRange.off, newRange.size);
}

Vk::ImageAllocView::ImageAllocView(Vk::Image &&image, ImageView &&view) :
	Vk::Image(std::move(image)),
	ImageView(std::move(view))
{
}

Vk::ImageAllocView::~ImageAllocView(void)
{
}

Vk::Framebuffer::Framebuffer(Device &dev, VkFramebuffer framebuffer, RenderPass &render_pass, std::vector<DescriptorSet> &&input_attachments) :
	Device::Handle<VkFramebuffer>(dev, framebuffer),
	m_render_pass(render_pass),
	m_input_attachments(std::move(input_attachments))
{
}

Vk::Framebuffer::~Framebuffer(void)
{
}

template <>
void Vk::Device::Handle<VkFramebuffer>::destroy(Vk::Device &device, VkFramebuffer framebuffer)
{
	device.destroy(vkDestroyFramebuffer, framebuffer);
}

VkDescriptorType Vk::descriptorType(sb::Shader::DescriptorType type)
{
	return static_cast<VkDescriptorType>(util::enum_underlying(type));
}

Vk::DescriptorSetLayout::DescriptorSetLayout(Vk::Device &dev, const sb::Shader::DescriptorSet::Layout::Description &desc) :
	Device::Handle<VkDescriptorSetLayout>(dev, create(dev, desc)),
	m_desc(desc)
{
	for (auto &b : getDescription())
		if (b.isMapped()) {
			m_buffer_size = util::align_dyn(m_buffer_size, dev.physical().properties().getAlignment(b.descriptorType));
			if (b.descriptorType == sb::Shader::DescriptorType::UniformBuffer) {
				m_uniform_off = m_buffer_size;
				m_uniform_size = b.descriptorCount;
			} else if (b.descriptorType == sb::Shader::DescriptorType::StorageBuffer) {
				m_storage_off = m_buffer_size;
				m_storage_size = b.descriptorCount;
			} else
				throw std::runtime_error("Unkown mapped buffer type");
			m_buffer_size += b.descriptorCount;
		}
}

Vk::DescriptorSetLayout::~DescriptorSetLayout(void)
{
}

VkDescriptorSetLayout Vk::DescriptorSetLayout::create(Device &device, const sb::Shader::DescriptorSet::Layout::Description &desc)
{
	std::vector<VkDescriptorSetLayoutBinding> bindings;
	for (auto &b : desc)
		bindings.emplace_back(bindingtoVk(b));

	VkDescriptorSetLayoutCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	ci.bindingCount = bindings.size();
	ci.pBindings = bindings.data();

	if (ci.bindingCount == 0)
		return VK_NULL_HANDLE;
	else
		return device.createVk(vkCreateDescriptorSetLayout, ci);
}

VkDescriptorSetLayoutBinding Vk::DescriptorSetLayout::bindingtoVk(const sb::Shader::DescriptorSet::Layout::DescriptionBinding &b)
{
	VkDescriptorSetLayoutBinding r {};
	r.binding = b.binding;
	r.descriptorType = descriptorType(b.descriptorType);
	r.descriptorCount = b.descriptorCount;
	if (b.isMapped())
		r.descriptorCount = 1;
	for (auto &s : b.stages)
		r.stageFlags |= Vk::Shader::sbStageToVk(s);
	return r;
}

template <>
void Vk::Device::Handle<VkDescriptorSetLayout>::destroy(Vk::Device &device, VkDescriptorSetLayout layout)
{
	device.destroy(vkDestroyDescriptorSetLayout, layout);
}

Vk::DescriptorSet::DescriptorSet(Vk::Device &dev, const Vk::DescriptorSetLayout &layout, sb::Queue *queue) :
	m_layout(layout),
	m_descriptor_pool(dev, createPool(dev, layout)),
	m_descriptor_set(create(dev, layout)),
	m_buffer(createBuffer(dev, queue))
{
	size_t mapped_count = 0;
	for (auto &b : layout.getDescription())
		if (b.isMapped())
			mapped_count++;

	std::vector<VkWriteDescriptorSet> writes;
	writes.reserve(mapped_count);
	std::vector<VkDescriptorBufferInfo> bufferInfos;
	bufferInfos.reserve(mapped_count);

	size_t size = 0;
	for (auto &b : layout.getDescription()) {
		if (!b.isMapped())
			continue;

		VkWriteDescriptorSet w {};

		w.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		w.dstSet = m_descriptor_set;
		w.dstBinding = b.binding;
		w.dstArrayElement = 0;
		w.descriptorCount = 1;
		w.descriptorType = static_cast<VkDescriptorType>(util::enum_underlying(b.descriptorType));

		size = util::align_dyn(size, dev.physical().properties().getAlignment(b.descriptorType));

		VkDescriptorBufferInfo buf_info;
		buf_info.buffer = m_buffer;
		buf_info.offset = size;
		buf_info.range = b.descriptorCount;
		w.pBufferInfo = &bufferInfos.emplace_back(buf_info);

		writes.emplace_back(w);
		size += b.descriptorCount;
	}

	if (writes.size() > 0)
		vkUpdateDescriptorSets(dev, writes.size(), writes.data(), 0, nullptr);
}


sb::Buffer::Region Vk::DescriptorSet::uniformBufferRegion(void)
{
	return sb::Buffer::Region(m_buffer, m_layout.getUniformOff(), m_layout.getUniformSize());
}

sb::Buffer::Region Vk::DescriptorSet::storageBufferRegion(void)
{
	return sb::Buffer::Region(m_buffer, m_layout.getStorageOff(), m_layout.getStorageSize());
}

void Vk::DescriptorSet::bindSampler(size_t binding, size_t index, sb::Sampler &sampler)
{
	VkDescriptorImageInfo ii {};
	ii.sampler = reinterpret_cast<Sampler&>(sampler);

	VkWriteDescriptorSet w {};
	w.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	w.dstSet = m_descriptor_set;
	w.dstBinding = binding;
	w.dstArrayElement = index;
	w.descriptorCount = 1;
	w.descriptorType = static_cast<VkDescriptorType>(util::enum_underlying(m_layout.getDescription().at(binding).descriptorType));
	w.pImageInfo = &ii;

	vkUpdateDescriptorSets(m_descriptor_pool.getDep(), 1, &w, 0, nullptr);
}

void Vk::DescriptorSet::bindImage(size_t binding, size_t index, sb::Image &image, sb::Image::Layout layout)
{
	VkDescriptorImageInfo ii {};
	ii.imageView = reinterpret_cast<ImageView&>(image);
	ii.imageLayout = static_cast<VkImageLayout>(util::enum_underlying(layout));

	VkWriteDescriptorSet w {};
	w.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	w.dstSet = m_descriptor_set;
	w.dstBinding = binding;
	w.dstArrayElement = index;
	w.descriptorCount = 1;
	w.descriptorType = static_cast<VkDescriptorType>(util::enum_underlying(m_layout.getDescription().at(binding).descriptorType));
	w.pImageInfo = &ii;

	vkUpdateDescriptorSets(m_descriptor_pool.getDep(), 1, &w, 0, nullptr);
}

void Vk::DescriptorSet::bindCombinedImageSampler(size_t binding, size_t index, sb::Sampler &sampler, sb::Image &image, sb::Image::Layout layout)
{
	VkDescriptorImageInfo ii {};
	ii.sampler = reinterpret_cast<Sampler&>(sampler);
	ii.imageView = reinterpret_cast<ImageView&>(image);
	ii.imageLayout = static_cast<VkImageLayout>(util::enum_underlying(layout));

	VkWriteDescriptorSet w {};
	w.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	w.dstSet = m_descriptor_set;
	w.dstBinding = binding;
	w.dstArrayElement = index;
	w.descriptorCount = 1;
	w.descriptorType = static_cast<VkDescriptorType>(util::enum_underlying(m_layout.getDescription().at(binding).descriptorType));
	w.pImageInfo = &ii;

	vkUpdateDescriptorSets(m_descriptor_pool.getDep(), 1, &w, 0, nullptr);
}

Vk::DescriptorSet::operator VkDescriptorSet(void) const
{
	return m_descriptor_set;
}

VkDescriptorPool Vk::DescriptorSet::createPool(Device &dev, const DescriptorSetLayout &layout)
{
	std::map<VkDescriptorType, size_t> typeCount;
	for (auto &b : layout.getDescription())
		typeCount[descriptorType(b.descriptorType)] += b.isMapped() ? 1 : b.descriptorCount;
	std::vector<VkDescriptorPoolSize> sizes;
	for (auto &t : typeCount) {
		VkDescriptorPoolSize s;
		s.type = t.first;
		s.descriptorCount = t.second;
		sizes.emplace_back(s);
	}

	VkDescriptorPoolCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	ci.maxSets = 1;
	ci.poolSizeCount = sizes.size();
	ci.pPoolSizes = sizes.data();

	if (ci.poolSizeCount == 0)
		return VK_NULL_HANDLE;
	else
		return dev.createVk(vkCreateDescriptorPool, ci);
}

VkDescriptorSet Vk::DescriptorSet::create(Device &dev, const DescriptorSetLayout &layout)
{
	VkDescriptorSetAllocateInfo ai {};
	ai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	ai.descriptorPool = m_descriptor_pool;
	ai.descriptorSetCount = 1;
	ai.pSetLayouts = &static_cast<const VkDescriptorSetLayout&>(layout);

	if (ai.descriptorPool == VK_NULL_HANDLE)
		return VK_NULL_HANDLE;
	else
		return dev.allocateVk(vkAllocateDescriptorSets, ai);
}

Vk::VmaBuffer Vk::DescriptorSet::createBuffer(Device &dev, sb::Queue *queue)
{
	if (m_layout.getBufferSize() == 0 || queue == nullptr)
		return VmaBuffer(dev, VK_NULL_HANDLE, VK_NULL_HANDLE);

	VkQueueFamilyIndex queueIndex = reinterpret_cast<Queue*>(queue)->getFamilyIndex();

	VkBufferCreateInfo bci {};
	bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bci.size = m_layout.getBufferSize();
	bci.usage = 0;
	if (m_layout.getUniformSize() > 0)
		bci.usage |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	if (m_layout.getStorageSize() > 0)
		bci.usage |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	bci.queueFamilyIndexCount = 1;
	bci.pQueueFamilyIndices = &queueIndex;

	VmaAllocationCreateInfo aci {};
	aci.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

	return dev.allocator().createBuffer(bci, aci);
}

template <>
void Vk::Device::Handle<VkDescriptorPool>::destroy(Vk::Device &device, VkDescriptorPool pool)
{
	device.destroy(vkDestroyDescriptorPool, pool);
}

VkAttachmentLoadOp Vk::RenderPass::sbLoadOpToVk(sb::Image::LoadOp loadOp)
{
	static const std::map<sb::Image::LoadOp, VkAttachmentLoadOp> table {
		{sb::Image::LoadOp::DontCare, VK_ATTACHMENT_LOAD_OP_DONT_CARE},
		{sb::Image::LoadOp::Load, VK_ATTACHMENT_LOAD_OP_LOAD},
		{sb::Image::LoadOp::Clear, VK_ATTACHMENT_LOAD_OP_CLEAR}
	};

	return table.at(loadOp);
}

VkAttachmentStoreOp Vk::RenderPass::sbStoreOpToVk(sb::Image::StoreOp storeOp)
{
	static const std::map<sb::Image::StoreOp, VkAttachmentStoreOp> table {
		{sb::Image::StoreOp::DontCare, VK_ATTACHMENT_STORE_OP_DONT_CARE},
		{sb::Image::StoreOp::Store, VK_ATTACHMENT_STORE_OP_STORE},
	};

	return table.at(storeOp);
}

Vk::RenderPass::RenderPass(Vk::Device &dev, sb::rs::RenderPass &res) :
	m_layout(res.layout()),
	m_handle(dev, create(dev)),
	m_subpasses_descriptor_set_layouts(createSubpassesDescriptorSetLayouts()),
	m_subpasses_pipeline_layouts(createSubpassesPipelineLayouts())
{
}

VkRenderPass Vk::RenderPass::create(Vk::Device &dev)
{
	auto &layout = m_layout;

	std::vector<VkAttachmentDescription> attachments;
	attachments.reserve(layout.attachments.size());
	for (auto &a : layout.attachments) {
		VkAttachmentDescription att {};
		att.format = dev.sbFormatToVk(a.format);
		att.samples = VK_SAMPLE_COUNT_1_BIT;
		att.loadOp = sbLoadOpToVk(a.loadOp);
		att.storeOp = sbStoreOpToVk(a.storeOp);
		att.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		att.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		att.initialLayout = sbImageLayoutToVk(a.inLayout);
		att.finalLayout = sbImageLayoutToVk(a.outLayout);
		attachments.emplace_back(att);
	}

	std::vector<VkSubpassDescription> subpasses;
	std::vector<VkAttachmentReference> subpasses_inputs;
	size_t subpasses_inputs_off = 0;
	std::vector<VkAttachmentReference> subpasses_color_atts;
	size_t subpasses_color_atts_off = 0;
	std::vector<VkAttachmentReference> subpasses_resolves;
	std::vector<VkAttachmentReference> subpasses_depth_stencils;
	size_t subpasses_depth_stencils_off = 0;
	std::vector<uint32_t> subpasses_preserve_atts;
	size_t subpasses_preserve_atts_off = 0;
	for (auto &s : layout.subpasses) {
		subpasses_inputs_off += s.inputAttachments.size();
		subpasses_color_atts_off += s.colorAttachments.size();
		if (s.depthStencilAttachment)
			subpasses_depth_stencils_off++;
		subpasses_preserve_atts_off += s.preserveAttachments.size();
	}
	subpasses_inputs.reserve(subpasses_inputs_off);
	subpasses_color_atts.reserve(subpasses_color_atts_off);
	subpasses_resolves.reserve(subpasses_color_atts_off);
	subpasses_depth_stencils.reserve(subpasses_depth_stencils_off);
	subpasses_preserve_atts.reserve(subpasses_preserve_atts_off);
	subpasses_inputs_off = 0;
	subpasses_color_atts_off = 0;
	subpasses_depth_stencils_off = 0;
	subpasses_preserve_atts_off = 0;

	subpasses.reserve(layout.subpasses.size());
	for (auto &s : layout.subpasses) {
		for (auto &in : s.inputAttachments)
			subpasses_inputs.emplace_back(sbAttachmentReferenceToVk(in));
		for (auto &color_att : s.colorAttachments) {
			subpasses_color_atts.emplace_back(sbAttachmentReferenceToVk(color_att));
			if (color_att.resolve)
				subpasses_resolves.emplace_back(sbAttachmentReferenceToVk(*color_att.resolve));
			else
				subpasses_resolves.emplace_back(VkAttachmentReference{VK_ATTACHMENT_UNUSED, VK_IMAGE_LAYOUT_UNDEFINED});
		}
		if (s.depthStencilAttachment)
			subpasses_depth_stencils.emplace_back(sbAttachmentReferenceToVk(*s.depthStencilAttachment));
		for (auto &pre : s.preserveAttachments)
			subpasses_preserve_atts.emplace_back(pre);

		VkSubpassDescription sub {};
		sub.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		sub.inputAttachmentCount = s.inputAttachments.size();
		sub.pInputAttachments = &subpasses_inputs[subpasses_inputs_off];
		sub.colorAttachmentCount = s.colorAttachments.size();
		sub.pColorAttachments = &subpasses_color_atts[subpasses_color_atts_off];
		sub.pResolveAttachments = &subpasses_resolves[subpasses_color_atts_off];
		sub.pDepthStencilAttachment = s.depthStencilAttachment ? &subpasses_depth_stencils[subpasses_depth_stencils_off] : nullptr;
		sub.preserveAttachmentCount = s.preserveAttachments.size();
		sub.pPreserveAttachments = &subpasses_preserve_atts[subpasses_preserve_atts_off];

		subpasses_inputs_off += s.inputAttachments.size();
		subpasses_color_atts_off += s.colorAttachments.size();
		if (s.depthStencilAttachment)
			subpasses_depth_stencils_off++;
		subpasses_preserve_atts_off += s.preserveAttachments.size();
		subpasses.emplace_back(sub);
	}

	std::vector<VkSubpassDependency> dependencies;
	dependencies.reserve(layout.dependencies.size());
	for (auto &d : layout.dependencies) {
		VkSubpassDependency dep {};
		dep.srcSubpass = d.srcSubpass;
		dep.dstSubpass = d.dstSubpass;
		dep.srcStageMask = sbPipelineStageToVk(d.srcStageMask);
		dep.dstStageMask = sbPipelineStageToVk(d.dstStageMask);
		dep.srcAccessMask = sbAccessToVk(d.srcAccessMask);
		dep.dstAccessMask = sbAccessToVk(d.dstAccessMask);
		dep.dependencyFlags = sbDependencyFlagToVk(d.flags);
		dependencies.emplace_back(dep);
	}

	VkRenderPassCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	ci.attachmentCount = attachments.size();
	ci.pAttachments = attachments.data();
	ci.subpassCount = subpasses.size();
	ci.pSubpasses = subpasses.data();
	ci.dependencyCount = dependencies.size();
	ci.pDependencies = dependencies.data();

	return dev.createVk(vkCreateRenderPass, ci);
}

std::vector<Vk::DescriptorSetLayout> Vk::RenderPass::createSubpassesDescriptorSetLayouts(void)
{
	std::vector<DescriptorSetLayout> res;

	for (auto &sub : m_layout.subpasses) {
		sb::Shader::DescriptorSet::Layout::Description desc;
		size_t n = 0;
		for (auto &in : sub.inputAttachments) {
			auto ndx = n++;
			static_cast<void>(in);

			sb::Shader::DescriptorSet::Layout::DescriptionBinding binding {};
			binding.binding = ndx;
			binding.descriptorCount = 1;
			binding.descriptorType = sb::Shader::DescriptorType::InputAttachment;
			binding.stages = {sb::Shader::Stage::Fragment};
			desc.emplace_back(binding);
		}
		res.emplace_back(m_handle.getDep(), desc);
	}
	return res;
}

std::vector<Vk::PipelineLayout> Vk::RenderPass::createSubpassesPipelineLayouts(void)
{
	std::vector<Vk::PipelineLayout> res;

	for (auto &desc : m_subpasses_descriptor_set_layouts) {
		VkDescriptorSetLayout layout = desc;
		if (layout == VK_NULL_HANDLE) {
			res.emplace_back(m_handle.getDep(), static_cast<VkPipelineLayout>(VK_NULL_HANDLE));
			continue;
		}

		VkPipelineLayoutCreateInfo ci {};
		ci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		ci.setLayoutCount = 1;
		ci.pSetLayouts = &layout;

		res.emplace_back(m_handle.getDep().create<PipelineLayout>(vkCreatePipelineLayout, ci));
	}

	return res;
}

Vk::RenderPass::~RenderPass(void)
{
}

std::unique_ptr<sb::Framebuffer> Vk::RenderPass::createFramebuffer(const svec2 &extent, size_t layers, size_t count, sb::Image **images)
{
	VkImageView atts_vla[count];
	for (size_t i = 0; i < count; i++)
		atts_vla[i] = *reinterpret_cast<ImageView*>(images[i]);

	VkFramebufferCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	ci.renderPass = *this;
	ci.attachmentCount = count;
	ci.pAttachments = atts_vla;
	ci.width = extent.x;
	ci.height = extent.y;
	ci.layers = layers;

	size_t n = 0;
	std::vector<DescriptorSet> input_attachments;
	for (auto &l : m_subpasses_descriptor_set_layouts) {
		auto ndx = n++;

		auto &set = input_attachments.emplace_back(m_handle.getDep(), l, nullptr);	// input attachments don't have buffer associated
		auto &subpass = m_layout.subpasses.at(ndx);
		VkWriteDescriptorSet writes_vla[subpass.inputAttachments.size()];
		VkDescriptorImageInfo image_info_vla[subpass.inputAttachments.size()];
		size_t wndx = 0;
		for (auto &in : subpass.inputAttachments) {
			VkDescriptorImageInfo image_info {};
			image_info.sampler = VK_NULL_HANDLE;
			image_info.imageView = atts_vla[in.ndx];
			image_info.imageLayout = static_cast<VkImageLayout>(util::enum_underlying(in.layout));
			image_info_vla[wndx] = image_info;

			VkWriteDescriptorSet write {};
			write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			write.dstSet = set;
			write.dstBinding = wndx;
			write.dstArrayElement = 0;
			write.descriptorCount = 1;
			write.descriptorType = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			write.pImageInfo = &image_info_vla[wndx];

			writes_vla[wndx++] = write;
		}
		vkUpdateDescriptorSets(m_handle.getDep(), subpass.inputAttachments.size(), writes_vla, 0, nullptr);
	}

	return std::make_unique<Framebuffer>(m_handle.getDep(), m_handle.getDep().createVk(vkCreateFramebuffer, ci), *this, std::move(input_attachments));
}

Vk::Swapchain::Swapchain(Vk::Device &device, VkSwapchainKHR swapchain, VkSurfaceFormatKHR surfaceFormat, const svec2 &extent) :
	Device::Handle<VkSwapchainKHR>(device, swapchain),
	m_surface_format(surfaceFormat),
	m_extent(extent),
	m_images(queryImages())
{
}

std::vector<sb::Swapchain::Image2D> Vk::Swapchain::queryImages(void)
{
	std::vector<sb::Swapchain::Image2D> res;

	for (auto &img : enumerate<VkImage>(vkGetSwapchainImagesKHR, getDep(), *this))
		res.emplace_back(*this, std::make_unique<ImageView>(getDep(), img, m_surface_format.format, sb::Image::Type::Image2D, svec3(m_extent.x, m_extent.y, 1), ComponentSwizzle::Identity, sb::Image::Aspect::Color, Range(0, 1), Range(0, 1)));

	return res;
}

Vk::Swapchain::~Swapchain(void)
{
}

template <>
void Vk::Device::Handle<VkSwapchainKHR>::destroy(Vk::Device &device, VkSwapchainKHR swapchain)
{
	device.destroy(vkDestroySwapchainKHR, swapchain);
}

std::vector<sb::Swapchain::Image2D>& Vk::Swapchain::getImages(void)
{
	return m_images;
}

size_t Vk::Swapchain::acquireNextImage(sb::Semaphore &semaphore)
{
	auto &vk_sem = reinterpret_cast<Semaphore&>(semaphore);
	uint32_t res;

	Vk::assert(vkAcquireNextImageKHR(getDep(), *this, ~0ULL, vk_sem, VK_NULL_HANDLE, &res));
	return res;
}

svec2 Vk::Swapchain::getExtent(void) const
{
	return m_extent;
}

template <>
void Vk::Device::Handle<VkRenderPass>::destroy(Vk::Device &device, VkRenderPass renderPass)
{
	device.destroy(vkDestroyRenderPass, renderPass);
}

Vk::Semaphore::Semaphore(Device &dev, VkSemaphore semaphore) :
	Device::Handle<VkSemaphore>(dev, semaphore)
{
}

Vk::Semaphore::~Semaphore(void)
{
}

template <>
void Vk::Device::Handle<VkSemaphore>::destroy(Vk::Device &device, VkSemaphore semaphore)
{
	device.destroy(vkDestroySemaphore, semaphore);
}

Vk::Fence::Fence(Device &dev, VkFence fence) :
	Device::Handle<VkFence>(dev, fence)
{
}

Vk::Fence::~Fence(void)
{
}

template <>
void Vk::Device::Handle<VkFence>::destroy(Vk::Device &device, VkFence fence)
{
	device.destroy(vkDestroyFence, fence);
}

void Vk::Fence::wait(void)
{
	VkFence fence = *this;

	Vk::assert(vkWaitForFences(getDep(), 1, &fence, VK_TRUE, ~0ULL));
}

void Vk::Fence::reset(void)
{
	VkFence fence = *this;

	Vk::assert(vkResetFences(getDep(), 1, &fence));
}

template <>
void Vk::Device::Handle<VkPipelineLayout>::destroy(Vk::Device &device, VkPipelineLayout pipelineLayout)
{
	device.destroy(vkDestroyPipelineLayout, pipelineLayout);
}

template <>
void Vk::Device::Handle<VkShaderModule>::destroy(Vk::Device &device, VkShaderModule shaderModule)
{
	device.destroy(vkDestroyShaderModule, shaderModule);
}

template <>
void Vk::Device::Handle<VkPipeline>::destroy(Vk::Device &device, VkPipeline pipeline)
{
	device.destroy(vkDestroyPipeline, pipeline);
}

VkShaderStageFlagBits Vk::Shader::sbStageToVk(Subtile::Shader::Stage stage)
{
	static const std::map<Subtile::Shader::Stage, VkShaderStageFlagBits> table {
		{Subtile::Shader::Stage::TesselationControl, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT},
		{Subtile::Shader::Stage::TesselationEvaluation, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT},
		{Subtile::Shader::Stage::Geometry, VK_SHADER_STAGE_GEOMETRY_BIT},
		{Subtile::Shader::Stage::Vertex, VK_SHADER_STAGE_VERTEX_BIT},
		{Subtile::Shader::Stage::Fragment, VK_SHADER_STAGE_FRAGMENT_BIT},
		{Subtile::Shader::Stage::All, VK_SHADER_STAGE_ALL}
	};

	return table.at(stage);
}

VkFormat Vk::Shader::vertexInputFormatToVk(sb::Shader::VertexInput::Format format)
{
	static const std::map<sb::Shader::VertexInput::Format, VkFormat> table {
		{sb::Shader::VertexInput::Format::Bool, VK_FORMAT_R32_UINT},
		{sb::Shader::VertexInput::Format::Int, VK_FORMAT_R32_SINT},
		{sb::Shader::VertexInput::Format::Uint, VK_FORMAT_R32_UINT},
		{sb::Shader::VertexInput::Format::Float, VK_FORMAT_R32_SFLOAT},
		{sb::Shader::VertexInput::Format::Double, VK_FORMAT_R64_SFLOAT},

		{sb::Shader::VertexInput::Format::Vec2, VK_FORMAT_R32G32_SFLOAT},
		{sb::Shader::VertexInput::Format::Vec3, VK_FORMAT_R32G32B32_SFLOAT},
		{sb::Shader::VertexInput::Format::Vec4, VK_FORMAT_R32G32B32A32_SFLOAT},

		{sb::Shader::VertexInput::Format::Bvec2, VK_FORMAT_R32G32_UINT},
		{sb::Shader::VertexInput::Format::Bvec3, VK_FORMAT_R32G32B32_UINT},
		{sb::Shader::VertexInput::Format::Bvec4, VK_FORMAT_R32G32B32A32_UINT},

		{sb::Shader::VertexInput::Format::Ivec2, VK_FORMAT_R32G32_SINT},
		{sb::Shader::VertexInput::Format::Ivec3, VK_FORMAT_R32G32B32_SINT},
		{sb::Shader::VertexInput::Format::Ivec4, VK_FORMAT_R32G32B32A32_SINT},

		{sb::Shader::VertexInput::Format::Uvec2, VK_FORMAT_R32G32_UINT},
		{sb::Shader::VertexInput::Format::Uvec3, VK_FORMAT_R32G32B32_UINT},
		{sb::Shader::VertexInput::Format::Uvec4, VK_FORMAT_R32G32B32A32_UINT},

		{sb::Shader::VertexInput::Format::Dvec2, VK_FORMAT_R64G64_SFLOAT},
		{sb::Shader::VertexInput::Format::Dvec3, VK_FORMAT_R64G64B64_SFLOAT},
		{sb::Shader::VertexInput::Format::Dvec4, VK_FORMAT_R64G64B64A64_SFLOAT}
	};

	return table.at(format);
}

Vk::Shader::Shader(Vk::Device &device, rs::Shader &shader) :
	m_device(device),
	m_render_pass(loadRenderPass(shader)),
	m_descriptor_set_offset(m_render_pass ?
		(reinterpret_cast<RenderPass&>(**m_render_pass->first).getSubpassesDescriptorSetLayouts().at(m_render_pass->second).getHandle() != VK_NULL_HANDLE ? 1 : 0)
	: 0),
	m_layouts(shader.loadDescriptorSetLayouts(device)),
	m_pipeline_layout(shader.isModule() ? PipelineLayout(device, VK_NULL_HANDLE) : createPipelineLayout()),
	m_shader_modules(shader.isModule() ? ShaderModulesType{} : createShaderModules(device, shader)),
	m_pipeline(shader.isModule() ? Pipeline(device, VK_NULL_HANDLE) : createPipeline(device, shader))
{
	static_cast<void>(shader);
}

Vk::PipelineLayout Vk::Shader::createPipelineLayout(void)
{
	std::vector<VkDescriptorSetLayout> layouts;

	if (m_descriptor_set_offset > 0)
		layouts.emplace_back(reinterpret_cast<RenderPass&>(**m_render_pass->first).getSubpassesDescriptorSetLayouts().at(m_render_pass->second));
	for (auto &l : m_layouts)
		layouts.emplace_back(reinterpret_cast<const DescriptorSetLayout&>(l.get()->resolve()));

	VkPipelineLayoutCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	ci.setLayoutCount = layouts.size();
	ci.pSetLayouts = layouts.data();
	return m_device.create<PipelineLayout>(vkCreatePipelineLayout, ci);
}

std::vector<std::pair<VkShaderStageFlagBits, Vk::ShaderModule>> Vk::Shader::createShaderModules(Vk::Device &device, rs::Shader &shader)
{
	std::vector<std::pair<VkShaderStageFlagBits, Vk::ShaderModule>> res;

	for (auto &sp : shader.getStages()) {
		std::stringstream ss;
		ss << sp.second.getVk().getCompiled().read().rdbuf();
		auto bin = ss.str();

		VkShaderModuleCreateInfo ci {};
		ci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		ci.codeSize = bin.size();
		ci.pCode = reinterpret_cast<uint32_t*>(bin.data());

		res.emplace_back(sbStageToVk(sp.first), device.create<ShaderModule>(vkCreateShaderModule, ci));
	}
	return res;
}

std::optional<std::pair<sb::RenderPass::Cache::Ref, size_t>> Vk::Shader::loadRenderPass(rs::Shader &shader)
{
	if (shader.isModule())
		return std::nullopt;

	auto rp = shader.getRenderPass();
	return std::pair<sb::RenderPass::Cache::Ref, size_t>(m_device.loadRenderPassRef(rp.first), rp.second);
}

std::optional<Vk::Pipeline> Vk::Shader::createPipeline(Vk::Device &device, rs::Shader &shader)
{
	if (shader.isModule())
		return std::nullopt;

	auto props = shader.getProps();

	std::vector<VkPipelineShaderStageCreateInfo> stages;
	for (auto &sp : m_shader_modules) {
		VkPipelineShaderStageCreateInfo ci {};
		ci.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ci.stage = sp.first;
		ci.module = sp.second;
		ci.pName = "main";
		stages.emplace_back(ci);
	}

	auto rsVertexInput = shader.vertexInput();
	std::vector<VkVertexInputBindingDescription> vertexBindings;
	VkVertexInputBindingDescription vertexBinding;
	vertexBinding.binding = 0;
	vertexBinding.stride = rsVertexInput.size;
	vertexBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	vertexBindings.emplace_back(vertexBinding);
	std::vector<VkVertexInputAttributeDescription> vertexAttributes;
	for (auto &a : rsVertexInput.attributes) {
		VkVertexInputAttributeDescription attr;
		attr.location = a.location;
		attr.binding = 0;
		attr.format = vertexInputFormatToVk(a.format);
		attr.offset = a.offset;
		vertexAttributes.emplace_back(attr);
	}
	VkPipelineVertexInputStateCreateInfo vertexInput {};
	vertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	vertexInput.vertexBindingDescriptionCount = vertexBindings.size();
	vertexInput.pVertexBindingDescriptions = vertexBindings.data();
	vertexInput.vertexAttributeDescriptionCount = vertexAttributes.size();
	vertexInput.pVertexAttributeDescriptions = vertexAttributes.data();

	VkPipelineInputAssemblyStateCreateInfo inputAssembly {};
	inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	std::array<VkViewport, 1> viewports {{
		{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
	}};
	std::array<VkRect2D, 1> scissors {{
		{{0, 0}, {0, 0}}
	}};
	VkPipelineViewportStateCreateInfo viewport {};
	viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewport.viewportCount = viewports.size();
	viewport.pViewports = viewports.data();
	viewport.scissorCount = scissors.size();
	viewport.pScissors = scissors.data();

	VkPipelineRasterizationStateCreateInfo rasterization {};
	rasterization.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterization.polygonMode = VK_POLYGON_MODE_FILL;
	rasterization.cullMode = util::enum_underlying(props.rasterizationCullMode);
	rasterization.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterization.lineWidth = 1.0f;

	VkPipelineMultisampleStateCreateInfo multisample {};
	multisample.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	auto &rp_layout = reinterpret_cast<RenderPass&>(**m_render_pass->first).getLayout();
	auto &sp = rp_layout.subpasses.at(m_render_pass->second);

	VkPipelineDepthStencilStateCreateInfo depthStencil {};
	depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencil.depthTestEnable = VK_TRUE;
	depthStencil.depthWriteEnable = VK_TRUE;
	depthStencil.depthCompareOp = static_cast<VkCompareOp>(util::enum_underlying(props.depthStencilDepthCompareOp));
	depthStencil.minDepthBounds = 0.0f;
	depthStencil.maxDepthBounds = 1.0f;

	std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
	for (size_t i = 0; i < sp.colorAttachments.size(); i++) {
		VkPipelineColorBlendAttachmentState colorBlendAttachment {};
		colorBlendAttachment.blendEnable = VK_TRUE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
		colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachments.emplace_back(colorBlendAttachment);
	}

	VkPipelineColorBlendStateCreateInfo colorBlend {};
	colorBlend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlend.attachmentCount = colorBlendAttachments.size();
	colorBlend.pAttachments = colorBlendAttachments.data();
	for (size_t i = 0; i < 4; i++)
		colorBlend.blendConstants[i] = 1.0f;

	auto dynamicStates = std::array{VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
	VkPipelineDynamicStateCreateInfo dynamicState {};
	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.dynamicStateCount = dynamicStates.size();
	dynamicState.pDynamicStates = dynamicStates.data();

	VkGraphicsPipelineCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	ci.stageCount = stages.size();
	ci.pStages = stages.data();
	ci.pVertexInputState = &vertexInput;
	ci.pInputAssemblyState = &inputAssembly;
	ci.pViewportState = &viewport;
	ci.pRasterizationState = &rasterization;
	ci.pMultisampleState = &multisample;
	ci.pDepthStencilState = &depthStencil;
	ci.pColorBlendState = &colorBlend;
	ci.pDynamicState = &dynamicState;
	ci.layout = m_pipeline_layout;
	ci.renderPass = reinterpret_cast<RenderPass&>(**m_render_pass->first);
	ci.subpass = m_render_pass->second;

	return device.create<Pipeline>(vkCreateGraphicsPipelines, ci);
}

const sb::Shader::DescriptorSet::Layout& Vk::Shader::setLayout(size_t ndx)
{
	return m_layouts.at(ndx).get()->resolve();
}

std::unique_ptr<sb::Shader::DescriptorSet> Vk::Shader::set(size_t ndx, sb::Queue &queue)
{
	return std::make_unique<Vk::DescriptorSet>(m_device, reinterpret_cast<const DescriptorSetLayout&>(m_layouts.at(ndx)->resolve()), &queue);
}

Vk::PipelineLayout& Vk::Shader::getPipelineLayout(void)
{
	return m_pipeline_layout;
}

Vk::Pipeline& Vk::Shader::getPipeline(void)
{
	return *m_pipeline;
}

Vk::CommandBuffer::CommandBuffer(CommandPool &pool, sb::CommandBuffer::Level level) :
	m_pool(pool),
	m_handle(createCommandBuffer(level))
{
}

VkCommandBuffer Vk::CommandBuffer::createCommandBuffer(sb::CommandBuffer::Level level)
{
	static const std::map<sb::CommandBuffer::Level, VkCommandBufferLevel> table {
		{sb::CommandBuffer::Level::Primary, VK_COMMAND_BUFFER_LEVEL_PRIMARY},
		{sb::CommandBuffer::Level::Secondary, VK_COMMAND_BUFFER_LEVEL_SECONDARY}
	};

	VkCommandBufferAllocateInfo ai {};
	ai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	ai.commandPool = m_pool;
	ai.level = table.at(level);
	ai.commandBufferCount = 1;

	return m_pool.getDep().allocateVk(vkAllocateCommandBuffers, ai);
}

Vk::CommandBuffer::~CommandBuffer(void)
{
	vkFreeCommandBuffers(m_pool.getDep(), m_pool, 1, &m_handle);
}

void Vk::CommandBuffer::reset(bool releaseResources)
{
	Vk::assert(vkResetCommandBuffer(*this, releaseResources ? VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT : 0));
}

void Vk::CommandBuffer::begin(Usage flags)
{
	VkCommandBufferInheritanceInfo ii {};
	ii.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;

	VkCommandBufferBeginInfo bi {};
	bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	bi.flags = static_cast<std::underlying_type_t<Usage>>(flags);
	bi.pInheritanceInfo = &ii;

	Vk::assert(vkBeginCommandBuffer(*this, &bi));
}

void Vk::CommandBuffer::beginRender(Usage flags, sb::Framebuffer &fb, size_t subpass)
{
	auto &vk_fb = reinterpret_cast<Framebuffer&>(fb);

	VkCommandBufferInheritanceInfo ii {};
	ii.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	ii.renderPass = vk_fb.getRenderPass();
	ii.subpass = subpass;
	ii.framebuffer = vk_fb;

	VkCommandBufferBeginInfo bi {};
	bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	bi.flags = static_cast<std::underlying_type_t<Usage>>(flags) | VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
	bi.pInheritanceInfo = &ii;

	Vk::assert(vkBeginCommandBuffer(*this, &bi));
}

void Vk::CommandBuffer::beginRender(Usage flags, sb::RenderPass &rp, size_t subpass)
{
	auto &vk_rp = reinterpret_cast<RenderPass&>(rp);

	VkCommandBufferInheritanceInfo ii {};
	ii.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	ii.renderPass = vk_rp;
	ii.subpass = subpass;
	ii.framebuffer = VK_NULL_HANDLE;

	VkCommandBufferBeginInfo bi {};
	bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	bi.flags = static_cast<std::underlying_type_t<Usage>>(flags) | VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
	bi.pInheritanceInfo = &ii;

	Vk::assert(vkBeginCommandBuffer(*this, &bi));
}

void Vk::CommandBuffer::end(void)
{
	Vk::assert(vkEndCommandBuffer(*this));
}

void Vk::CommandBuffer::executeCommands(size_t count, sb::CommandBuffer **cmds)
{
	VkCommandBuffer cmds_vla[count];

	for (size_t i = 0; i < count; i++)
		cmds_vla[i] = *reinterpret_cast<CommandBuffer*>(cmds[i]);

	vkCmdExecuteCommands(*this, count, cmds_vla);
}

void Vk::CommandBuffer::bindPipeline(sb::Shader &shader)
{
	vkCmdBindPipeline(*this, VK_PIPELINE_BIND_POINT_GRAPHICS, reinterpret_cast<Shader&>(shader).getPipeline());
}

void Vk::CommandBuffer::bindDescriptorSets(sb::Shader &shader, size_t first_set, size_t count, sb::Shader::DescriptorSet **sets)
{
	VkDescriptorSet sets_vla[count];

	for (size_t i = 0; i < count; i++)
		sets_vla[i] = *reinterpret_cast<DescriptorSet*>(sets[i]);

	auto &sh = reinterpret_cast<Shader&>(shader);
	vkCmdBindDescriptorSets(*this, VK_PIPELINE_BIND_POINT_GRAPHICS, sh.getPipelineLayout(), reinterpret_cast<Shader&>(shader).getDescriptorSetOffset() + first_set, count, sets_vla, 0, nullptr);
}

void Vk::CommandBuffer::beginRenderPass(bool isInline, sb::Framebuffer &fb, const srect2 &renderArea, size_t clearValueCount, ClearValue *clearValues)
{
	auto &vk_fb = reinterpret_cast<Framebuffer&>(fb);

	VkRenderPassBeginInfo bi {};
	bi.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	bi.renderPass = vk_fb.getRenderPass();
	bi.framebuffer = vk_fb;
	bi.renderArea.offset = VkOffset2D{static_cast<int32_t>(renderArea.offset.x), static_cast<int32_t>(renderArea.offset.y)};
	bi.renderArea.extent = VkExtent2D{static_cast<uint32_t>(renderArea.extent.x), static_cast<uint32_t>(renderArea.extent.y)};
	bi.clearValueCount = clearValueCount;
	bi.pClearValues = reinterpret_cast<VkClearValue*>(clearValues);
	vkCmdBeginRenderPass(*this, &bi, isInline ? VK_SUBPASS_CONTENTS_INLINE : VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);
	m_render_pass_subpass_ndx = 0;
	m_render_pass_fb = &vk_fb;
	VkDescriptorSet desc_set = m_render_pass_fb->getInputAttachments().at(m_render_pass_subpass_ndx);
	if (desc_set != VK_NULL_HANDLE)
		vkCmdBindDescriptorSets(*this, VK_PIPELINE_BIND_POINT_GRAPHICS, m_render_pass_fb->getRenderPass().getSubpassesPipelineLayouts().at(m_render_pass_subpass_ndx), 0, 1, &desc_set, 0, nullptr);
	m_render_pass_subpass_ndx++;
}

void Vk::CommandBuffer::nextSubpass(bool isInline)
{
	vkCmdNextSubpass(*this, isInline ? VK_SUBPASS_CONTENTS_INLINE : VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);
	VkDescriptorSet desc_set = m_render_pass_fb->getInputAttachments().at(m_render_pass_subpass_ndx);
	if (desc_set != VK_NULL_HANDLE)
		vkCmdBindDescriptorSets(*this, VK_PIPELINE_BIND_POINT_GRAPHICS, m_render_pass_fb->getRenderPass().getSubpassesPipelineLayouts().at(m_render_pass_subpass_ndx), 0, 1, &desc_set, 0, nullptr);
	m_render_pass_subpass_ndx++;
}

void Vk::CommandBuffer::endRenderPass(void)
{
	vkCmdEndRenderPass(*this);
}

void Vk::CommandBuffer::copy(const sb::Buffer::Region &src, const sb::Buffer::Region &dst)
{
	VkBufferCopy bc;
	bc.srcOffset = src.offset;
	bc.dstOffset = dst.offset;
	bc.size = src.size;

	vkCmdCopyBuffer(*this, reinterpret_cast<VmaBuffer&>(src.buffer), reinterpret_cast<VmaBuffer&>(dst.buffer), 1, &bc);
}

void Vk::CommandBuffer::memoryBarrier(PipelineStage srcStageMask, PipelineStage dstStageMask, DependencyFlag flags, Access srcAccessMask, Access dstAccessMask)
{
	VkMemoryBarrier barrier {};
	barrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
	barrier.srcAccessMask = util::enum_underlying(srcAccessMask);
	barrier.dstAccessMask = util::enum_underlying(dstAccessMask);
	vkCmdPipelineBarrier(*this, util::enum_underlying(srcStageMask), util::enum_underlying(dstStageMask), util::enum_underlying(flags), 1, &barrier, 0, nullptr, 0, nullptr);
}

void Vk::CommandBuffer::imageMemoryBarrier(PipelineStage srcStageMask, PipelineStage dstStageMask, DependencyFlag flags, Access srcAccessMask, Access dstAccessMask, sb::Image::Layout oldLayout, sb::Image::Layout newLayout, sb::Image &image)
{
	Vk::ImageView &vk_img = reinterpret_cast<Vk::ImageView&>(image);

	VkImageMemoryBarrier barrier {};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.srcAccessMask = util::enum_underlying(srcAccessMask);
	barrier.dstAccessMask = util::enum_underlying(dstAccessMask);
	barrier.oldLayout = static_cast<VkImageLayout>(oldLayout);
	barrier.newLayout = static_cast<VkImageLayout>(newLayout);
	barrier.srcQueueFamilyIndex = 0;
	barrier.dstQueueFamilyIndex = 0;
	barrier.image = vk_img.getImage();
	barrier.subresourceRange.aspectMask = util::enum_underlying(vk_img.getAspect());
	barrier.subresourceRange.baseArrayLayer = vk_img.getArrayRange().off;
	barrier.subresourceRange.layerCount = vk_img.getArrayRange().size;
	barrier.subresourceRange.baseMipLevel = vk_img.getMipRange().off;
	barrier.subresourceRange.levelCount = vk_img.getMipRange().size;
	vkCmdPipelineBarrier(*this, util::enum_underlying(srcStageMask), util::enum_underlying(dstStageMask), util::enum_underlying(flags), 0, nullptr, 0, nullptr, 1, &barrier);
}

void Vk::CommandBuffer::setViewport(const rect2 &area, float minDepth, float maxDepth)
{
	VkViewport viewport;
	viewport.x = area.offset.x;
	viewport.y = area.offset.y;
	viewport.width = area.extent.x;
	viewport.height = area.extent.y;
	viewport.minDepth = minDepth;
	viewport.maxDepth = maxDepth;
	vkCmdSetViewport(*this, 0, 1, &viewport);
}

void Vk::CommandBuffer::setScissor(const srect2 &scissor)
{
	VkRect2D vk_s;
	vk_s.offset.x = scissor.offset.x;
	vk_s.offset.y = scissor.offset.y;
	vk_s.extent.width = scissor.extent.x;
	vk_s.extent.height = scissor.extent.y;
	vkCmdSetScissor(*this, 0, 1, &vk_s);
}

void Vk::CommandBuffer::blit(sb::Image &srcImage, sb::Image::Layout srcLayout, const srect3 &srcRegion, sb::Image &dstImage, sb::Image::Layout dstLayout, const srect3 &dstRegion, Filter filter)
{
	auto &vk_src = reinterpret_cast<Vk::ImageView&>(srcImage);
	auto &vk_dst = reinterpret_cast<Vk::ImageView&>(dstImage);

	auto st_to_i32 = [](size_t v){
		return static_cast<int32_t>(static_cast<uint32_t>(v));
	};

	VkImageBlit region;
	region.srcSubresource.aspectMask = static_cast<VkImageAspectFlags>(vk_src.getAspect());
	region.srcSubresource.mipLevel = vk_src.getMipRange().off;
	region.srcSubresource.baseArrayLayer = vk_src.getArrayRange().off;
	region.srcSubresource.layerCount = vk_src.getArrayRange().size;
	region.srcOffsets[0] = VkOffset3D{st_to_i32(srcRegion.offset.x), st_to_i32(srcRegion.offset.y), st_to_i32(srcRegion.offset.z)};
	region.srcOffsets[1] = VkOffset3D{st_to_i32(srcRegion.offset.x) + st_to_i32(srcRegion.extent.x), st_to_i32(srcRegion.offset.y + srcRegion.extent.y), st_to_i32(srcRegion.offset.z + srcRegion.extent.z)};

	region.dstSubresource.aspectMask = static_cast<VkImageAspectFlags>(vk_dst.getAspect());
	region.dstSubresource.mipLevel = vk_dst.getMipRange().off;
	region.dstSubresource.baseArrayLayer = vk_dst.getArrayRange().off;
	region.dstSubresource.layerCount = vk_dst.getArrayRange().size;
	region.dstOffsets[0] = VkOffset3D{st_to_i32(dstRegion.offset.x), st_to_i32(dstRegion.offset.y), st_to_i32(dstRegion.offset.z)};
	region.dstOffsets[1] = VkOffset3D{st_to_i32(dstRegion.offset.x + dstRegion.extent.x), st_to_i32(dstRegion.offset.y + dstRegion.extent.y), st_to_i32(dstRegion.offset.z + dstRegion.extent.z)};

	vkCmdBlitImage(*this, vk_src.getImage(), static_cast<VkImageLayout>(util::enum_underlying(srcLayout)), vk_dst.getImage(), static_cast<VkImageLayout>(util::enum_underlying(dstLayout)), 1, &region, static_cast<VkFilter>(util::enum_underlying(filter)));
}

void Vk::CommandBuffer::copyBufferToImage(const sb::Buffer::Region &srcBuffer, sb::Image &dstImage, sb::Image::Layout dstImageLayout, const srect3 &dstRegion)
{
	auto &vk_src = reinterpret_cast<Vk::VmaBuffer&>(srcBuffer.buffer);;
	auto &vk_dst = reinterpret_cast<Vk::ImageView&>(dstImage);;

	auto st_to_i32 = [](size_t v){
		return static_cast<int32_t>(static_cast<uint32_t>(v));
	};
	auto st_to_u32 = [](size_t v){
		return static_cast<uint32_t>(v);
	};

	VkBufferImageCopy region;

	region.bufferOffset = srcBuffer.offset;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;
	region.imageSubresource.aspectMask = static_cast<VkImageAspectFlags>(vk_dst.getAspect());
	region.imageSubresource.mipLevel = vk_dst.getMipRange().off;
	region.imageSubresource.baseArrayLayer = vk_dst.getArrayRange().off;
	region.imageSubresource.layerCount = vk_dst.getArrayRange().size;
	region.imageOffset = VkOffset3D{st_to_i32(dstRegion.offset.x), st_to_i32(dstRegion.offset.y), st_to_i32(dstRegion.offset.z)};
	region.imageExtent = VkExtent3D{st_to_u32(dstRegion.extent.x), st_to_u32(dstRegion.extent.y), st_to_u32(dstRegion.extent.z)};

	vkCmdCopyBufferToImage(*this, vk_src, vk_dst.getImage(), static_cast<VkImageLayout>(util::enum_underlying(dstImageLayout)), 1, &region);
}

Vk::CommandPool::CommandPool(Device &dev, VkQueueFamilyIndex familyIndex, bool isReset) :
	Device::Handle<VkCommandPool>(dev, create(dev, familyIndex, isReset))
{
}

VkCommandPool Vk::CommandPool::create(Device &dev, VkQueueFamilyIndex familyIndex, bool isReset)
{
	VkCommandPoolCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	if (isReset)
		ci.flags |= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	ci.queueFamilyIndex = familyIndex;

	return dev.createVk(vkCreateCommandPool, ci);
}

Vk::CommandPool::~CommandPool(void)
{
}

template <>
void Vk::Device::Handle<VkCommandPool>::destroy(Vk::Device &device, VkCommandPool commandPool)
{
	device.destroy(vkDestroyCommandPool, commandPool);
}

std::unique_ptr<sb::CommandBuffer> Vk::CommandPool::commandBuffer(sb::CommandBuffer::Level level)
{
	return std::make_unique<CommandBuffer>(*this, level);
}

Vk::Queue::Queue(Device &dev, VkQueueFamilyIndex familyIndex, VkQueue queue) :
	m_device(dev),
	m_family_index(familyIndex),
	m_handle(queue)
{
}

Vk::Queue::~Queue(void)
{
}

std::unique_ptr<sb::CommandPool> Vk::Queue::commandPool(bool isReset)
{
	return std::make_unique<CommandPool>(m_device, m_family_index, isReset);
}

void Vk::Queue::submit(size_t submitCount, SubmitInfo *submits, sb::Fence *fence)
{
	size_t waitSemaphoreCount = 0;
	size_t commandBufferCount = 0;
	size_t signalSemaphoreCount = 0;
	for (size_t i = 0; i < submitCount; i++) {
		SubmitInfo &cur = submits[i];
		waitSemaphoreCount += cur.waitSemaphoreCount;
		commandBufferCount += cur.commandBufferCount;
		signalSemaphoreCount += cur.signalSemaphoreCount;
	}
	VkSemaphore waitSemaphores[waitSemaphoreCount];
	VkPipelineStageFlags waitDstStageMask[waitSemaphoreCount];
	VkCommandBuffer commandBuffers[commandBufferCount];
	VkSemaphore signalSemaphores[signalSemaphoreCount];
	waitSemaphoreCount = 0;
	commandBufferCount = 0;
	signalSemaphoreCount = 0;

	VkSubmitInfo submits_vla[submitCount];
	for (size_t i = 0; i < submitCount; i++) {
		auto &cur = submits[i];

		auto wWaitSemaphores = &waitSemaphores[waitSemaphoreCount];
		auto wWaitDstStageMask = &waitDstStageMask[waitSemaphoreCount];
		auto wCommandBuffers = &commandBuffers[commandBufferCount];
		auto wSignalSemaphores = &signalSemaphores[signalSemaphoreCount];

		for (size_t i = 0; i < cur.waitSemaphoreCount; i++) {
			wWaitSemaphores[i] = reinterpret_cast<Semaphore&>(*cur.waitSemaphores[i].first);
			wWaitDstStageMask[i] = util::enum_underlying(cur.waitSemaphores[i].second);
		}

		for (size_t i = 0; i < cur.commandBufferCount; i++)
			wCommandBuffers[i] = reinterpret_cast<CommandBuffer&>(*cur.commandBuffers[i]);

		for (size_t i = 0; i < cur.signalSemaphoreCount; i++)
			wSignalSemaphores[i] = reinterpret_cast<Semaphore&>(*cur.signalSemaphores[i]);

		VkSubmitInfo sub {};
		sub.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		sub.waitSemaphoreCount = cur.waitSemaphoreCount;
		sub.pWaitSemaphores = wWaitSemaphores;
		sub.pWaitDstStageMask = wWaitDstStageMask;
		sub.commandBufferCount = cur.commandBufferCount;
		sub.pCommandBuffers = wCommandBuffers;
		sub.signalSemaphoreCount = cur.signalSemaphoreCount;
		sub.pSignalSemaphores = wSignalSemaphores;

		waitSemaphoreCount += cur.waitSemaphoreCount;
		commandBufferCount += cur.commandBufferCount;
		signalSemaphoreCount += cur.signalSemaphoreCount;
		submits_vla[i] = sub;
	}

	Vk::assert(vkQueueSubmit(m_handle, submitCount, submits_vla, fence ? reinterpret_cast<Fence&>(*fence) : VK_NULL_HANDLE));
}

void Vk::Queue::present(size_t waitSemaphoreCount, sb::Semaphore **waitSemaphores, sb::Swapchain::Image2D &image)
{
	VkSemaphore wait_semaphores_vla[waitSemaphoreCount];
	for (size_t i = 0; i < waitSemaphoreCount; i++)
		wait_semaphores_vla[i] = *reinterpret_cast<Semaphore*>(waitSemaphores[i]);

	auto &sp = reinterpret_cast<Swapchain&>(sb::Swapchain::Image2D::Getter().get(image));
	VkSwapchainKHR swapchain = sp;
	uint32_t ndx = &image - sp.getImages().data();

	VkPresentInfoKHR pi {};
	pi.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	pi.waitSemaphoreCount = waitSemaphoreCount;
	pi.pWaitSemaphores = wait_semaphores_vla;
	pi.swapchainCount = 1;
	pi.pSwapchains = &swapchain;
	pi.pImageIndices = &ndx;

	Vk::assert(vkQueuePresentKHR(m_handle, &pi));
}

void Vk::Queue::waitIdle(void)
{
	vkQueueWaitIdle(*this);
}

Vk::Model::Model(VmaBuffer &buffer, size_t vertexCount) :
	m_buffer(buffer),
	m_vertex_count(vertexCount)
{
}

Vk::Model::~Model(void)
{
}

void Vk::Model::draw(sb::CommandBuffer &cmd)
{
	auto &vk_cmd = reinterpret_cast<CommandBuffer&>(cmd);
	VkBuffer buffer = m_buffer;
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(vk_cmd, 0, 1, &buffer, &offset);
	vkCmdDraw(vk_cmd, m_vertex_count, 1, 0, 0);
}

Vk::ModelIndexed::ModelIndexed(VmaBuffer &buffer, VmaBuffer &indexBuffer, VkIndexType indexType, size_t indexCount) :
	m_buffer(buffer),
	m_index_buffer(indexBuffer),
	m_index_type(indexType),
	m_index_count(indexCount)
{
}

Vk::ModelIndexed::~ModelIndexed(void)
{
}

void Vk::ModelIndexed::draw(sb::CommandBuffer &cmd)
{
	auto &vk_cmd = reinterpret_cast<CommandBuffer&>(cmd);
	VkBuffer buffer = m_buffer;
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(vk_cmd, 0, 1, &buffer, &offset);
	vkCmdBindIndexBuffer(vk_cmd, m_index_buffer, 0, m_index_type);
	vkCmdDrawIndexed(vk_cmd, m_index_count, 1, 0, 0, 0);
}

Vk::Sampler::Sampler(Device &dev, VkSampler sampler) :
	Device::Handle<VkSampler>(dev, sampler)
{
}

Vk::Sampler::~Sampler(void)
{
}

template <>
void Vk::Device::Handle<VkSampler>::destroy(Vk::Device &device, VkSampler sampler)
{
	device.destroy(vkDestroySampler, sampler);
}

}