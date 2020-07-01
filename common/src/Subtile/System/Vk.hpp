#pragma once

#include <vulkan/vulkan.h>
#include "../ISystem.hpp"
#include "Glfw.hpp"

#undef assert

namespace Subtile {
namespace System {

class Vk : public ISystem
{
	Vk(bool isDebug, Glfw &&glfw);

public:
	template <typename ...Args>
	Vk(bool isDebug, Args &&...args) :
		Vk(isDebug, Glfw(GLFW_NO_API, std::forward<Args>(args)...))
	{
	}
	~Vk(void);

	void scanInputs(void) override;
	const std::map<std::string, System::IInput&>& getInputs(void) override;

private:
	Glfw m_glfw;

	static const std::string& resultToString(VkResult res);
	static void assert(VkResult res);

	template <typename T>
	static std::vector<T> enumerateAbstract(VkResult (*callable)(uint32_t*, T*))
	{
		uint32_t size;

		assert(callable(&size, nullptr));
		std::vector<T> res(size);
		assert(callable(&size, res.data()));
		return res;
	}

	template <typename T, typename C, typename ...Args>
	static std::vector<T> enumerate(C &&callable, Args &&...args)
	{
		uint32_t size;

		assert(callable(std::forward<Args>(args)..., &size, nullptr));
		std::vector<T> res(size);
		assert(callable(std::forward<Args>(args)..., &size, res.data()));
		return res;
	}

	template <typename T, typename C, typename ...Args>
	static T create(C &&callable, Args &&...args)
	{
		T res;
		assert(callable(std::forward<Args>(args)..., &res));
		return res;
	}

	template <typename T, typename C, typename ...Args>
	static T get(C &&callable, Args &&...args)
	{
		T res;
		callable(std::forward<Args>(args)..., &res);
		return res;
	}

	template <typename T, typename C, typename ...Args>
	static std::vector<T> getCollection(C &&callable, Args &&...args)
	{
		uint32_t size;

		callable(std::forward<Args>(args)..., &size, nullptr);
		std::vector<T> res(size);
		callable(std::forward<Args>(args)..., &size, res.data());
		return res;
	}

	template <typename VkHandle>
	class Handle
	{
	public:
		Handle(VkHandle handle) :
			m_handle(handle)
		{
		}

		Handle(Handle &&other) :
			m_handle(other.m_handle)
		{
			m_handle = VK_NULL_HANDLE;
		}

		void destroy(VkHandle handle);

		~Handle(void)
		{
			if (m_handle != VK_NULL_HANDLE)
				destroy(m_handle);
		}

		operator VkHandle(void) const
		{
			return m_handle;
		}

	protected:
		VkHandle m_handle;
	};

	class PhysicalDevices;

	class Instance : public Handle<VkInstance>
	{
	public:
		Instance(bool isDebug, Glfw &window);

		template <typename FunType>
		FunType getProcAddr(const char *name)
		{
			auto res = vkGetInstanceProcAddr(m_handle, name);

			if (res == nullptr)
				throw std::runtime_error(std::string("Can't get proc '") + std::string(name) + std::string("'"));
			return reinterpret_cast<FunType>(res);
		}

		template <typename VkHandle>
		class Handle
		{
		public:
			Handle(Instance &instance, VkHandle handle) :
				m_instance(instance),
				m_handle(handle)
			{
			}

			Handle(Handle &&other) :
				m_instance(other.m_instance),
				m_handle(other.m_handle)
			{
				m_handle = VK_NULL_HANDLE;
			}

			void destroy(Instance &instance, VkHandle handle);

			~Handle(void)
			{
				if (m_handle != VK_NULL_HANDLE)
					destroy(m_instance, m_handle);
			}

			operator VkHandle(void) const
			{
				return m_handle;
			}

		private:
			Instance &m_instance;

		protected:
			VkHandle m_handle;
		};

		class Surface : public Handle<VkSurfaceKHR>
		{
		public:
			Surface(Glfw::Window &window, Instance &instance);
		};

		Surface& getSurface(void);
		PhysicalDevices enumerateDevices(void);

	private:
		class Messenger : public Handle<VkDebugUtilsMessengerEXT>
		{
		public:
			Messenger(Instance &instance);

		private:
			VkDebugUtilsMessengerEXT create(Instance &instance);
		};

		std::optional<Messenger> m_messenger;
		Surface m_surface;

		VkInstance createInstance(const util::svec &layers, const util::svec &extensions);
		std::optional<Messenger> createMessenger(bool isDebug);
	};

	using Surface = typename Instance::Surface;

	class PhysicalDevice
	{
	public:
		PhysicalDevice(VkPhysicalDevice device, Vk::Surface &surface);

		class Surface
		{
		public:
			Surface(PhysicalDevice &device, Vk::Surface &surface);

			const VkSurfaceCapabilitiesKHR& capabilities(void) const;
			const std::vector<VkSurfaceFormatKHR>& formats(void) const;
			const std::vector<VkPresentModeKHR>& presentModes(void) const;

