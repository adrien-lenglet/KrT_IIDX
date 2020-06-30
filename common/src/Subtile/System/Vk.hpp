#pragma once

#include <vulkan/vulkan.h>
#undef assert
#include "../ISystem.hpp"
#include "Glfw.hpp"

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
	static std::vector<T> enumerate(VkResult (*callable)(uint32_t*, T*))
	{
		uint32_t size;

		assert(callable(&size, nullptr));
		std::vector<T> res(size);
		assert(callable(&size, res.data()));
		return res;
	}

	template <typename T, typename C, typename ...Args>
	static std::vector<T> enumerateAbstract(C &&callable, Args &&...args)
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

	class PhysicalDevice
	{
	public:
		PhysicalDevice(VkPhysicalDevice device);

		operator VkPhysicalDevice(void) const;

		const VkPhysicalDeviceProperties& properties(void) const;
		const VkPhysicalDeviceFeatures& features(void) const;

		bool isCompetent(void) const;
		size_t getScore(void) const;

		class QueueFamilies
		{
		public:
			QueueFamilies(VkPhysicalDevice device);

			const std::vector<VkQueueFamilyProperties>& properties(void) const;
			std::optional<uint32_t> indexOf(VkQueueFlagBits queueFlags) const;

		private:
			std::vector<VkQueueFamilyProperties> m_queues;

			std::vector<VkQueueFamilyProperties> getProps(VkPhysicalDevice device);
		};

		const QueueFamilies& getQueues(void) const;

	private:
		VkPhysicalDevice m_device;
		const VkPhysicalDeviceProperties m_props;
		const VkPhysicalDeviceFeatures m_features;
		const QueueFamilies m_queue_families;
	};

	class Instance;

	class PhysicalDevices
	{
	public:
		PhysicalDevices(Instance &instance);

		const PhysicalDevice& getBest(void) const;

	private:
		std::vector<PhysicalDevice> m_devices;

		std::vector<Vk::PhysicalDevice> enumerate(Instance &instance);
	};

	class Instance : public Handle<VkInstance>
	{
	public:
		Instance(bool isDebug, const util::svec &layers, const util::svec &extensions);

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

		VkInstance createInstance(const util::svec &layers, const util::svec &extensions);
		std::optional<Messenger> createMessenger(bool isDebug);
	};

	Instance m_instance;
	PhysicalDevice m_physical_device;

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

		Device(PhysicalDevice &physicalDevice, const QueuesCreateInfo &queues);

		VkQueue getQueue(uint32_t family_ndx, uint32_t ndx);

	private:
		VkDevice create(PhysicalDevice &physicalDevice, const QueuesCreateInfo &queues);

	};

	Device m_device;
	VkQueue m_graphics_queue;

	class Surface : public Instance::Handle<VkSurfaceKHR>
	{
	public:
		Surface(Glfw::Window &window, Instance &instance);
	};

	Surface m_surface;
};

}
}