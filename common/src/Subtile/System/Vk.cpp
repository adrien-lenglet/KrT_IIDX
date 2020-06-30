#include <iostream>
#include <set>
#include "Vk.hpp"

namespace Subtile {
namespace System {

Vk::Vk(bool isDebug, Glfw &&glfw) :
	m_glfw(std::move(glfw)),
	m_instance(isDebug, m_glfw.getWindow(),
		isDebug ? util::svec{"VK_LAYER_KHRONOS_validation"} : util::svec{},
		m_glfw.getRequiredVkInstanceExts() + (isDebug ? util::svec{VK_EXT_DEBUG_UTILS_EXTENSION_NAME} : util::svec{})
	),
	m_surface(m_instance.getSurface()),
	m_physical_device(m_instance.enumerateDevices().getBest()),
	m_device(m_physical_device, getDesiredQueues()),
	m_graphics_queue(m_device.getQueue(*m_physical_device.getQueues().indexOf(VK_QUEUE_GRAPHICS_BIT), 0)),
	m_present_queue(m_device.getQueue(*m_physical_device.getQueues().presentation(), 0))
{
}

Vk::~Vk(void)
{
}

void Vk::scanInputs(void)
{
	return m_glfw.scanInputs();
}

const std::map<std::string, System::IInput&>& Vk::getInputs(void)
{
	return m_glfw.getInputs();
}

const std::string& Vk::resultToString(VkResult res)
{
	static const std::map<VkResult, std::string> table = {
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

Vk::PhysicalDevice::PhysicalDevice(VkPhysicalDevice device, Vk::Surface &surface) :
	m_device(device),
	m_surface(surface),
	m_props(get<VkPhysicalDeviceProperties>(vkGetPhysicalDeviceProperties, m_device)),
	m_features(get<VkPhysicalDeviceFeatures>(vkGetPhysicalDeviceFeatures, m_device)),
	m_queue_families(*this)
{
}

Vk::PhysicalDevice::operator VkPhysicalDevice(void) const
{
	return m_device;
}

const VkPhysicalDeviceProperties& Vk::PhysicalDevice::properties(void) const
{
	return m_props;
}

const VkPhysicalDeviceFeatures& Vk::PhysicalDevice::features(void) const
{
	return m_features;
}

bool Vk::PhysicalDevice::getSurfaceSupport(uint32_t queueFamilyIndex) const
{
	return create<VkBool32>(vkGetPhysicalDeviceSurfaceSupportKHR, m_device, queueFamilyIndex, m_surface);
}

bool Vk::PhysicalDevice::isCompetent(void) const
{
	return m_queue_families.indexOf(VK_QUEUE_GRAPHICS_BIT) && m_queue_families.presentation();
}

size_t Vk::PhysicalDevice::getScore(void) const
{
	size_t res = 0;

	if (m_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		res += 1;
	return res;
}

const Vk::PhysicalDevice::QueueFamilies& Vk::PhysicalDevice::getQueues(void) const
{
	return m_queue_families;
}

Vk::PhysicalDevice::QueueFamilies::QueueFamilies(Vk::PhysicalDevice &device) :
	m_queues(getCollection<VkQueueFamilyProperties>(vkGetPhysicalDeviceQueueFamilyProperties, device)),
	m_presentation_queue(getPresentationQueue(device))
{
}

const std::vector<VkQueueFamilyProperties>& Vk::PhysicalDevice::QueueFamilies::properties(void) const
{
	return m_queues;
}

std::optional<uint32_t> Vk::PhysicalDevice::QueueFamilies::indexOf(VkQueueFlagBits queueFlags) const
{
	uint32_t res = 0;

	for (auto &q : m_queues) {
		if (q.queueFlags & queueFlags)
			return res;
		res++;
	}
	return std::nullopt;
}

std::optional<uint32_t> Vk::PhysicalDevice::QueueFamilies::presentation(void) const
{
	return m_presentation_queue;
}

std::optional<uint32_t> Vk::PhysicalDevice::QueueFamilies::getPresentationQueue(PhysicalDevice &device)
{
	uint32_t res = 0;

	for (auto &q : m_queues) {
		static_cast<void>(q);
		if (device.getSurfaceSupport(res))
			return res;
		res++;
	}
	return std::nullopt;
}

Vk::PhysicalDevices::PhysicalDevices(Vk::Instance &instance) :
	m_devices(enumerate(instance))
{
}

const Vk::PhysicalDevice& Vk::PhysicalDevices::getBest(void) const
{
	std::map<size_t, std::reference_wrapper<const PhysicalDevice>> cands;

	for (auto &p : m_devices)
		if (p.isCompetent())
			cands.emplace(p.getScore(), p);
	if (cands.size() == 0)
		throw std::runtime_error("No physical device found");
	return cands.rbegin()->second.get();
}

Vk::Surface& Vk::Instance::getSurface(void)
{
	return m_surface;
}

std::vector<Vk::PhysicalDevice> Vk::PhysicalDevices::enumerate(Instance &instance)
{
	auto devices = enumerateAbstract<VkPhysicalDevice>(vkEnumeratePhysicalDevices, instance);

	std::vector<Vk::PhysicalDevice> res;
	res.reserve(devices.size());

	for (auto &d : devices)
		res.emplace_back(d, instance.getSurface());
	return res;
}

Vk::Instance::Instance(bool isDebug, Glfw::Window &window, const util::svec &layers, const util::svec &extensions) :
	Vk::Handle<VkInstance>(createInstance(layers, extensions)),
	m_messenger(createMessenger(isDebug)),
	m_surface(window, *this)
{
}

VkInstance Vk::Instance::createInstance(const util::svec &layers, const util::svec &extensions)
{
	VkApplicationInfo appinfo {};

	appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appinfo.pApplicationName = "SUBTILE® Application";
	appinfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	appinfo.pEngineName = "SUBTILE®";
	appinfo.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	appinfo.apiVersion = VK_API_VERSION_1_2;

	VkInstanceCreateInfo createInfo {};

	createInfo.pApplicationInfo = &appinfo;
	auto clayers = layers.c_strs();
	createInfo.enabledLayerCount = clayers.size();
	createInfo.ppEnabledLayerNames = clayers.data();
	auto cexts = extensions.c_strs();
	createInfo.enabledExtensionCount = cexts.size();
	createInfo.ppEnabledExtensionNames = cexts.data();

	return create<VkInstance>(vkCreateInstance, &createInfo, nullptr);
}

std::optional<Vk::Instance::Messenger> Vk::Instance::createMessenger(bool isDebug)
{
	if (isDebug)
		return *this;
	else
		return std::nullopt;
}

template <>
void Vk::Handle<VkInstance>::destroy(VkInstance handle)
{
	vkDestroyInstance(handle, nullptr);
}

Vk::Instance::Messenger::Messenger(Instance &instance) :
	Handle<VkDebugUtilsMessengerEXT>(instance, create(instance))
{
}

static VKAPI_ATTR VkBool32 VKAPI_CALL validation_cb(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void*)
{
	static const std::map<VkDebugUtilsMessageSeverityFlagBitsEXT, std::string> sever_table = {
		{VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT, "VERBOSE"},
		{VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT, "INFO"},
		{VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT, "WARNING"},
		{VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, "ERROR"}
	};

	static const std::map<VkDebugUtilsMessageTypeFlagBitsEXT, std::string> type_table = {
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

VkDebugUtilsMessengerEXT Vk::Instance::Messenger::create(Instance &instance)
{
	VkDebugUtilsMessengerCreateInfoEXT createInfo {};

	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = validation_cb;

	return Vk::create<VkDebugUtilsMessengerEXT>(instance.getProcAddr<PFN_vkCreateDebugUtilsMessengerEXT>("vkCreateDebugUtilsMessengerEXT"), instance, &createInfo, nullptr);
}

template <>
void Vk::Instance::Handle<VkDebugUtilsMessengerEXT>::destroy(Instance &instance, VkDebugUtilsMessengerEXT handle)
{
	instance.getProcAddr<PFN_vkDestroyDebugUtilsMessengerEXT>("vkDestroyDebugUtilsMessengerEXT")(instance, handle, nullptr);
}

Vk::PhysicalDevices Vk::Instance::enumerateDevices(void)
{
	return *this;
}

Vk::Device::Device(PhysicalDevice &physicalDevice, const QueuesCreateInfo &queues) :
	Handle<VkDevice>(create(physicalDevice, queues))
{
}

VkDevice Vk::Device::create(PhysicalDevice &physicalDevice, const QueuesCreateInfo &queues)
{
	auto vk_queues = queues.getInfos();

	VkDeviceCreateInfo createInfo {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = vk_queues.size();
	createInfo.pQueueCreateInfos = vk_queues.data();
	createInfo.pEnabledFeatures = &physicalDevice.features();

	return Vk::create<VkDevice>(vkCreateDevice, physicalDevice, &createInfo, nullptr);
}

Vk::Device::QueueCreateInfo::QueueCreateInfo(uint32_t family_ndx, const std::vector<float> &priorities) :
	m_priorities(priorities),
	m_info({})
{
	m_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	m_info.queueFamilyIndex = family_ndx;
	m_info.queueCount = m_priorities.size();
	m_info.pQueuePriorities = m_priorities.data();
}

Vk::Device::QueueCreateInfo::QueueCreateInfo(const Vk::Device::QueueCreateInfo::Struct &str) :
	QueueCreateInfo(str.family_ndx, str.priorities)
{
}

const VkDeviceQueueCreateInfo& Vk::Device::QueueCreateInfo::getInfo(void) const
{
	return m_info;
}

Vk::Device::QueuesCreateInfo::QueuesCreateInfo(void)
{
}

Vk::Device::QueuesCreateInfo::QueuesCreateInfo(std::initializer_list<QueueCreateInfo> queues)
{
	for (auto &q : queues)
		add(q);
}

const std::vector<VkDeviceQueueCreateInfo>& Vk::Device::QueuesCreateInfo::getInfos(void) const
{
	return m_vk_infos;
}

template <>
void Vk::Handle<VkDevice>::destroy(VkDevice device)
{
	vkDestroyDevice(device, nullptr);
}

VkQueue Vk::Device::getQueue(uint32_t family_ndx, uint32_t ndx)
{
	return get<VkQueue>(vkGetDeviceQueue, *this, family_ndx, ndx);
}

Vk::Surface::Surface(Glfw::Window &window, Vk::Instance &instance) :
	Instance::Handle<VkSurfaceKHR>(instance, create<VkSurfaceKHR>(glfwCreateWindowSurface, instance, window, nullptr))
{
}

template <>
void Vk::Instance::Handle<VkSurfaceKHR>::destroy(Vk::Instance &instance, VkSurfaceKHR surface)
{
	vkDestroySurfaceKHR(instance, surface, nullptr);
}

Vk::Device::QueuesCreateInfo Vk::getDesiredQueues(void)
{
	auto &queues = m_physical_device.getQueues();
	std::set<uint32_t> unique_queues {*queues.indexOf(VK_QUEUE_GRAPHICS_BIT), *queues.presentation()};
	Device::QueuesCreateInfo res;

	for (auto &q : unique_queues)
		res.add(q, std::vector<float>{1.0f});
	return res;
}

}
}