			const VkSurfaceFormatKHR& chooseFormat(void) const;
			VkPresentModeKHR choosePresentMode(void) const;
			VkExtent2D chooseExtent(VkExtent2D baseExtent) const;

			operator VkSurfaceKHR(void) const;

		private:
			const VkSurfaceCapabilitiesKHR m_capabilities;
			const std::vector<VkSurfaceFormatKHR> m_formats;
			const std::vector<VkPresentModeKHR> m_present_modes;
			Vk::Surface &m_vk_surface;
		};

		operator VkPhysicalDevice(void) const;

		const VkPhysicalDeviceProperties& properties(void) const;
		const VkPhysicalDeviceFeatures& features(void) const;
		const Surface& surface(void) const;

		bool getSurfaceSupport(uint32_t queueFamilyIndex) const;
		bool isCompetent(void) const;
		size_t getScore(void) const;

		static const util::svec required_extensions;

		class QueueFamilies
		{
		public:
			QueueFamilies(PhysicalDevice &device);

			const std::vector<VkQueueFamilyProperties>& properties(void) const;
			std::optional<uint32_t> indexOf(VkQueueFlagBits queueFlags) const;
			std::optional<uint32_t> presentation(void) const;

		private:
			std::vector<VkQueueFamilyProperties> m_queues;
			std::optional<uint32_t> m_presentation_queue;

			std::optional<uint32_t> getPresentationQueue(PhysicalDevice &device);
		};

		const QueueFamilies& queues(void) const;

	private:
		VkPhysicalDevice m_device;
		Vk::Surface &m_surface;
		const VkPhysicalDeviceProperties m_props;
		const VkPhysicalDeviceFeatures m_features;
		const QueueFamilies m_queue_families;
		Surface m_phys_surface;

		bool areExtensionsSupported(void) const;
	};

	class PhysicalDevices
	{
	public:
		PhysicalDevices(Instance &instance);

		const PhysicalDevice& getBest(void) const;

	private:
		std::vector<PhysicalDevice> m_devices;

		std::vector<Vk::PhysicalDevice> enumerate(Instance &instance);
	};

	Instance m_instance;

	class Device : public Handle<VkDevice>
	{
	public:
		class QueueCreateInfo
		{
		public:
			struct Struct {
				uint32_t family_ndx;
				std::vector<float> priorities;
			};

			QueueCreateInfo(uint32_t family_ndx, const std::vector<float> &priorities);
			QueueCreateInfo(const Struct &str);

			const VkDeviceQueueCreateInfo& getInfo(void) const;

		private:
			std::vector<float> m_priorities;
			VkDeviceQueueCreateInfo m_info;
		};

		class QueuesCreateInfo
		{
		public:
			QueuesCreateInfo(void);
			QueuesCreateInfo(std::initializer_list<QueueCreateInfo> queues);

			template <typename ...Args>
			void add(Args &&...args)
			{
				m_infos.emplace_back(std::forward<Args>(args)...);
				m_vk_infos.emplace_back(m_infos.rbegin()->getInfo());
			}

			const std::vector<VkDeviceQueueCreateInfo>& getInfos(void) const;

		private:
			std::vector<QueueCreateInfo> m_infos;
			std::vector<VkDeviceQueueCreateInfo> m_vk_infos;
		};

		Device(const PhysicalDevice &physicalDevice, const QueuesCreateInfo &queues);

		const PhysicalDevice& physical(void) const;
		VkQueue getQueue(uint32_t family_ndx, uint32_t ndx);

		template <typename VkHandle>
		class Handle
		{
		public:
			Handle(Device &device, VkHandle handle) :
				m_device(device),
				m_handle(handle)
			{
			}

			Handle(Handle &&other) :
				m_device(other.m_device),
				m_handle(other.m_handle)
			{
				m_handle = VK_NULL_HANDLE;
			}

			void destroy(Device &device, VkHandle handle);

			~Handle(void)
			{
				if (m_handle != VK_NULL_HANDLE)
					destroy(m_device, m_handle);
			}

			operator VkHandle(void) const
			{
				return m_handle;
			}

		private:
			Device &m_device;

		protected:
			VkHandle m_handle;
		};

	private:
		PhysicalDevice m_physical;

		VkDevice create(const PhysicalDevice &physicalDevice, const QueuesCreateInfo &queues);
	};

	Device::QueuesCreateInfo getDesiredQueues(const PhysicalDevice &dev);
	Device createDevice(void);

	Device m_device;
	VkQueue m_graphics_queue;
	VkQueue m_present_queue;

	class Swapchain : public Device::Handle<VkSwapchainKHR>
	{
	public:
		Swapchain(const Glfw::Window &window, Vk::Device &device);

	private:
		std::vector<VkImage> m_images;

		VkSwapchainKHR create(const Glfw::Window &window, Vk::Device &device);
	};

	Swapchain m_swapchain;
};

}
}