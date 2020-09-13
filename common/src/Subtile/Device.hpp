#pragma once

#include "Queue.hpp"
#include "Swapchain.hpp"
#include "Surface.hpp"
#include "Image.hpp"
#include "Semaphore.hpp"
#include "Fence.hpp"
#include "Buffer.hpp"
#include "Model.hpp"
#include "Sampler.hpp"
#include "Resource/Shader.hpp"
#include "Resource/RenderPass.hpp"
#include <memory>

namespace Subtile {

class Device
{
	Shader::Cache m_shaders;
	RenderPass::Cache m_render_passes;

public:
	Device(void) = default;
	virtual ~Device(void) = default;

	virtual std::unique_ptr<Queue> getQueue(Queue::Flag flags, size_t index) = 0;
	virtual std::unique_ptr<sb::Swapchain> createSwapchain(Surface &surface, const svec2 &extent, size_t desiredImageCount, sb::Image::Usage usage, sb::Queue &queue) = 0;
	virtual std::unique_ptr<Image> createImage(Image::Type type, Format format, Image::Sample sample, const svec3 &extent, size_t layers, const sb::Image::MipmapLevels &mipLevels, Image::Usage usage, Queue &queue) = 0;
	virtual std::unique_ptr<Semaphore> createSemaphore(void) = 0;
	virtual std::unique_ptr<Fence> createFence(bool isSignaled) = 0;
	virtual std::unique_ptr<Buffer> createBuffer(size_t size, Buffer::Location location, Buffer::Usage usage, Queue &queue) = 0;
	virtual std::unique_ptr<Model> createModel(Buffer &vertexBuffer, size_t vertexCount) = 0;
	virtual std::unique_ptr<Model> createModelIndexed(Buffer &vertexBuffer, Buffer &indexBuffer, Model::IndexType indexType, size_t indexCount) = 0;
	virtual std::unique_ptr<Sampler> createSampler(Filter magFilter, Filter minFilter, bool normalizedCoordinates, const Sampler::AddressModeUVW &addressMode, BorderColor borderColor, const std::optional<CompareOp> &compare, Sampler::MipmapMode mipmapMode, float minLod, float maxLod, float mipLodBias, const std::optional<float> &anisotropy) = 0;

	virtual std::unique_ptr<RenderPass> createRenderPass(rs::RenderPass &renderpass) = 0;
	virtual std::unique_ptr<Shader> createShader(rs::Shader &shader) = 0;
	virtual std::unique_ptr<Shader::DescriptorSet::Layout> createDescriptorSetLayout(const Shader::DescriptorSet::Layout::Description &desc) = 0;

	Shader::Cache::Ref loadShaderRef(rs::Shader &shaderres)
	{
		auto got = m_shaders.find(shaderres);
		if (got == m_shaders.end())
			return m_shaders.emplace(shaderres, createShader(shaderres));
		else
			return got->second.new_ref();
	}

	RenderPass::Cache::Ref loadRenderPassRef(rs::RenderPass &renderpassres)
	{
		auto got = m_render_passes.find(renderpassres);
		if (got == m_render_passes.end())
			return m_render_passes.emplace(renderpassres, createRenderPass(renderpassres));
		else
			return got->second.new_ref();
	}

	template <typename S>
	decltype(auto) loadShader(S &&shaderres)
	{
		return Shader::Loaded<std::remove_cv_t<std::remove_reference_t<S>>>(loadShaderRef(std::forward<S>(shaderres)));
	}
	template <typename R>
	decltype(auto) loadRenderPass(R &&renderpassres)
	{
		return RenderPass::Loaded<std::remove_cv_t<std::remove_reference_t<R>>>(loadRenderPassRef(std::forward<R>(renderpassres)));
	}

	template <typename ResType>
	decltype(auto) load(ResType &&res)
	{
		static_cast<void>(res);

		if constexpr (std::is_base_of_v<rs::Shader, std::remove_reference_t<ResType>>) {
			return loadShader(std::forward<ResType>(res));
		} else if constexpr (std::is_base_of_v<rs::RenderPass, std::remove_reference_t<ResType>>) {
			return loadRenderPass(std::forward<ResType>(res));
		} else
			static_assert(!std::is_same_v<ResType, ResType>, "Unsupported resource type");
	}

	class Handle
	{
	public:
		Handle(std::unique_ptr<Device> &&device) :
			m_device(std::move(device))
		{
		}

		template <sb::Queue::Flag Flags>
		auto queue(size_t index)
		{
			return Queue::Handle<Flags>(m_device->getQueue(Flags, index));
		}

		auto swapchain(Surface &surface, const svec2 &extent, size_t desiredImageCount, sb::Image::Usage usage, sb::Queue &queue)
		{
			return Swapchain::Handle(m_device->createSwapchain(surface, extent, desiredImageCount, usage, queue));
		}

		auto image2D(Format format, const svec2 &extent, const sb::Image::MipmapLevels &mipLevels, Image::Usage usage, sb::Queue &queue)
		{
			return Image2D(m_device->createImage(Image::Type::Image2D, format, Image::Sample::Count1, svec3(extent.x, extent.y, 1), 1, mipLevels, usage, queue));
		}

