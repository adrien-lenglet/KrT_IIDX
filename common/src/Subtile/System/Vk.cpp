#include <iostream>
#include <set>
#include <cstring>
#include <sstream>
#include "Vk.hpp"

namespace Subtile {
namespace System {

Vk::Vk(bool isDebug, Glfw &&glfw) :
	m_is_debug(isDebug),
	m_glfw(std::move(glfw)),
	m_instance(createInstance()),
	m_debug_messenger(createDebugMessenger()),
	m_surface(createSurface()),
	m_device(createDevice()),
	m_graphics_queue(m_device.getQueue(*m_device.physical().queues().indexOf(VK_QUEUE_GRAPHICS_BIT), 0)),
	m_present_queue(m_device.getQueue(*m_device.physical().queues().presentation(), 0)),
	m_swapchain_format(m_device.physical().surface().chooseFormat()),
	m_swapchain(createSwapchain()),
	m_default_render_pass(createDefaultRenderPass())
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

Vk::PhysicalDevices Vk::Instance::enumerateDevices(Vk::Surface &surface)
{
	return PhysicalDevices(*this, surface);
}

Vk::Instance Vk::createInstance(void)
{
	util::svec layers;
	util::svec exts = m_glfw.getRequiredVkInstanceExts();

	if (m_is_debug) {
		layers.emplace_back("VK_LAYER_KHRONOS_validation");
		exts.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	VkApplicationInfo ai {};

	ai.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ai.pApplicationName = "SUBTILE® Application";
	ai.applicationVersion = VK_MAKE_VERSION(0, 0, 0);
	ai.pEngineName = "SUBTILE®";
	ai.engineVersion = VK_MAKE_VERSION(0, 0, 0);
	ai.apiVersion = VK_API_VERSION_1_2;

	VkInstanceCreateInfo createInfo {};

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

Vk::Surface::Surface(Instance &instance, VkSurfaceKHR surface) :
	Instance::Handle<VkSurfaceKHR>(instance, surface)
{
}

template <>
void Vk::Instance::Handle<VkSurfaceKHR>::destroy(Vk::Instance &instance, VkSurfaceKHR surface)
{
	instance.destroy(vkDestroySurfaceKHR, surface);
}

Vk::Surface Vk::createSurface(void)
{
	return m_instance.create<Surface>(glfwCreateWindowSurface, m_glfw.getWindow());
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

Vk::PhysicalDevice::Properties::Properties(const VkPhysicalDeviceProperties &props) :
	VkPhysicalDeviceProperties(props)
{
}

size_t Vk::PhysicalDevice::Properties::getAlignment(sb::Shader::DescriptorType type) const
{
	if (type == sb::Shader::DescriptorType::UniformBuffer)
		return limits.minUniformBufferOffsetAlignment;
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
		if (f.format == VK_FORMAT_B8G8R8A8_SRGB && f.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
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

Vk::PhysicalDevices::PhysicalDevices(Vk::Instance &instance, Vk::Surface &surface) :
	m_devices(enumerate(instance, surface))
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

std::vector<Vk::PhysicalDevice> Vk::PhysicalDevices::enumerate(Instance &instance, Vk::Surface &surface)
{
	auto devices = Vk::enumerate<VkPhysicalDevice>(vkEnumeratePhysicalDevices, instance);

	std::vector<Vk::PhysicalDevice> res;
	res.reserve(devices.size());

	for (auto &d : devices)
		res.emplace_back(d, surface);
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

Vk::Device::Device(Instance &instance, const PhysicalDevice &physicalDevice, VkDevice device) :
	Vk::Handle<VkDevice>(device),
	m_instance(instance),
	m_physical(physicalDevice),
	m_allocator(*this)
{
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
	vkDestroyDevice(device, static_cast<Device&>(*this).m_instance.m_vk.getAllocator());
}

Vk& Vk::Device::vk(void)
{
	return m_instance.m_vk;
}

const Vk::PhysicalDevice& Vk::Device::physical(void) const
{
	return m_physical;
}

Vk::Allocator& Vk::Device::allocator(void)
{
	return m_allocator;
}

VkQueue Vk::Device::getQueue(uint32_t family_ndx, uint32_t ndx)
{
	return get<VkQueue>(vkGetDeviceQueue, *this, family_ndx, ndx);
}

Vk::Device Vk::createDevice(void)
{
	auto devs = m_instance.enumerateDevices(m_surface);
	auto &phys = devs.getBest();
	auto queues = getDesiredQueues(phys);

	auto vk_queues = queues.getInfos();

	VkDeviceCreateInfo createInfo {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = vk_queues.size();
	createInfo.pQueueCreateInfos = vk_queues.data();
	createInfo.pEnabledFeatures = &phys.features();

	auto cexts = PhysicalDevice::required_extensions.c_strs();
	createInfo.enabledExtensionCount = cexts.size();
	createInfo.ppEnabledExtensionNames = cexts.data();

	return Device(m_instance, phys, Vk::create<VkDevice>(vkCreateDevice, phys, &createInfo, getAllocator()));
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
	Buffer(dev, buffer)
{
}

Vk::ImageView::ImageView(Vk::Device &device, VkImageView imageView) :
	Device::Handle<VkImageView>(device, imageView)
{
}

template <>
void Vk::Device::Handle<VkImageView>::destroy(Vk::Device &device, VkImageView imageView)
{
	device.destroy(vkDestroyImageView, imageView);
}

Vk::Swapchain::Swapchain(Vk::Device &device, VkSwapchainKHR swapchain) :
	Device::Handle<VkSwapchainKHR>(device, swapchain),
	m_images(enumerate<VkImage>(vkGetSwapchainImagesKHR, device, *this)),
	m_views(createViews(device))
{
}

std::vector<Vk::ImageView> Vk::Swapchain::createViews(Vk::Device &dev)
{
	std::vector<Vk::ImageView> res;

	VkImageViewCreateInfo ci {};

	ci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	ci.viewType = VK_IMAGE_VIEW_TYPE_2D;
	ci.format = dev.physical().surface().chooseFormat().format;
	ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	ci.subresourceRange.levelCount = VK_REMAINING_MIP_LEVELS;
	ci.subresourceRange.layerCount = VK_REMAINING_ARRAY_LAYERS;

	for (auto &i : m_images) {
		ci.image = i;
		res.emplace_back(dev.create<ImageView>(vkCreateImageView, ci));
	}
	return res;
}

template <>
void Vk::Device::Handle<VkSwapchainKHR>::destroy(Vk::Device &device, VkSwapchainKHR swapchain)
{
	device.destroy(vkDestroySwapchainKHR, swapchain);
}

Vk::Swapchain Vk::createSwapchain(void)
{
	auto &phys = m_device.physical();
	auto &surface = phys.surface();

	VkSwapchainCreateInfoKHR ci {};
	ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	ci.surface = surface;
	ci.minImageCount = surface.capabilities().minImageCount + 1;
	if (surface.capabilities().maxImageCount > 0)
		ci.minImageCount = std::min(ci.minImageCount, surface.capabilities().maxImageCount);
	ci.imageFormat = m_swapchain_format.format;
	ci.imageColorSpace = m_swapchain_format.colorSpace;
	auto winsize = m_glfw.getWindow().getSize();
	ci.imageExtent = surface.chooseExtent(VkExtent2D{static_cast<uint32_t>(winsize.x), static_cast<uint32_t>(winsize.y)});
	ci.imageArrayLayers = 1;
	ci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	auto &queues = phys.queues();
	std::set<uint32_t> unique_queues {*queues.indexOf(VK_QUEUE_GRAPHICS_BIT), *queues.presentation()};
	std::vector<uint32_t> queues_ndx(unique_queues.begin(), unique_queues.end());
	ci.imageSharingMode = queues_ndx.size() > 1 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
	ci.queueFamilyIndexCount = queues_ndx.size();
	ci.pQueueFamilyIndices = queues_ndx.data();
	ci.preTransform = surface.capabilities().currentTransform;
	ci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	ci.presentMode = surface.choosePresentMode();
	ci.clipped = VK_TRUE;
	ci.oldSwapchain = VK_NULL_HANDLE;

	return m_device.create<Swapchain>(vkCreateSwapchainKHR, ci);
}

Vk::RenderPass::RenderPass(Device &dev, VkRenderPass renderPass) :
	Device::Handle<VkRenderPass>(dev, renderPass)
{
}

template <>
void Vk::Device::Handle<VkRenderPass>::destroy(Vk::Device &device, VkRenderPass renderPass)
{
	device.destroy(vkDestroyRenderPass, renderPass);
}

Vk::RenderPass Vk::createDefaultRenderPass(void)
{
	std::vector<VkAttachmentDescription> atts;
	VkAttachmentDescription att {};
	att.format = m_swapchain_format.format;
	att.samples = VK_SAMPLE_COUNT_1_BIT;
	att.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	att.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	att.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	att.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	atts.emplace_back(att);

	std::vector<VkAttachmentReference> colorAtts;
	VkAttachmentReference colorAtt;
	colorAtt.attachment = 0;
	colorAtt.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	colorAtts.emplace_back(colorAtt);

	std::vector<VkSubpassDescription> subs;
	VkSubpassDescription sub {};
	sub.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	sub.colorAttachmentCount = colorAtts.size();
	sub.pColorAttachments = colorAtts.data();
	subs.emplace_back(sub);

	VkRenderPassCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	ci.attachmentCount = atts.size();
	ci.pAttachments = atts.data();
	ci.subpassCount = subs.size();
	ci.pSubpasses = subs.data();
	return m_device.create<RenderPass>(vkCreateRenderPass, ci);
}

Vk::RenderPass& Vk::getDefaultRenderPass(void)
{
	return m_default_render_pass;
}

VkDescriptorType Vk::descriptorType(sb::Shader::DescriptorType type)
{
	static const std::map<sb::Shader::DescriptorType, VkDescriptorType> table {
		{sb::Shader::DescriptorType::UniformBuffer, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER},
		{sb::Shader::DescriptorType::CombinedImageSampler, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER}
	};

	return table.at(type);
}

Vk::DescriptorSetLayout::DescriptorSetLayout(Vk::Device &device, const sb::Shader::DescriptorSet::Layout::Description &desc) :
	Device::Handle<VkDescriptorSetLayout>(device, create(device, desc)),
	m_desc(desc)
{
}

Vk::DescriptorSetLayout::~DescriptorSetLayout(void)
{
}

const sb::Shader::DescriptorSet::Layout::Description& Vk::DescriptorSetLayout::getDescription(void) const
{
	return m_desc;
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
	static const std::map<sb::Shader::Stage, VkShaderStageFlags> stageTable {
		{sb::Shader::Stage::TesselationControl, VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT},
		{sb::Shader::Stage::TesselationEvaluation, VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT},
		{sb::Shader::Stage::Geometry, VK_SHADER_STAGE_GEOMETRY_BIT},
		{sb::Shader::Stage::Vertex, VK_SHADER_STAGE_VERTEX_BIT},
		{sb::Shader::Stage::Fragment, VK_SHADER_STAGE_FRAGMENT_BIT}
	};

	VkDescriptorSetLayoutBinding r {};
	r.binding = b.binding;
	r.descriptorType = descriptorType(b.descriptorType);
	r.descriptorCount = b.descriptorCount;
	if (b.isMapped())
		r.descriptorCount = 1;
	for (auto &s : b.stages)
		r.stageFlags |= stageTable.at(s);
	return r;
}

template <>
void Vk::Device::Handle<VkDescriptorSetLayout>::destroy(Vk::Device &device, VkDescriptorSetLayout layout)
{
	device.destroy(vkDestroyDescriptorSetLayout, layout);
}

std::unique_ptr<sb::Shader::DescriptorSet::Layout> Vk::createDescriptorSetLayout(const sb::Shader::DescriptorSet::Layout::Description &desc)
{
	return std::make_unique<DescriptorSetLayout>(m_device, desc);
}

Vk::DescriptorSet::DescriptorSet(Vk::Device &dev, const Vk::DescriptorSetLayout &layout) :
	Device::Handle<VkDescriptorPool>(dev, createPool(dev, layout)),
	m_descriptor_set(create(layout)),
	m_buffer(createBuffer(layout))
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
		w.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

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

void Vk::DescriptorSet::write(size_t offset, size_t range, const void *data)
{
	if (range == 0)
		return;

	auto dst = m_buffer.map();
	std::memcpy(&static_cast<char*>(dst)[offset], data, range);
	m_buffer.unmap();
}

VkDescriptorPool Vk::DescriptorSet::createPool(Device &dev, const DescriptorSetLayout &layout)
{
	std::map<VkDescriptorType, size_t> typeCount;
	for (auto &b : layout.getDescription())
		typeCount[descriptorType(b.descriptorType)] += b.descriptorCount;
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

VkDescriptorSet Vk::DescriptorSet::create(const DescriptorSetLayout &layout)
{
	Device &dev = *this;

	VkDescriptorSetAllocateInfo ai {};
	ai.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	ai.descriptorPool = *this;
	ai.descriptorSetCount = 1;
	ai.pSetLayouts = &static_cast<const VkDescriptorSetLayout&>(layout);

	if (ai.descriptorPool == VK_NULL_HANDLE)
		return VK_NULL_HANDLE;
	else
		return dev.allocateVk(vkAllocateDescriptorSets, ai);
}

Vk::VmaBuffer Vk::DescriptorSet::createBuffer(const DescriptorSetLayout &layout)
{
	Device &dev = *this;
	std::vector<uint32_t> queues {*dev.physical().queues().indexOf(VK_QUEUE_GRAPHICS_BIT)};
	size_t size = 0;
	for (auto &b : layout.getDescription())
		if (b.isMapped()) {
			size = util::align_dyn(size, dev.physical().properties().getAlignment(b.descriptorType));
			size += b.descriptorCount;
		}

	VkBufferCreateInfo bci {};
	bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bci.size = size;
	bci.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	bci.sharingMode = queues.size() > 1 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
	bci.queueFamilyIndexCount = queues.size();
	bci.pQueueFamilyIndices = queues.data();

	VmaAllocationCreateInfo aci {};
	aci.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

	return dev.allocator().createBuffer(bci, aci);
}

Vk::Model::Model(Vk::Device &dev, size_t count, size_t stride, const void *data) :
	m_count(count),
	m_buffer(createBuffer(dev, count * stride))
{
	if (count > 0) {
		auto dst = m_buffer.map();
		std::memcpy(dst, data, count * stride);
		m_buffer.unmap();
	}
}

Vk::VmaBuffer Vk::Model::createBuffer(Device &dev, size_t size)
{
	std::vector<uint32_t> queues {*dev.physical().queues().indexOf(VK_QUEUE_GRAPHICS_BIT)};

	VkBufferCreateInfo bci {};
	bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bci.size = size;
	bci.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bci.sharingMode = queues.size() > 1 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE;
	bci.queueFamilyIndexCount = queues.size();
	bci.pQueueFamilyIndices = queues.data();

	VmaAllocationCreateInfo aci {};
	aci.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

	if (size == 0)
		return Vk::VmaBuffer(dev, VK_NULL_HANDLE, VK_NULL_HANDLE);
	else
		return dev.allocator().createBuffer(bci, aci);
}

template <>
void Vk::Device::Handle<VkDescriptorPool>::destroy(Vk::Device &device, VkDescriptorPool pool)
{
	device.destroy(vkDestroyDescriptorPool, pool);
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
		{Subtile::Shader::Stage::Fragment, VK_SHADER_STAGE_FRAGMENT_BIT}
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
	m_layouts(shader.loadDescriptorSetLayouts(device.vk())),
	m_pipeline_layout(createPipelineLayout()),
	m_shader_modules(createShaderModules(device, shader)),
	m_pipeline(createPipeline(device, shader))
{
	static_cast<void>(shader);
}

Vk::PipelineLayout Vk::Shader::createPipelineLayout(void)
{
	std::vector<VkDescriptorSetLayout> layouts;

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

Vk::Pipeline Vk::Shader::createPipeline(Vk::Device &device, rs::Shader &shader)
{
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

	std::vector<VkViewport> viewports {	// x, y, w, h, minDepth, maxDepth
		{0.0f, 0.0f, 1600.0f, 900.0f, 0.0f, 1.0f}	// NOTE: temporary, use dynamic states
	};
	std::vector<VkRect2D> scissors {
		{{0, 0}, {1600, 900}}	// NOTE: temporary, use dynamic states
	};
	VkPipelineViewportStateCreateInfo viewport {};
	viewport.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewport.viewportCount = viewports.size();
	viewport.pViewports = viewports.data();
	viewport.scissorCount = scissors.size();
	viewport.pScissors = scissors.data();

	VkPipelineRasterizationStateCreateInfo rasterization {};
	rasterization.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterization.polygonMode = VK_POLYGON_MODE_FILL;
	rasterization.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterization.frontFace = VK_FRONT_FACE_CLOCKWISE;

	VkPipelineMultisampleStateCreateInfo multisample {};
	multisample.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisample.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	std::vector<VkPipelineColorBlendAttachmentState> colorBlendAttachments;
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
	VkPipelineColorBlendStateCreateInfo colorBlend {};
	colorBlend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlend.attachmentCount = colorBlendAttachments.size();
	colorBlend.pAttachments = colorBlendAttachments.data();
	for (size_t i = 0; i < 4; i++)
		colorBlend.blendConstants[i] = 1.0f;

	VkGraphicsPipelineCreateInfo ci {};
	ci.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	ci.stageCount = stages.size();
	ci.pStages = stages.data();
	ci.pVertexInputState = &vertexInput;
	ci.pInputAssemblyState = &inputAssembly;
	ci.pViewportState = &viewport;
	ci.pRasterizationState = &rasterization;
	ci.pMultisampleState = &multisample;
	ci.pColorBlendState = &colorBlend;
	ci.layout = m_pipeline_layout;
	ci.renderPass = device.vk().getDefaultRenderPass();
	ci.subpass = 0;

	return device.create<Pipeline>(vkCreateGraphicsPipelines, ci);
}

std::unique_ptr<sb::Shader::DescriptorSet> Vk::Shader::set(size_t ndx)
{
	return std::make_unique<Vk::DescriptorSet>(m_device, reinterpret_cast<const DescriptorSetLayout&>(m_layouts.at(ndx)->resolve()));
}

std::unique_ptr<sb::Shader::Model> Vk::Shader::model(size_t count, size_t stride, const void *data)
{
	return std::make_unique<Vk::Model>(m_device, count, stride, data);
}

std::unique_ptr<sb::Shader> Vk::loadShader(rs::Shader &shader)
{
	return std::make_unique<Shader>(m_device, shader);
}

}
}