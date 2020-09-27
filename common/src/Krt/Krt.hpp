#pragma once

#include <optional>
#include <vector>
#include <string>

#include "Subtile/Instance.hpp"
#include "res.resdecl.hpp"

namespace Krt {

class Config {
public:
	Config(const std::vector<std::string> &args);
	~Config(void);

	bool isNoValidation = false;
	bool forceValidation = false;
	bool isRenderDoc = false;
	bool isMonitor = false;
};

class Instance : public sb::Instance<Instance>
{
	static inline constexpr auto m_graphics_family = sb::Queue::Flag::Graphics | sb::Queue::Flag::Present;

	Instance(bool isDebug, const Config &config);

public:
	Instance(bool isDebug, const std::vector<std::string> &args);
	~Instance(void);

	void run(void);

	std::optional<sb::Surface::Handle> surface;
	sb::Device::Handle device;
	sb::Queue::Handle<m_graphics_family> graphics;
	std::optional<sb::Swapchain::Handle> swapchain;
	decltype(graphics.pool<true>()) m_transfer_pool;

public:
	size_t img_count;
	struct ImageRes {
		Instance &instance;
		decltype(m_transfer_pool.primary()) transfer_cmd_buf;
		sb::CommandBuffer &transfer_unsafe;
		sb::CommandBuffer::Record::Primary<sb::Queue::Flag::Graphics> transfer;
		sb::Buffer::Mappable staging_buffer;
		size_t staging_off;
		static inline constexpr size_t staging_buffer_size = 8000000;

		ImageRes(Instance &instance) :
			instance(instance),
			transfer_cmd_buf(instance.m_transfer_pool.primary()),
			transfer_unsafe(transfer_cmd_buf),
			transfer(transfer_cmd_buf),
			staging_buffer(instance.device.mappableBuffer(staging_buffer_size, sb::Buffer::Usage::TransferSrc | sb::Buffer::Usage::TransferDst, instance.graphics)),
			staging_off(0)
		{
		}

		void resetStagingOff(void)
		{
			staging_off = 0;
		}

		template <typename SrcType, typename Type>
		void copyBuffer(SrcType &&src, sb::Buffer::Array<Type> &dst)
		{
			auto src_size = src.size() * sizeof(decltype(*src.data()));
			if (staging_off + src_size > staging_buffer_size) {
				size_t buf_size = staging_buffer_size;
				auto buf = instance.device.mappableBuffer(buf_size, sb::Buffer::Usage::TransferSrc | sb::Buffer::Usage::TransferDst, instance.graphics);
				size_t off = 0;
				size_t bytes_left = src_size;
				auto cmd = instance.m_transfer_pool.primary();
				while (bytes_left > 0) {
					cmd.record([&](auto &cmd){
						size_t to_write = std::min(bytes_left, buf_size);
						buf.write(0, to_write, reinterpret_cast<const char*>(src.data()) + off);
						cmd.copy(buf.region(0, to_write), dst.region(off, to_write));
						bytes_left -= to_write;
						off += to_write;
					});
					instance.graphics.submit(util::empty, cmd, util::empty);
					instance.graphics.waitIdle();
				}
				return;
			}
			staging_buffer.write(staging_off, src_size, src.data());
			transfer.copy(staging_buffer.region(staging_off, src_size), dst);
			staging_off += src_size;
		}

		void copyDataToImage(const void *srcPixels, size_t sizeofPixel, sb::Image2D &dstImage, sb::Image::Layout dstLayout, const sb::srect3 &dstRegion)
		{
			auto src_size = dstRegion.extent.x * dstRegion.extent.y * dstRegion.extent.z * sizeofPixel;
			if (staging_off + src_size > staging_buffer_size) {
				size_t lines_per_pass = std::min((staging_buffer_size / (dstRegion.extent.x * sizeofPixel)) / sizeofPixel, dstRegion.extent.y);
				if (lines_per_pass == 0)
					throw std::runtime_error("Can't even fit one line in staging buffer!");
				auto buf = instance.device.mappableBuffer(staging_buffer_size, sb::Buffer::Usage::TransferSrc | sb::Buffer::Usage::TransferDst, instance.graphics);
				for (size_t z = 0; z < dstRegion.extent.z; z++) {
					size_t line_off = 0;
					size_t byte_off = 0;
					size_t lines_left = dstRegion.extent.y;
					auto cmd = instance.m_transfer_pool.primary();
					while (lines_left > 0) {
						cmd.record([&](auto &cmd){
							size_t lines_to_write = std::min(lines_left, lines_per_pass);
							auto img_off = sb::svec3(0, line_off, z);
							auto img_extent = sb::svec3(dstRegion.extent.x, lines_to_write, 1);
							size_t bytes_to_write = img_extent.y * img_extent.x * sizeofPixel;
							buf.write(0, bytes_to_write, reinterpret_cast<const char*>(srcPixels) + byte_off);
							cmd.copyBufferToImage(buf.region(0, bytes_to_write), dstImage, dstLayout, dstImage.blitRegion(dstRegion.offset + img_off, img_extent));
							lines_left -= lines_to_write;
							line_off += lines_to_write;
							byte_off += bytes_to_write;
						});
						instance.graphics.submit(util::empty, cmd, util::empty);
						instance.graphics.waitIdle();
					}
				}
				return;
			}
			staging_buffer.write(staging_off, src_size, srcPixels);
			transfer.copyBufferToImage(staging_buffer.region(staging_off, ~0ULL), dstImage, dstLayout, dstRegion);
			staging_off += src_size;
		}

		template <typename DescSet>
		void uploadDescSet(DescSet &&set)
		{
			auto src = set.uniformBufferData();
			auto src_size = src.size() * sizeof(decltype(*src.data()));
			if (src_size > 0) {
				staging_buffer.write(staging_off, src_size, src.data());
				transfer.copy(staging_buffer.region(staging_off, src_size), set.uniformBufferRegion());
			}
			staging_off += src_size;

			src = set.storageBufferData();
			src_size = src.size() * sizeof(decltype(*src.data()));
			if (src_size > 0) {
				staging_buffer.write(staging_off, src_size, src.data());
				transfer.copy(staging_buffer.region(staging_off, src_size), set.storageBufferRegion());
			}
			staging_off += src_size;
		}
	};
	std::vector<ImageRes> images;
	decltype(images) createImages(void)
	{
		decltype(images) res;

		for (size_t i = 0; i < img_count; i++)
			res.emplace_back(*this);
		return res;
	}
	size_t cur_img;
	ImageRes *cur_img_res;

	void nextFrame(void)
	{
		cur_img = (cur_img + 1) % images.size();
		cur_img_res = &images.at(cur_img);
	}

private:
	sb::Buffer::Vertex<decltype(res.shaders().vertex().p2().loaded())::Vertex> m_screen_quad_buffer;
	decltype(m_screen_quad_buffer) createScreenQuadBuffer(void);

public:
	sb::Model::Typed<decltype(res.shaders().vertex().p2().loaded())::Vertex> screen_quad;
};

}