#include <iostream>
#include <set>
#include "Vk.hpp"

namespace Subtile {
namespace System {

Vk::Vk(bool isDebug, Glfw &&glfw) :
	m_glfw(std::move(glfw)),
	m_instance(isDebug, m_glfw),
	m_device(createDevice()),
	m_graphics_queue(m_device.getQueue(*m_device.physical().queues().indexOf(VK_QUEUE_GRAPHICS_BIT), 0)),
	m_present_queue(m_device.getQueue(*m_device.physical().queues().presentation(), 0)),
	m_swapchain(m_glfw.getWindow(), m_device)
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

Vk::PhysicalDevice::PhysicalDevice(VkPhysicalDevice device, Vk::Surface &surface) :
	m_device(device),
	m_surface(surface),
	m_props(get<VkPhysicalDeviceProperties>(vkGetPhysicalDeviceProperties, m_device)),
	m_features(get<VkPhysicalDeviceFeatures>(vkGetPhysicalDeviceFeatures, m_device)),
	m_queue_families(*this),
	m_phys_surface(*this, surface)
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

const Vk::PhysicalDevice::Surface& Vk::PhysicalDevice::surface(void) const
{
	return m_phys_surface;
}

bool Vk::PhysicalDevice::getSurfaceSupport(uint32_t queueFamilyIndex) const
{
	return create<VkBool32>(vkGetPhysicalDeviceSurfaceSupportKHR, m_device, queueFamilyIndex, m_surface);
}

bool Vk::PhysicalDevice::isCompetent(void) const
{
	return m_queue_families.indexOf(VK_QUEUE_GRAPHICS_BIT) &&
	m_queue_families.presentation() &&
	areExtensionsSupported() &&
	surface().formats().size() > 0 &&
	surface().presentModes().size() > 0;
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
		if (q.queueCount > 0 && q.queueFlags & queueFlags)
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
		if (q.queueCount > 0 && device.getSurfaceSupport(res))
			return res;
		res++;
	}
	return std::nullopt;
}

Vk::PhysicalDevice::Surface::Surface(PhysicalDevice &device, Vk::Surface &surface) :
	m_capabilities(create<VkSurfaceCapabilitiesKHR>(vkGetPhysicalDeviceSurfaceCapabilitiesKHR, device, surface)),
	m_formats(enumerate<VkSurfaceFormatKHR>(vkGetPhysicalDeviceSurfaceFormatsKHR, device, surface)),
	m_present_modes(enumerate<VkPresentModeKHR>(vkGetPhysicalDeviceSurfacePresentModesKHR, device, surface)),
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
		if (f.format == VK_FORMAT_B8G8R8_SRGB && f.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
			return f;
	return *m_formats.begin();
}

VkPresentModeKHR Vk::PhysicalDevice::Surface::choosePresentMode(void) const
{
	for (auto &p : m_present_modes)
		if (p == VK_PRESENT_MODE_FIFO_KHR)
			return p;
	return VK_PRESENT_MODE_IMMEDIATE_KHR;
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

Vk::PhysicalDevice::Surface::operator VkSurfaceKHR(void) const
{
	return m_vk_surface;
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
		throw std::runtime_error("No compatible GPU found");
	return cands.rbegin()->second.get();
}

Vk::Surface& Vk::Instance::getSurface(void)
{
	return m_surface;
}

std::vector<Vk::PhysicalDevice> Vk::PhysicalDevices::enumerate(Instance &instance)
{
	auto devices = Vk::enumerate<VkPhysicalDevice>(vkEnumeratePhysicalDevices, instance);

	std::vector<Vk::PhysicalDevice> res;
	res.reserve(devices.size());

	for (auto &d : devices)
		res.emplace_back(d, instance.getSurface());
	return res;
}

Vk::Instance::Instance(bool isDebug, Glfw &glfw) :
	Vk::Handle<VkInstance>(createInstance(
		isDebug ? util::svec{"VK_LAYER_KHRONOS_validation"} : util::svec{},
		glfw.getRequiredVkInstanceExts() + (isDebug ? util::svec{VK_EXT_DEBUG_UTILS_EXTENSION_NAME} : util::svec{})
	)),
	m_messenger(createMessenger(isDebug)),
	m_surface(glfw.getWindow(), *this)
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

Vk::Device::Device(const PhysicalDevice &physicalDevice, const QueuesCreateInfo &queues) :
	Vk::Handle<VkDevice>(create(physicalDevice, queues)),
	m_physical(physicalDevice)
{
}

VkDevice Vk::Device::create(const PhysicalDevice &physicalDevice, const QueuesCreateInfo &queues)
{
	auto vk_queues = queues.getInfos();

	VkDeviceCreateInfo createInfo {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = vk_queues.size();
	createInfo.pQueueCreateInfos = vk_queues.data();
	createInfo.pEnabledFeatures = &physicalDevice.features();

	auto cexts = PhysicalDevice::required_extensions.c_strs();
	createInfo.enabledExtensionCount = cexts.size();
	createInfo.ppEnabledExtensionNames = cexts.data();

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

const Vk::PhysicalDevice& Vk::Device::physical(void) const
{
	return m_physical;
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

Vk::Device::QueuesCreateInfo Vk::getDesiredQueues(const Vk::PhysicalDevice &dev)
{
	auto &queues = dev.queues();
	std::set<uint32_t> unique_queues {*queues.indexOf(VK_QUEUE_GRAPHICS_BIT), *queues.presentation()};
	Device::QueuesCreateInfo res;

	for (auto &q : unique_queues)
		res.add(q, std::vector<float>{1.0f});
	return res;
}

Vk::Device Vk::createDevice(void)
{
	auto devs = m_instance.enumerateDevices();
	auto &phys = devs.getBest();

	return Device(phys, getDesiredQueues(phys));
}

Vk::ImageView::ImageView(Vk::Device &device, VkImageView imageView) :
	Device::Handle<VkImageView>(device, imageView)
{
}

VkImageView Vk::ImageView::create(Vk::Device &device, VkImage image, VkImageViewType viewType, VkFormat format, const VkImageSubresourceRange &subres)
{
	VkImageViewCreateInfo createInfo {};

	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	createInfo.image = image;
	createInfo.viewType = viewType;
	createInfo.format = format;
	createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfo.subresourceRange = subres;

	return Vk::create<VkImageView>(vkCreateImageView, device, &createInfo, nullptr);
}

template <>
void Vk::Device::Handle<VkImageView>::destroy(Vk::Device &device, VkImageView imageView)
{
	vkDestroyImageView(device, imageView, nullptr);
}

Vk::Swapchain::Swapchain(const Glfw::Window &window, Vk::Device &device) :
	Device::Handle<VkSwapchainKHR>(device, create(window, device)),
	m_images(enumerate<VkImage>(vkGetSwapchainImagesKHR, device, *this)),
	m_views(createViews(device))
{
}

VkSwapchainKHR Vk::Swapchain::create(const Glfw::Window &window, Vk::Device &device)
{
	VkSwapchainCreateInfoKHR createInfo {};
	auto &phys = device.physical();
	auto &surface = phys.surface();

	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;
	createInfo.minImageCount = surface.capabilities().minImageCount + 1;
	if (surface.capabilities().maxImageCount > 0)
		createInfo.minImageCount = std::min(createInfo.minImageCount, surface.capabilities().maxImageCount);
	auto fmt = surface.chooseFormat();
	createInfo.imageFormat = fmt.format;
	createInfo.imageColorSpace = fmt.colorSpace;
	auto winsize = window.getSize();
	createInfo.imageExtent = surface.chooseExtent(VkExtent2D{static_cast<uint32_t>(winsize.x), static_cast<uint32_t>(winsize.y)});
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	auto &queues = phys.queues();
	std::set<uint32_t> unique_queues {*queues.indexOf(VK_QUEUE_GRAPHICS_BIT), *queues.presentation()};
	std::vector<uint32_t> queues_ndx(unique_queues.begin(), unique_queues.end());
	createInfo.imageSharingMode = queues_ndx.size() > 1 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
	createInfo.queueFamilyIndexCount = queues_ndx.size();
	createInfo.pQueueFamilyIndices = queues_ndx.data();
	createInfo.preTransform = surface.capabilities().currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = surface.choosePresentMode();
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	return Vk::create<VkSwapchainKHR>(vkCreateSwapchainKHR, device, &createInfo, nullptr);
}

std::vector<Vk::ImageView> Vk::Swapchain::createViews(Vk::Device &dev)
{
	std::vector<Vk::ImageView> res;

	auto fmt = dev.physical().surface().chooseFormat().format;
	for (auto &i : m_images)
		res.emplace_back(dev, i, VK_IMAGE_VIEW_TYPE_2D, fmt);
	return res;
}

template <>
void Vk::Device::Handle<VkSwapchainKHR>::destroy(Vk::Device &device, VkSwapchainKHR swapchain)
{
	vkDestroySwapchainKHR(device, swapchain, nullptr);
}

VkDescriptorType Vk::descriptorType(sb::Shader::DescriptorType type)
{
	static const std::map<sb::Shader::DescriptorType, VkDescriptorType> table {
		{sb::Shader::DescriptorType::UniformBuffer, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER},
		{sb::Shader::DescriptorType::CombinedImageSampler, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER}
	};

	return table.at(type);
}

Vk::DescriptorSetLayout::DescriptorSetLayout(Vk::Device &device, const sb::Shader::DescriptorSet::Layout &layout) :
	Device::Handle<VkDescriptorSetLayout>(device, create(device, layout)),
	m_layout(layout)
{
}

const sb::Shader::DescriptorSet::Layout& Vk::DescriptorSetLayout::getLayout(void) const
{
	return m_layout;
}

VkDescriptorSetLayout Vk::DescriptorSetLayout::create(Device &device, const sb::Shader::DescriptorSet::Layout &layout)
{
	static const std::map<sb::Shader::Stage, VkShaderStageFlags> stageTable {
		{sb::Shader::Stage::TesselationControl, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT},
		{sb::Shader::Stage::TesselationEvaluation, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT},
		{sb::Shader::Stage::Geometry, VK_SHADER_STAGE_GEOMETRY_BIT},
		{sb::Shader::Stage::Vertex, VK_SHADER_STAGE_VERTEX_BIT},
		{sb::Shader::Stage::Fragment, VK_SHADER_STAGE_FRAGMENT_BIT}
	};

	VkDescriptorSetLayoutCreateInfo createInfo {};

	createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;

	std::vector<VkDescriptorSetLayoutBinding> bindings;
	for (auto &b : layout.getBindings()) {
		VkDescriptorSetLayoutBinding r {};
		r.binding = b.binding;
		r.descriptorType = descriptorType(b.descriptorType);
		r.descriptorCount = b.descriptorCount;
		for (auto &s : b.stages)
			r.stageFlags |= stageTable.at(s);

		bindings.emplace_back(r);
	}

	createInfo.bindingCount = bindings.size();
	createInfo.pBindings = bindings.data();

	return Vk::create<VkDescriptorSetLayout>(vkCreateDescriptorSetLayout, device, &createInfo, nullptr);
}

template <>
void Vk::Device::Handle<VkDescriptorSetLayout>::destroy(Vk::Device &device, VkDescriptorSetLayout layout)
{
	vkDestroyDescriptorSetLayout(device, layout, nullptr);
}

Vk::DescriptorSet::DescriptorSet(Vk::Device &dev, const Vk::DescriptorSetLayout &layout) :
	Device::Handle<VkDescriptorPool>(dev, createPool(dev, layout)),
	m_descriptor_set(create(layout))
{
}

void Vk::DescriptorSet::write(size_t offset, size_t range, const void *data)
{
}

VkDescriptorPool Vk::DescriptorSet::createPool(Device &dev, const DescriptorSetLayout &layout)
{
	VkDescriptorPoolCreateInfo createInfo {};

	createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	createInfo.maxSets = 1;

	std::map<VkDescriptorType, size_t> typeCount;
	for (auto &b : layout.getLayout().getBindings())
		typeCount[descriptorType(b.descriptorType)] += b.descriptorCount;
	std::vector<VkDescriptorPoolSize> sizes;
	for (auto &t : typeCount) {
		VkDescriptorPoolSize s;
		s.type = t.first;
		s.descriptorCount = t.second;
		sizes.emplace_back(s);
	}

	createInfo.poolSizeCount = sizes.size();
	createInfo.pPoolSizes = sizes.data();

	return Vk::create<VkDescriptorPool>(vkCreateDescriptorPool, dev, &createInfo, nullptr);
}

VkDescriptorSet Vk::DescriptorSet::create(const DescriptorSetLayout &layout)
{
	VkDescriptorSetAllocateInfo allocInfo {};

	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = *this;
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = &static_cast<const VkDescriptorSetLayout&>(layout);

	return Vk::create<VkDescriptorSet>(vkAllocateDescriptorSets, getDevice(), &allocInfo);
}

template <>
void Vk::Device::Handle<VkDescriptorPool>::destroy(Vk::Device &device, VkDescriptorPool pool)
{
	vkDestroyDescriptorPool(device, pool, nullptr);
}

Vk::Shader::Shader(Vk::Device &device, rs::Shader &shader) :
	m_device(device),
	m_material_layout(device, shader.material()),
	m_object_layout(device, shader.object())
{
	static_cast<void>(shader);
}

std::unique_ptr<sb::Shader::DescriptorSet> Vk::Shader::material(void)
{
	return std::make_unique<Vk::DescriptorSet>(m_device, m_material_layout);
}

std::unique_ptr<sb::Shader::DescriptorSet> Vk::Shader::object(void)
{
	return std::make_unique<Vk::DescriptorSet>(m_device, m_object_layout);
}

std::unique_ptr<sb::Shader> Vk::loadShader(rs::Shader &shader)
{
	return std::make_unique<Shader>(m_device, shader);
}

}
}