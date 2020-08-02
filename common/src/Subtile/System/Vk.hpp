#pragma once

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
#include "../ISystem.hpp"
#include "Glfw.hpp"
#include "Subtile/Shader.hpp"
#include "Subtile/Model.hpp"

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

	const VkAllocationCallbacks* getAllocator(void) const;

private:
	bool m_is_debug;
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
		void destroy(VkHandle handle);

	public:
		Handle(VkHandle handle) :
			m_handle(handle)
		{
		}

		Handle(Handle &&other) :
			m_handle(other.m_handle)
		{
			other.m_handle = VK_NULL_HANDLE;
		}

		~Handle(void)
		{
			if (m_handle != VK_NULL_HANDLE)
				destroy(m_handle);
		}

		operator const VkHandle&(void) const
		{
			return m_handle;
		}

	protected:
		VkHandle m_handle;
	};

	template <typename DepType, typename VkHandle>
	class HandleDep
	{
		void destroy(DepType &dep, VkHandle handle);

	public:
		HandleDep(DepType &dep, VkHandle handle) :
			m_dep(dep),
			m_handle(handle)
		{
		}

		HandleDep(HandleDep &&other) :
			m_dep(other.m_dep),
			m_handle(other.m_handle)
		{
			other.m_handle = VK_NULL_HANDLE;
		}

		~HandleDep(void)
		{
			if (m_handle != VK_NULL_HANDLE)
				destroy(m_dep, m_handle);
		}

		operator const VkHandle&(void) const
		{
			return m_handle;
		}

		VkHandle getHandle(void) const
		{
			return m_handle;
		}

	private:
		DepType &m_dep;

	protected:
		VkHandle m_handle;

		operator DepType&(void)
		{
			return m_dep;
		}

		operator const DepType&(void) const
		{
			return m_dep;
		}
	};

	class PhysicalDevices;
	class Surface;
	class Device;

	class Instance : public Handle<VkInstance>
	{
		friend Handle<VkInstance>;
		friend Handle<VkDevice>;
		friend Device;

	public:
		Instance(Vk &vk, VkInstance instance);

		template <typename FunType>
		FunType getProcAddr(const char *name) const
		{
			auto res = vkGetInstanceProcAddr(m_handle, name);

			if (res == nullptr)
				throw std::runtime_error(std::string("Can't get proc '") + std::string(name) + std::string("'"));
			return reinterpret_cast<FunType>(res);
		}

		template <typename VkHandle>
		using Handle = HandleDep<Instance, VkHandle>;

		PhysicalDevices enumerateDevices(Vk::Surface &surface);

		template <typename T, typename C>
		auto createVk(VkResult (*fun)(VkInstance, const C *createInfo, const VkAllocationCallbacks *pAllocator, T *res), const C &createInfo)
		{
			T res;

			Vk::assert(fun(*this, &createInfo, m_vk.getAllocator(), &res));
			return res;
		}

		template <typename T, typename C, typename Val>
		// Val is convertible to C
		auto createVk(VkResult (*fun)(VkInstance, C *createInfo, const VkAllocationCallbacks *pAllocator, T *res), const Val &val)
		{
			T res;

			Vk::assert(fun(*this, val, m_vk.getAllocator(), &res));
			return res;
		}

		template <typename T, typename Fun, typename C>
		auto create(Fun &&fun, const C &createInfo)
		{
			return T(*this, createVk(std::forward<Fun>(fun), createInfo));
		}

		template <typename T>
		void destroy(void (*fun)(VkInstance, T obj, const VkAllocationCallbacks *pAllocator), T obj)
		{
			fun(*this, obj, m_vk.getAllocator());
		}

	private:
		Vk &m_vk;
	};

	Instance m_instance;
	Instance createInstance(void);

	class DebugMessenger : public Instance::Handle<VkDebugUtilsMessengerEXT>
	{
	public:
		DebugMessenger(Instance &instance, VkDebugUtilsMessengerEXT messenger);
	};

	std::optional<DebugMessenger> m_debug_messenger;
	std::optional<DebugMessenger> createDebugMessenger(void);

	class Surface : public Instance::Handle<VkSurfaceKHR>
	{
	public:
		Surface(Instance &instance, VkSurfaceKHR surface);
	};

	Surface m_surface;
	Surface createSurface(void);

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

		struct Properties : public VkPhysicalDeviceProperties
		{
			Properties(const VkPhysicalDeviceProperties &props);

			size_t getAlignmentFor(sb::Shader::DescriptorType type) const;
		};

		const Properties& properties(void) const;
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
		const Properties m_props;
		const VkPhysicalDeviceFeatures m_features;
		const QueueFamilies m_queue_families;
		Surface m_phys_surface;

		bool areExtensionsSupported(void) const;
	};

	class PhysicalDevices
	{
	public:
		PhysicalDevices(Vk::Instance &instance, Vk::Surface &surface);

		const PhysicalDevice& getBest(void) const;

	private:
		std::vector<PhysicalDevice> m_devices;

		std::vector<Vk::PhysicalDevice> enumerate(Vk::Instance &instance, Vk::Surface &surface);
	};

	class VmaBuffer;

	class Allocator : public Vk::Handle<VmaAllocator>
	{
	public:
		Allocator(Device &device);

		template <typename VkHandle>
		using Handle = HandleDep<Allocator, VkHandle>;

		VmaBuffer createBuffer(const VkBufferCreateInfo &bufferCreateInfo, const VmaAllocationCreateInfo &allocationCreateInfo);

	private:
		Device &m_device;

		VmaAllocator create(Device &device);
	};

	class ImageView;
	class RenderPass;

	class Device : public Handle<VkDevice>
	{
		friend Handle<VkDevice>;

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

		Device(Instance &instance, const PhysicalDevice &physicalDevice, VkDevice device);

		Vk& vk(void);
		const PhysicalDevice& physical(void) const;
		Allocator& allocator(void);
		VkQueue getQueue(uint32_t family_ndx, uint32_t ndx);

		template <typename VkHandle>
		using Handle = HandleDep<Device, VkHandle>;

		template <typename T, typename C>
		auto createVk(VkResult (*fun)(VkDevice, const C *createInfo, const VkAllocationCallbacks *pAllocator, T *res), const C &createInfo)
		{
			T res;

			Vk::assert(fun(*this, &createInfo, m_instance.m_vk.getAllocator(), &res));
			return res;
		}

		template <typename T, typename C, typename VkHandle1>
		auto createVk(VkResult (*fun)(VkDevice, VkHandle1, uint32_t createInfoCount, const C *createInfos, const VkAllocationCallbacks *pAllocator, T *res), const C &createInfo)
		{
			T res;

			Vk::assert(fun(*this, VK_NULL_HANDLE, 1, &createInfo, m_instance.m_vk.getAllocator(), &res));
			return res;
		}

		template <typename T, typename Fun, typename C>
		auto create(Fun &&fun, const C &createInfo)
		{
			return T(*this, createVk(std::forward<Fun>(fun), createInfo));
		}

		template <typename T, typename C>
		auto allocateVk(VkResult (*fun)(VkDevice, const C *allocInfo, T *res), const C &createInfo)
		{
			T res;

			Vk::assert(fun(*this, &createInfo, &res));
			return res;
		}

		template <typename T, typename C>
		void allocateVks(VkResult (*fun)(VkDevice, const C *allocInfo, T *res), const C &createInfo, T *dst)
		{
			Vk::assert(fun(*this, &createInfo, dst));
		}

		template <typename T>
		void destroy(void (*fun)(VkDevice, T obj, const VkAllocationCallbacks *pAllocator), T obj)
		{
			fun(*this, obj, m_instance.m_vk.getAllocator());
		}

	private:
		Instance &m_instance;
		PhysicalDevice m_physical;
		Allocator m_allocator;

		VkDevice createDevice(const PhysicalDevice &physicalDevice, const QueuesCreateInfo &queues);
	};

	class Allocation : public Allocator::Handle<VmaAllocation>
	{
	public:
		Allocation(Allocator &allocator, VmaAllocation alloc);

		void* map(void);
		void unmap(void);
	};

	class Buffer : public Device::Handle<VkBuffer>
	{
	public:
		Buffer(Device &dev, VkBuffer buffer);
	};

	class VmaBuffer : public Allocation, public Buffer
	{
	public:
		VmaBuffer(Device &dev, VkBuffer buffer, VmaAllocation allocation);
	};

	Device m_device;
	Device createDevice(void);
	Device::QueuesCreateInfo getDesiredQueues(const PhysicalDevice &dev);

	VkQueue m_graphics_queue;
	VkQueue m_present_queue;

	class ImageView : public Device::Handle<VkImageView>
	{
	public:
		ImageView(Device &device, VkImageView imageView);
	};

	class Swapchain : public Device::Handle<VkSwapchainKHR>
	{
	public:
		Swapchain(Vk::Device &device, VkSwapchainKHR swapchain);

	private:
		std::vector<VkImage> m_images;
		std::vector<ImageView> m_views;

		std::vector<ImageView> createViews(Device &dev);
	};

	const VkSurfaceFormatKHR &m_swapchain_format;
	Swapchain m_swapchain;
	Swapchain createSwapchain(void);

	class RenderPass : public Device::Handle<VkRenderPass>
	{
	public:
		RenderPass(Device &dev, VkRenderPass renderPass);
	};

	RenderPass m_default_render_pass;
	RenderPass createDefaultRenderPass(void);
	RenderPass& getDefaultRenderPass(void);

	static VkDescriptorType descriptorType(sb::Shader::DescriptorType type);

	class DescriptorSetLayout : public sb::Shader::DescriptorSet::Layout, public Device::Handle<VkDescriptorSetLayout>
	{
	public:
		DescriptorSetLayout(Device &device, const sb::Shader::DescriptorSet::Layout::Description &layout);
		~DescriptorSetLayout(void);

		const sb::Shader::DescriptorSet::Layout::Description& getDescription(void) const;

	private:
		const sb::Shader::DescriptorSet::Layout::Description m_desc;

		VkDescriptorSetLayout create(Device &device, const sb::Shader::DescriptorSet::Layout::Description &layout);
		VkDescriptorSetLayoutBinding bindingtoVk(const sb::Shader::DescriptorSet::Layout::DescriptionBinding &binding);
	};

	std::unique_ptr<sb::Shader::DescriptorSet::Layout> createDescriptorSetLayout(const sb::Shader::DescriptorSet::Layout::Description &desc) override;

	class DescriptorSet : public sb::Shader::DescriptorSet, private Device::Handle<VkDescriptorPool>
	{
	public:
		DescriptorSet(Device &dev, const DescriptorSetLayout &layout);

		void write(size_t offset, size_t range, const void *data) override;

	private:
		VkDescriptorSet m_descriptor_set;
		VmaBuffer m_buffer;

		VkDescriptorPool createPool(Device &dev, const DescriptorSetLayout &layout);
		VkDescriptorSet create(const DescriptorSetLayout &layout);
		VmaBuffer createBuffer(const DescriptorSetLayout &layout);
	};

	class Model : public sb::Shader::Model
	{
	public:
		Model(Device &dev, size_t count, size_t stride, const void *data);

	private:
		size_t m_count;
		VmaBuffer m_buffer;

		VmaBuffer createBuffer(Device &dev, size_t size);
	};

	using PipelineLayout = Device::Handle<VkPipelineLayout>;
	using ShaderModule = Device::Handle<VkShaderModule>;
	using Pipeline = Device::Handle<VkPipeline>;

	class Shader : public sb::Shader
	{
	public:
		static VkShaderStageFlagBits sbStageToVk(Subtile::Shader::Stage stage);
		static VkFormat vertexInputFormatToVk(sb::Shader::VertexInput::Format);

		Shader(Device &device, rs::Shader &shader);

		//std::unique_ptr<sb::Shader::DescriptorSet> material(void) override;
		//std::unique_ptr<sb::Shader::DescriptorSet> object(void) override;
		std::unique_ptr<sb::Shader::Model> model(size_t count, size_t stride, const void *data) override;
		std::unique_ptr<sb::Shader::DescriptorSet> set(size_t ndx) override;

	private:
		Device &m_device;
		rs::Shader::DescriptorSetLayouts m_layouts;
		PipelineLayout m_pipeline_layout;
		PipelineLayout createPipelineLayout(void);
		std::vector<std::pair<VkShaderStageFlagBits, ShaderModule>> m_shader_modules;
		std::vector<std::pair<VkShaderStageFlagBits, ShaderModule>> createShaderModules(Vk::Device &device, rs::Shader &shader);
		Pipeline m_pipeline;
		Pipeline createPipeline(Vk::Device &device, rs::Shader &shader);
	};

	std::unique_ptr<sb::Shader> loadShader(rs::Shader &shader) override;
};

}
}