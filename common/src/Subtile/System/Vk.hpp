#pragma once

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>
#include "../System.hpp"
#include "Glfw.hpp"
#include "Subtile/Shader.hpp"
#include "Subtile/RenderList.hpp"
#include "Subtile/Model.hpp"

#undef assert

namespace Subtile {

class Vk : public System
{
public:
	Vk(bool validate, bool isRenderDoc, bool isMonitor);
	~Vk(void) override;

	void scanInputs(void) override;

	const VkAllocationCallbacks* getAllocator(void) const;

private:
	Glfw m_glfw;
	bool m_is_debug;

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

		Handle(const Handle&) = delete;

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

		HandleDep(const HandleDep&) = delete;

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

		DepType& getDep(void) const
		{
			return m_dep;
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
public:
	class Surface;

private:
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

		PhysicalDevices enumerateDevices(void);

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
	Instance createInstance(bool isRenderDoc, bool isMonitor);

	class DebugMessenger : public Instance::Handle<VkDebugUtilsMessengerEXT>
	{
	public:
		DebugMessenger(Instance &instance, VkDebugUtilsMessengerEXT messenger);
	};

	std::optional<DebugMessenger> m_debug_messenger;
	std::optional<DebugMessenger> createDebugMessenger(void);

	class Swapchain;

public:
	class Surface : public sb::Surface
	{
	public:
		Surface(Instance &instance, const svec2 &extent, const std::string &title);
		~Surface(void) override;

		svec2 getExtent(void) const override;
		std::optional<svec2> isResized(void) const override;
		bool shouldClose(void) const override;

		const std::vector<Input*>& getInputs(void) const override;
		const std::map<std::string, Input*>& getInputsId(void) const override;
		const std::vector<Button*>& getButtons(void) const override;
		const std::map<std::string, Button*>& getButtonsId(void) const override;
		const std::vector<Analog*>& getAnalogs(void) const override;
		const std::map<std::string, Analog*>& getAnalogsId(void) const override;

		glm::dvec2 cursor(void) const override;
		void cursorMode(bool show) override;

		operator VkSurfaceKHR(void) const
		{
			return m_surface;
		}

		void resized(const svec2 &size)
		{
			m_is_resized = size;
		}
		void resetResized(void)
		{
			m_is_resized.reset();
		}

	private:
		Glfw::Window m_window;
		Instance::Handle<VkSurfaceKHR> m_surface;
		svec2 m_extent;
		std::optional<svec2> m_is_resized;

		std::vector<std::unique_ptr<Button>> m_unique_buttons;
		std::vector<std::unique_ptr<Button>> createUniqueButtons(void);
		class GlfwButton : public Button
		{
		public:
			GlfwButton(const std::string &id, GLFWwindow *window, int key_id);
			~GlfwButton(void) override;

			void update(void) override;
			const std::string& id(void) const override;
			bool active(void) const override;
			bool state(void) const override;
			bool pressed(void) const override;
			bool released(void) const override;

		private:
			std::string m_id;
			GLFWwindow *m_window;
			int m_key_id;
			bool m_last_state = false;
			bool m_state = false;
		};

		std::vector<Button*> m_buttons;
		decltype(m_buttons) getButtons(void)
		{
			decltype(m_buttons) res;

			for (auto &b : m_unique_buttons)
				res.emplace_back(&*b);
			return res;
		}
		std::map<std::string, Button*> m_buttons_id;
		decltype(m_buttons_id) getButtonsId(void)
		{
			decltype(m_buttons_id) res;

			for (auto &b : m_unique_buttons)
				res.emplace(b->id(), &*b);
			return res;
		}

		std::vector<Analog*> m_analogs;
		std::map<std::string, Analog*> m_analogs_id;

		std::vector<Input*> m_inputs;
		decltype(m_inputs) getInputs(void)
		{
			decltype(m_inputs) res;

			for (auto &b : m_buttons)
				res.emplace_back(b);
			for (auto &a : m_analogs)
				res.emplace_back(a);
			return res;
		}
		std::map<std::string, Input*> m_inputs_id;
		decltype(m_inputs_id) getInputsId(void)
		{
			decltype(m_inputs_id) res;

			for (auto &bp : m_buttons_id)
				res.emplace(bp.first, bp.second);
			for (auto &ap : m_analogs_id)
				res.emplace(ap.first, ap.second);
			return res;
		}
	};

	std::unique_ptr<sb::Surface> createSurface(const svec2 &extent, const std::string &title) override;

private:
	class PhysicalDevice
	{
	public:
		PhysicalDevice(VkPhysicalDevice device);

		class Surface
		{
		public:
			Surface(const PhysicalDevice &device, Vk::Surface &surface);

			const VkSurfaceCapabilitiesKHR& capabilities(void) const;
			const std::vector<VkSurfaceFormatKHR>& formats(void) const;
			const std::vector<VkPresentModeKHR>& presentModes(void) const;

			const VkSurfaceFormatKHR& chooseFormat(void) const;
			VkPresentModeKHR choosePresentMode(void) const;
			VkExtent2D chooseExtent(VkExtent2D baseExtent) const;

			bool getSurfaceSupport(uint32_t queueFamilyIndex) const;

			operator VkSurfaceKHR(void) const;

		private:
			const VkSurfaceCapabilitiesKHR m_capabilities;
			const std::vector<VkSurfaceFormatKHR> m_formats;
			const std::vector<VkPresentModeKHR> m_present_modes;
			const PhysicalDevice &m_device;
			Vk::Surface &m_vk_surface;
		};

		operator VkPhysicalDevice(void) const;

		struct Properties : public VkPhysicalDeviceProperties
		{
			Properties(const VkPhysicalDeviceProperties &props);

			size_t getAlignment(sb::Shader::DescriptorType type) const;
		};

		static const VkPhysicalDeviceFeatures& requiredFeatures(void);

		const Properties& properties(void) const;
		const VkPhysicalDeviceFeatures& features(void) const;

		bool isCompetent(const sb::Queue::Set &requiredQueues, Vk::Surface &surface) const;
		size_t getScore(void) const;

		static const util::svec required_extensions;

		class QueueFamilies
		{
		public:
			QueueFamilies(PhysicalDevice &device);

			const std::vector<VkQueueFamilyProperties>& properties(void) const;
			std::optional<uint32_t> indexOf(Vk::PhysicalDevice::Surface &surface, sb::Queue::Flag flags, size_t count = 1) const;

		private:
			std::vector<VkQueueFamilyProperties> m_queues;
		};

		const QueueFamilies& queues(void) const;

	private:
		VkPhysicalDevice m_device;
		const Properties m_props;
		const VkPhysicalDeviceFeatures m_features;
		const QueueFamilies m_queue_families;

		bool areExtensionsSupported(void) const;
	};

	class PhysicalDevices
	{
	public:
		PhysicalDevices(Vk::Instance &instance);

		const PhysicalDevice& getBest(const sb::Queue::Set &requiredQueues, Vk::Surface &surface) const;

	private:
		std::vector<PhysicalDevice> m_devices;

		std::vector<Vk::PhysicalDevice> enumerate(Vk::Instance &instance);
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

	using VkQueueFamilyIndex = uint32_t;
	using sbQueueFamilyMapping = std::map<sb::Queue::Flag, VkQueueFamilyIndex>;
	using sbQueueIndex = size_t;
	using VkQueueIndex = uint32_t;
	using sbQueueMapping = std::map<std::pair<sb::Queue::Flag, sbQueueIndex>, std::pair<VkQueueFamilyIndex, VkQueueIndex>>;

	class Device : public sb::Device, public Handle<VkDevice>
	{
	public:
		Device(Instance &instance, const PhysicalDevice &physicalDevice, const sbQueueFamilyMapping& queueFamilyMapping, const sbQueueMapping &queueMapping, VkDevice device);
		~Device(void) override;

		Vk& vk(void)
		{
			return m_instance.m_vk;
		}

		const PhysicalDevice& physical(void) const;
		Allocator& allocator(void);
		VkFormat sbFormatToVk(sb::Format format) const;

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

		void newSurface(sb::Surface &surface) override;

		std::unique_ptr<sb::Queue> getQueue(Queue::Flag flags, size_t index) override;
		std::unique_ptr<sb::Swapchain> createSwapchain(sb::Surface &surface, const svec2 &extent, size_t desiredImageCount, sb::Image::Usage usage, sb::Queue &queue) override;
		std::unique_ptr<sb::Image> createImage(sb::Image::Type type, Format format, sb::Image::Sample sample, const svec3 &extent, size_t layers, const sb::Image::MipmapLevels &mipLevels, sb::Image::Usage usage, sb::Queue &queue) override;
		std::unique_ptr<sb::Semaphore> createSemaphore(void) override;
		std::unique_ptr<sb::Fence> createFence(bool isSignaled) override;
		std::unique_ptr<sb::Buffer> createBuffer(size_t size, sb::Buffer::Location location, sb::Buffer::Usage usage, sb::Queue &queue) override;
		std::unique_ptr<sb::Model> createModel(sb::Buffer &vertexBuffer, size_t vertexCount) override;
		std::unique_ptr<sb::Model> createModelIndexed(sb::Buffer &vertexBuffer, sb::Buffer &indexBuffer, sb::Model::IndexType indexType, size_t indexCount) override;
		std::unique_ptr<sb::Sampler> createSampler(Filter magFilter, Filter minFilter, bool normalizedCoordinates, const sb::Sampler::AddressModeUVW &addressMode, BorderColor borderColor, const std::optional<CompareOp> &compare, sb::Sampler::MipmapMode mipmapMode, float minLod, float maxLod, float mipLodBias, const std::optional<float> &anisotropy) override;

		std::unique_ptr<sb::RenderPass> createRenderPass(sb::rs::RenderPass &renderpass) override;
		std::unique_ptr<sb::Shader> createShader(rs::Shader &shader) override;
		std::unique_ptr<sb::Shader::DescriptorSet::Layout> createDescriptorSetLayout(const sb::Shader::DescriptorSet::Layout::Description &desc) override;

		Instance &m_instance;
		PhysicalDevice m_physical;
		sbQueueFamilyMapping m_queue_family_mapping;
		sbQueueMapping m_queue_mapping;
		Allocator m_allocator;
		std::map<sb::Format, VkFormat> m_dynamic_formats;

		std::map<sb::Format, VkFormat> getDynamicFormats(void);
		bool isDepthFormatSupportedSplAtt(VkFormat format);
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

	class VmaBuffer : public sb::Buffer, public Allocation, public Vk::Buffer
	{
	public:
		VmaBuffer(Device &dev, VkBuffer buffer, VmaAllocation allocation);
		~VmaBuffer(void) override;

		VmaBuffer(VmaBuffer&&) = default;

		void write(size_t off, size_t size, const void *data) override;
	};

	std::unique_ptr<sb::Device> createDevice(sb::Surface &surface, const sb::Queue::Set &queues) override;

	class Image : private Allocation, public Device::Handle<VkImage>
	{
	public:
		Image(Device &dev, VkImage image, VmaAllocation allocation);

		static sb::Image::Aspect sbFormatToImageAspectFlags(sb::Format format);
		static VkImageType sbImageTypeToVk(sb::Image::Type type);
	};

	class ImageView : public sb::Image, public Device::Handle<VkImageView>
	{
	public:
		ImageView(Device &dev, VkImage image, VkFormat imageFormat, sb::Image::Type type, const svec3 &extent, const ComponentMapping &components, Aspect aspect, const Range &arrayRange, const Range &mipRange);
		~ImageView(void) override;

		ImageView(ImageView&&) = default;

		std::unique_ptr<sb::Image> createView(sb::Image::Type type, const ComponentMapping &components, Aspect aspect, const Range &arrayRange, const Range &mipRange) const override;
		size_t getArrayLayers(void) const override;
		size_t getMipLevels(void) const override;
		const svec3& getExtent(void) const override;

		auto& getImage(void) const { return m_image; }
		auto& getAspect(void) const { return m_aspect; }
		auto& getArrayRange(void) const { return m_array_range; }
		auto& getMipRange(void) const { return m_mip_range; }

	private:
		VkImage m_image;
		VkFormat m_image_format;
		svec3 m_extent;
		ComponentMapping m_components;
		Aspect m_aspect;
		Range m_array_range;
		Range m_mip_range;

		VkImageView create(Device &dev, VkImage image, VkFormat imageFormat, sb::Image::Type type, const ComponentMapping &components, Aspect aspect, const Range &arrayRange, const Range &mipRange);

		svec3 deriveExtent(size_t mipmapOff) const;
		ComponentMapping deriveComponents(const ComponentMapping &newMapping) const;
		ComponentSwizzle deriveComponent(ComponentSwizzle ComponentMapping::* baseLoc, const ComponentMapping &newMapping) const;
		Aspect deriveAspect(Aspect newAspect) const;
		static Range deriveRange(const Range &baseRange, const Range &newRange);
	};

	class ImageAllocView : public Vk::Image, public ImageView
	{
	public:
		ImageAllocView(Vk::Image &&image, ImageView &&view);
		~ImageAllocView(void) override;
	};

	static inline VkImageLayout sbImageLayoutToVk(sb::Image::Layout layout)
	{
		return static_cast<VkImageLayout>(static_cast<std::underlying_type_t<sb::Image::Layout>>(layout));
	}

	static VkDescriptorType descriptorType(sb::Shader::DescriptorType type);

	class DescriptorSetLayout : public sb::Shader::DescriptorSet::Layout, public Device::Handle<VkDescriptorSetLayout>
	{
	public:
		DescriptorSetLayout(Device &device, const sb::Shader::DescriptorSet::Layout::Description &layout);
		~DescriptorSetLayout(void) override;
		DescriptorSetLayout(DescriptorSetLayout&&) = default;

		const sb::Shader::DescriptorSet::Layout::Description& getDescription(void) const { return m_desc; }
		auto getBufferSize(void) const { return m_buffer_size; }
		auto getUniformOff(void) const { return m_uniform_off; }
		auto getUniformSize(void) const { return m_uniform_size; }
		auto getStorageOff(void) const { return m_storage_off; }
		auto getStorageSize(void) const { return m_storage_size; }

	private:
		const sb::Shader::DescriptorSet::Layout::Description m_desc;
		size_t m_buffer_size = 0;
		size_t m_uniform_off = 0;
		size_t m_uniform_size = 0;
		size_t m_storage_off = 0;
		size_t m_storage_size = 0;

		VkDescriptorSetLayout create(Device &device, const sb::Shader::DescriptorSet::Layout::Description &layout);
		VkDescriptorSetLayoutBinding bindingtoVk(const sb::Shader::DescriptorSet::Layout::DescriptionBinding &binding);
	};

	class DescriptorSet : public sb::Shader::DescriptorSet
	{
	public:
		DescriptorSet(Device &dev, const DescriptorSetLayout &layout, sb::Queue *queue);	// ptr for queue buffer attribution

		sb::Buffer::Region uniformBufferRegion(void) override;
		sb::Buffer::Region storageBufferRegion(void) override;
		void bindSampler(size_t binding, size_t index, sb::Sampler &sampler) override;
		void bindImage(size_t binding, size_t index, sb::Image &image, sb::Image::Layout layout) override;
		void bindCombinedImageSampler(size_t binding, size_t index, sb::Sampler &sampler, sb::Image &image, sb::Image::Layout layout) override;

		operator VkDescriptorSet(void) const;

	private:
		const DescriptorSetLayout &m_layout;
		Device::Handle<VkDescriptorPool> m_descriptor_pool;
		VkDescriptorSet m_descriptor_set;
		VmaBuffer m_buffer;

		VkDescriptorPool createPool(Device &dev, const DescriptorSetLayout &layout);
		VkDescriptorSet create(Device &dev, const DescriptorSetLayout &layout);
		VmaBuffer createBuffer(Device &dev, sb::Queue *queue);
	};

	class RenderPass;

	class Framebuffer : public sb::Framebuffer, public Device::Handle<VkFramebuffer>
	{
	public:
		Framebuffer(Device &dev, VkFramebuffer framebuffer, RenderPass &render_pass, std::vector<DescriptorSet> &&input_attachments);
		~Framebuffer(void) override;

		RenderPass& getRenderPass(void)
		{
			return m_render_pass;
		}

		std::vector<DescriptorSet>& getInputAttachments(void)
		{
			return m_input_attachments;
		}

	private:
		RenderPass &m_render_pass;
		std::vector<DescriptorSet> m_input_attachments;
	};

	using PipelineLayout = Device::Handle<VkPipelineLayout>;

	class RenderPass : public sb::RenderPass
	{
		static VkAttachmentLoadOp sbLoadOpToVk(sb::Image::LoadOp loadOp);
		static VkAttachmentStoreOp sbStoreOpToVk(sb::Image::StoreOp storeOp);

		static inline VkAttachmentReference sbAttachmentReferenceToVk(const sb::RenderPass::Layout::AttachmentReference &ref)
		{
			return {static_cast<uint32_t>(ref.ndx), sbImageLayoutToVk(ref.layout)};
		}

		static inline VkPipelineStageFlags sbPipelineStageToVk(sb::PipelineStage stage)
		{
			return static_cast<VkPipelineStageFlags>(static_cast<std::underlying_type_t<sb::PipelineStage>>(stage));
		}

		static inline VkAccessFlags sbAccessToVk(sb::Access access)
		{
			return static_cast<VkAccessFlags>(static_cast<std::underlying_type_t<sb::Access>>(access));
		}

		static inline VkDependencyFlags sbDependencyFlagToVk(sb::DependencyFlag flag)
		{
			return static_cast<VkDependencyFlags>(static_cast<std::underlying_type_t<sb::DependencyFlag>>(flag));
		}

	public:
		RenderPass(Device &dev, sb::rs::RenderPass &res);
		~RenderPass(void) override;

		std::unique_ptr<sb::Framebuffer> createFramebuffer(const svec2 &extent, size_t layers, size_t count, sb::Image **images) override;

		operator VkRenderPass(void) const
		{
			return m_handle;
		}

		auto& getLayout(void) const
		{
			return m_layout;
		}

		auto& getSubpassesDescriptorSetLayouts(void) const
		{
			return m_subpasses_descriptor_set_layouts;
		}

		auto& getSubpassesPipelineLayouts(void) const
		{
			return m_subpasses_pipeline_layouts;
		}

	private:
		sb::RenderPass::Layout m_layout;
		Device::Handle<VkRenderPass> m_handle;
		std::vector<DescriptorSetLayout> m_subpasses_descriptor_set_layouts;
		std::vector<PipelineLayout> m_subpasses_pipeline_layouts;

		VkRenderPass create(Device &dev);
		std::vector<DescriptorSetLayout> createSubpassesDescriptorSetLayouts(void);
		std::vector<PipelineLayout> createSubpassesPipelineLayouts(void);
	};

	class Swapchain : public sb::Swapchain, public Device::Handle<VkSwapchainKHR>
	{
	public:
		Swapchain(Vk::Device &device, VkSwapchainKHR swapchain, VkSurfaceFormatKHR surfaceFormat, const svec2 &extent);
		~Swapchain(void) override;

		std::vector<sb::Swapchain::Image2D>& getImages(void) override;
		size_t acquireNextImage(sb::Semaphore &semaphore) override;
		svec2 getExtent(void) const override;

	private:
		VkSurfaceFormatKHR m_surface_format;
		svec2 m_extent;
		std::vector<sb::Swapchain::Image2D> m_images;

		std::vector<sb::Swapchain::Image2D> queryImages(void);
	};

	class Semaphore : public sb::Semaphore, public Device::Handle<VkSemaphore>
	{
	public:
		Semaphore(Device &dev, VkSemaphore semaphore);
		~Semaphore(void) override;
	};

	class Fence : public sb::Fence, public Device::Handle<VkFence>
	{
	public:
		Fence(Device &dev, VkFence fence);
		~Fence(void) override;

		void wait(void) override;
		void reset(void) override;
	};

	using ShaderModule = Device::Handle<VkShaderModule>;
	using Pipeline = Device::Handle<VkPipeline>;

	class Shader : public sb::Shader
	{
	public:
		static VkShaderStageFlagBits sbStageToVk(Subtile::Shader::Stage stage);
		static VkFormat vertexInputFormatToVk(sb::Shader::VertexInput::Format);

		Shader(Device &device, rs::Shader &shader);

		const sb::Shader::DescriptorSet::Layout& setLayout(size_t ndx) override;
		std::unique_ptr<sb::Shader::DescriptorSet> set(size_t ndx, sb::Queue &queue) override;

		PipelineLayout& getPipelineLayout(void);
		Pipeline& getPipeline(void);

		auto getDescriptorSetOffset(void) const
		{
			return m_descriptor_set_offset;
		}

	private:
		Device &m_device;

		std::optional<std::pair<sb::RenderPass::Cache::Ref, size_t>> m_render_pass;
		std::optional<std::pair<sb::RenderPass::Cache::Ref, size_t>> loadRenderPass(rs::Shader &shader);
		size_t m_descriptor_set_offset;

		rs::Shader::DescriptorSetLayouts m_layouts;
		PipelineLayout m_pipeline_layout;
		PipelineLayout createPipelineLayout(void);
		using ShaderModulesType = std::vector<std::pair<VkShaderStageFlagBits, ShaderModule>>;
		ShaderModulesType m_shader_modules;
		ShaderModulesType createShaderModules(Vk::Device &device, rs::Shader &shader);

		std::optional<Pipeline> m_pipeline;
		std::optional<Pipeline> createPipeline(Vk::Device &device, rs::Shader &shader);
	};

	class CommandPool;

	class CommandBuffer : public sb::CommandBuffer
	{
	public:
		CommandBuffer(CommandPool &pool, sb::CommandBuffer::Level level);
		~CommandBuffer(void) override;

		operator VkCommandBuffer(void) const
		{
			return m_handle;
		}

		void reset(bool releaseResources) override;
		void begin(Usage flags) override;
		void beginRender(Usage flags, sb::Framebuffer &fb, size_t subpass) override;
		void beginRender(Usage flags, sb::RenderPass &rp, size_t subpass) override;
		void end(void) override;

		void executeCommands(size_t count, sb::CommandBuffer **cmds) override;
		void bindPipeline(sb::Shader &shader) override;
		void bindDescriptorSets(sb::Shader &shader, size_t first_set, size_t count, sb::Shader::DescriptorSet **sets) override;

		void beginRenderPass(bool isInline, sb::Framebuffer &fb, const srect2 &renderArea, size_t clearValueCount, ClearValue *clearValues) override;
		void nextSubpass(bool isInline) override;
		void endRenderPass(void) override;

		void copy(const sb::Buffer::Region &src, const sb::Buffer::Region &dst) override;

		void memoryBarrier(PipelineStage srcStageMask, PipelineStage dstStageMask, DependencyFlag flags, Access srcAccessMask, Access dstAccessMask) override;
		void imageMemoryBarrier(PipelineStage srcStageMask, PipelineStage dstStageMask, DependencyFlag flags, Access srcAccessMask, Access dstAccessMask, sb::Image::Layout oldLayout, sb::Image::Layout newLayout, sb::Image &image) override;

		void setViewport(const rect2 &area, float minDepth, float maxDepth) override;
		void setScissor(const srect2 &scissor) override;

		void blit(sb::Image &srcImage, sb::Image::Layout srcLayout, const srect3 &srcRegion, sb::Image &dstImage, sb::Image::Layout dstLayout, const srect3 &dstRegion, Filter filter) override;
		void copyBufferToImage(const sb::Buffer::Region &srcBuffer, sb::Image &dstImage, sb::Image::Layout dstImageLayout, const srect3 &dstRegion) override;

	private:
		CommandPool &m_pool;
		VkCommandBuffer m_handle;
		size_t m_render_pass_subpass_ndx = 0;
		Framebuffer *m_render_pass_fb;

		VkCommandBuffer createCommandBuffer(sb::CommandBuffer::Level level);
	};

	class CommandPool : public sb::CommandPool, public Device::Handle<VkCommandPool>
	{
	public:
		CommandPool(Device &dev, VkQueueFamilyIndex familyIndex, bool isReset);
		~CommandPool(void) override;

		std::unique_ptr<sb::CommandBuffer> commandBuffer(sb::CommandBuffer::Level level) override;

	private:
		VkCommandPool create(Device &dev, VkQueueFamilyIndex familyIndex, bool isReset);
	};

	class Queue : public sb::Queue
	{
	public:
		Queue(Device &dev, VkQueueFamilyIndex familyIndex, VkQueue queue);
		~Queue(void) override;

		std::unique_ptr<sb::CommandPool> commandPool(bool isReset) override;
		void submit(size_t submitCount, SubmitInfo *submits, sb::Fence *fence) override;
		void present(size_t waitSemaphoreCount, sb::Semaphore **waitSemaphores, sb::Swapchain::Image2D &image) override;
		void waitIdle(void) override;

		operator VkQueue(void) const
		{
			return m_handle;
		}

		auto getFamilyIndex(void) const
		{
			return m_family_index;
		}

	private:
		Device &m_device;
		VkQueueFamilyIndex m_family_index;
		VkQueue m_handle;
	};

	class Model : public sb::Model
	{
	public:
		Model(VmaBuffer &buffer, size_t vertexCount);
		~Model(void) override;

		void draw(sb::CommandBuffer &cmd) override;

	private:
		VmaBuffer &m_buffer;
		size_t m_vertex_count;
	};

	class ModelIndexed : public sb::Model
	{
	public:
		ModelIndexed(VmaBuffer &buffer, VmaBuffer &indexBuffer, VkIndexType indexType, size_t indexCount);
		~ModelIndexed(void) override;

		void draw(sb::CommandBuffer &cmd) override;

	private:
		VmaBuffer &m_buffer;
		VmaBuffer &m_index_buffer;
		VkIndexType m_index_type;
		size_t m_index_count;
	};

	class Sampler : public sb::Sampler, public Device::Handle<VkSampler>
	{
	public:
		Sampler(Device &dev, VkSampler sampler);
		~Sampler(void) override;
	};
};

}