		auto image2DMS(Format format, Image::Sample sampleCount, const svec2 &extent, const sb::Image::MipmapLevels &mipLevels, Image::Usage usage, sb::Queue &queue)
		{
			return Image2DMS(m_device->createImage(Image::Type::Image2D, format, sampleCount, svec3(extent.x, extent.y, 1), 1, mipLevels, usage, queue));
		}

		auto image2DArray(Format format, const svec2 &extent, size_t layers, const sb::Image::MipmapLevels &mipLevels, Image::Usage usage, sb::Queue &queue)
		{
			return Image2DArray(m_device->createImage(Image::Type::Image2DArray, format, Image::Sample::Count1, svec3(extent.x, extent.y, 1), layers, mipLevels, usage, queue));
		}

		auto image2DMSArray(Format format, Image::Sample sampleCount, const svec2 &extent, size_t layers, const sb::Image::MipmapLevels &mipLevels, Image::Usage usage, sb::Queue &queue)
		{
			return Image2DMSArray(m_device->createImage(Image::Type::Image2DArray, format, sampleCount, svec3(extent.x, extent.y, 1), layers, mipLevels, usage, queue));
		}

		auto semaphore(void)
		{
			return Semaphore::Handle(m_device->createSemaphore());
		}

		auto fence(bool isSignaled = false)
		{
			return Fence::Handle(m_device->createFence(isSignaled));
		}

		template <typename VertexType>
		auto vertexBuffer(size_t size, sb::Queue &queue)
		{
			auto s = size * sizeof(VertexType);
			return Buffer::Vertex<VertexType>(m_device->createBuffer(s, Buffer::Location::Device, Buffer::Usage::TransferDst | Buffer::Usage::VertexBuffer, queue), s);
		}

		auto index16Buffer(size_t size, sb::Queue &queue)
		{
			auto s = size * sizeof(uint16_t);
			return Buffer::Index16(m_device->createBuffer(s, Buffer::Location::Device, Buffer::Usage::TransferDst | Buffer::Usage::IndexBuffer, queue), s);
		}

		auto index32Buffer(size_t size, sb::Queue &queue)
		{
			auto s = size * sizeof(uint32_t);
			return Buffer::Index32(m_device->createBuffer(s, Buffer::Location::Device, Buffer::Usage::TransferDst | Buffer::Usage::IndexBuffer, queue), s);
		}

		auto buffer(size_t size, Buffer::Usage usage, sb::Queue &queue)
		{
			return Buffer::Handle(m_device->createBuffer(size, Buffer::Location::Device, usage, queue), size);
		}

		auto mappableBuffer(size_t size, Buffer::Usage usage, sb::Queue &queue)
		{
			return Buffer::Mappable(m_device->createBuffer(size, Buffer::Location::Host, usage, queue), size);
		}

		template <typename VertexType>
		auto model(Buffer::Vertex<VertexType> &vertex)
		{
			return Model::Typed<VertexType>(m_device->createModel(vertex, vertex.size()));
		}

		template <typename VertexType>
		auto model(Buffer::Vertex<VertexType> &vertex, Buffer::Index16 &index_buffer)
		{
			return Model::Typed<VertexType>::Indexed16(m_device->createModelIndexed(vertex, vertex.size(), index_buffer, Model::IndexType::Uint16));
		}

		template <typename VertexType>
		auto model(Buffer::Vertex<VertexType> &vertex, Buffer::Index32 &index_buffer)
		{
			return Model::Typed<VertexType>::Indexed32(m_device->createModelIndexed(vertex, index_buffer, Model::IndexType::Uint32, index_buffer.size()));
		}

		auto sampler(Filter magFilter, Filter minFilter, const Sampler::AddressModeUVW &addressMode, BorderColor borderColor, const std::optional<CompareOp> &compare, Sampler::MipmapMode mipmapMode, float minLod, float maxLod, float mipLodBias, const std::optional<float> &anisotropy)
		{
			return Sampler::Handle(m_device->createSampler(magFilter, minFilter, true, addressMode, borderColor, compare, mipmapMode, minLod, maxLod, mipLodBias, anisotropy));
		}

		auto samplerUnnormalized(Filter filter, const Sampler::AddressModeUVW &addressMode, BorderColor borderColor, float mipLodBias)
		{
			return Sampler::Handle(m_device->createSampler(filter, filter, false, addressMode, borderColor, std::nullopt, Sampler::MipmapMode::Nearest, 0.0f, 0.0f, mipLodBias, std::nullopt));
		}

		template <typename ResType>
		decltype(auto) load(ResType &&res)
		{
			return m_device->load(std::forward<ResType>(res));
		}

	private:
		std::unique_ptr<Device> m_device;
	};
};

template <typename ShaderRes>
class Shader::DescriptorSet::Layout::Resolver::Foreign : public Shader::DescriptorSet::Layout::Resolver
{
public:
	Foreign(Device &device, ShaderRes &shaderres, size_t set_ndx) :
		m_loaded(device.loadShader(shaderres)),
		m_layout((**RefGetter<CacheRefHolder>(m_loaded).get()).setLayout(set_ndx))
	{
	}
	~Foreign(void) override
	{
	}

	const Layout& resolve(void) const override
	{
		return m_layout;
	}

private:
	Shader::Loaded<ShaderRes> m_loaded;
	const Layout &m_layout;
};

}