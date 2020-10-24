#pragma once

#include "Track.hpp"

namespace Krt {

class Race : public sb::Event::Socket
{
public:
	Race(Instance &instance);
	~Race(void);

	void run(void);

	Instance &instance;

	sb::Sampler::Handle m_sampler;
	sb::Sampler::Handle m_sampler_clamp;
	sb::Sampler::Handle m_sampler_nearest;
	sb::Sampler::Handle m_fb_sampler;
	sb::Sampler::Handle m_fb_sampler_linear;

	decltype(instance.device.load(res.shaders().render_passes().opaque())) m_opaque_pass;

	decltype(instance.device.load(res.shaders().render_passes().depth_max())) m_depth_max_pass;
	decltype(instance.device.load(res.shaders().depth_max())) m_depth_max_shader;

	decltype(instance.device.load(res.shaders().render_passes().buffer_to_wsi_screen())) m_buffer_to_wsi_screen;
	decltype(instance.device.load(res.shaders().diffuse_to_wsi_screen())) m_diffuse_to_wsi_screen;

	decltype(res.shaders().modules().env().loaded()) m_env_shader;
	decltype(res.shaders().modules().rt().loaded()) m_rt_shader;

	decltype(instance.device.load(res.shaders().render_passes().scheduling())) m_scheduling_pass;
	decltype(instance.device.load(res.shaders().modules().scheduling_fb())) m_scheduling_fb_shader;

	decltype(instance.device.load(res.shaders().render_passes().cube_depth())) m_cube_depth_pass;
	decltype(instance.device.load(res.shaders().cube_depth())) m_cube_depth_shader;

	decltype(instance.graphics.pool<true>()) m_cmd_pool;
	size_t m_rt_quality;

	sb::ImageCube env;
	decltype(instance.device.load(res.shaders().opaque_env())) m_opaque_env_shader;

	struct Image;
	std::vector<Image> images;
	decltype(images) getImages(void);

	bool m_is_done = false;
	std::unique_ptr<Track> m_track;
};

struct Race::Image {

	class DepthRange
	{
	public:
		virtual ~DepthRange(void) = default;

		virtual sb::Image2D& depthBufferFl(void) = 0;
		virtual void drawDepth(sb::CommandBuffer::Record::Primary<sb::Queue::Flag::Graphics> &cmd, Track &track) = 0;
		virtual void schedule(sb::CommandBuffer::Record::Primary<sb::Queue::Flag::Graphics> &cmd, Image &img) = 0;
	};

	class DepthStero : public DepthRange
	{
	public:
		DepthStero(Race &race, sb::Image2D &fb_depth_buffer, sb::Image2D &fb_depth_buffer_max) :
			race(race),
			m_depth_inter_front_shader(race.instance.device.load(res.shaders().stereo().depth_inter_front())),
			m_depth_inter_back_shader(race.instance.device.load(res.shaders().stereo().depth_inter_back())),
			m_depth_range_pass(race.instance.device.load(res.shaders().stereo().render_passes().depth_range())),
			m_first_depth_range(race.instance.device.load(res.shaders().stereo().first_depth_range())),
			m_compute_depth_range(race.instance.device.load(res.shaders().stereo().compute_depth_range())),
			m_depth_to_fl_pass(race.instance.device.load(res.shaders().stereo().render_passes().depth_to_fl())),
			m_depth_to_fl_shader(race.instance.device.load(res.shaders().stereo().depth_to_fl())),
			m_scheduling_shader(race.instance.device.load(res.shaders().stereo().scheduling())),

			extent(race.instance.swapchain->extent()),
			depth_inter_front(race.instance.device.image2D(sb::Format::d24un_or_32sf_spl_att_sfb, extent, 1, sb::Image::Usage::DepthStencilAttachment | sb::Image::Usage::Sampled | sb::Image::Usage::TransferSrc, race.instance.graphics)),
			depth_inter_front_fb(race.m_depth_max_pass.framebuffer(extent, 1, depth_inter_front)),
			depth_inter_front_set(m_depth_inter_front_shader.fb(race.instance.graphics)),
			depth_inter_back(race.instance.device.image2D(sb::Format::d24un_or_32sf_spl_att_sfb, extent, 1, sb::Image::Usage::DepthStencilAttachment | sb::Image::Usage::Sampled | sb::Image::Usage::TransferSrc, race.instance.graphics)),
			depth_inter_back_fb(race.m_depth_max_pass.framebuffer(extent, 1, depth_inter_back)),
			depth_inter_back_set(m_depth_inter_back_shader.fb(race.instance.graphics)),

			fb_depth_buffer_raw_fl(race.instance.device.image2D(sb::Format::rgba32_sfloat, {static_cast<size_t>(std::pow(2.0, std::ceil(std::log2(extent.x)))), static_cast<size_t>(std::pow(2.0, std::ceil(std::log2(extent.y))))}, sb::Image::allMipLevels, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled | sb::Image::Usage::TransferSrc | sb::Image::Usage::TransferDst, race.instance.graphics)),
			fb_depth_buffer_raw_fl_mips(getDepthBufferRawFlMips()),
			depth_to_fl_fb(m_depth_to_fl_pass.framebuffer(fb_depth_buffer_raw_fl_mips.at(0).extent(), 1, fb_depth_buffer_raw_fl_mips.at(0))),
			depth_to_fl_set(m_depth_to_fl_shader.fb(race.instance.graphics)),
			fb_depth_buffer_fl(race.instance.device.image2D(sb::Format::rgba32_sfloat, sb::svec2(static_cast<size_t>(std::pow(2.0, std::ceil(std::log2(extent.x)))), static_cast<size_t>(std::pow(2.0, std::ceil(std::log2(extent.y))))), sb::Image::allMipLevels, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled | sb::Image::Usage::TransferSrc | sb::Image::Usage::TransferDst, race.instance.graphics)),
			fb_depth_buffer_fl_mips(getDepthBufferFlMips()),

			first_depth_range_in_fb(getFirstDepthRangeInFb()),
			compute_depth_range_in_fb(getComputeDepthRangeInFb())
		{
			depth_inter_front_set.prev.bind(race.m_sampler, fb_depth_buffer, sb::Image::Layout::ShaderReadOnlyOptimal);
			depth_inter_front_set.size = glm::vec2(1.0) / glm::vec2(depth_inter_front.extent());
			race.instance.cur_img_res->uploadDescSet(depth_inter_front_set);
			depth_inter_back_set.prev.bind(race.m_sampler, depth_inter_front, sb::Image::Layout::ShaderReadOnlyOptimal);
			depth_inter_back_set.size = glm::vec2(1.0) / glm::vec2(depth_inter_back.extent());
			race.instance.cur_img_res->uploadDescSet(depth_inter_back_set);

			depth_to_fl_set.depth_buffer.bind(race.m_fb_sampler, fb_depth_buffer, sb::Image::Layout::ShaderReadOnlyOptimal);
			depth_to_fl_set.depth_inter_front.bind(race.m_sampler_nearest, depth_inter_front, sb::Image::Layout::ShaderReadOnlyOptimal);
			depth_to_fl_set.depth_inter_back.bind(race.m_sampler_nearest, depth_inter_back, sb::Image::Layout::ShaderReadOnlyOptimal);
			depth_to_fl_set.depth_buffer_max.bind(race.m_sampler_nearest, fb_depth_buffer_max, sb::Image::Layout::ShaderReadOnlyOptimal);
		}
		~DepthStero(void) override
		{
		}

		sb::Image2D& depthBufferFl(void) override
		{
			return fb_depth_buffer_fl;
		}

		void drawDepth(sb::CommandBuffer::Record::Primary<sb::Queue::Flag::Graphics> &cmd, Track &track) override
		{
			cmd.render(depth_inter_front_fb, {{0, 0}, extent},
				1.0f,

				[&](auto &cmd){
					cmd.bind(m_depth_inter_front_shader);
					cmd.bind(m_depth_inter_front_shader, track.render.camera, 0);
					cmd.bind(m_depth_inter_front_shader, depth_inter_front_set, 1);
					cmd.bind(m_depth_inter_front_shader, track.entity.m_depth_object, 2);
					cmd.draw(track.entity.m_model);
				}
			);

			cmd.memoryBarrier(sb::PipelineStage::LateFragmentTests, sb::PipelineStage::FragmentShader, {},
				sb::Access::DepthStencilAttachmentWrite, sb::Access::ShaderRead);

			cmd.render(depth_inter_back_fb, {{0, 0}, extent},
				1.0f,

				[&](auto &cmd){
					cmd.bind(m_depth_inter_back_shader);
					cmd.bind(m_depth_inter_back_shader, track.render.camera, 0);
					cmd.bind(m_depth_inter_back_shader, depth_inter_back_set, 1);
					cmd.bind(m_depth_inter_back_shader, track.entity.m_depth_object, 2);
					cmd.draw(track.entity.m_model);
				}
			);

			cmd.memoryBarrier(sb::PipelineStage::LateFragmentTests, sb::PipelineStage::FragmentShader, {},
				sb::Access::DepthStencilAttachmentWrite, sb::Access::ShaderRead);

			cmd.render(depth_to_fl_fb, {{0, 0}, fb_depth_buffer_raw_fl.extent()},
				[&](auto &cmd){
					cmd.bind(m_depth_to_fl_shader);
					cmd.bind(m_depth_to_fl_shader, depth_to_fl_set, 0);
					cmd.draw(race.instance.screen_quad);
				}
			);

			cmd.imageMemoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::Transfer, {},
				sb::Access::ColorAttachmentWrite, sb::Access::TransferRead,
				sb::Image::Layout::ShaderReadOnlyOptimal, sb::Image::Layout::TransferSrcOptimal, fb_depth_buffer_raw_fl_mips.at(0));

			{
				auto end = fb_depth_buffer_raw_fl_mips.end();
				for (auto it = fb_depth_buffer_raw_fl_mips.begin() + 1; it != end; it++) {
					auto &cur = *it;
					cmd.imageMemoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::Transfer, {},
						sb::Access::TransferWrite, sb::Access::TransferRead,
						sb::Image::Layout::Undefined, sb::Image::Layout::TransferDstOptimal, cur);

					cmd.blit(*(it - 1), sb::Image::Layout::TransferSrcOptimal, (it - 1)->blitRegion({0, 0}, (it - 1)->extent()),
					cur, sb::Image::Layout::TransferDstOptimal, cur.blitRegion({0, 0}, cur.extent()), sb::Filter::Linear);

					cmd.imageMemoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::Transfer, {},
						sb::Access::TransferWrite, sb::Access::TransferRead,
						sb::Image::Layout::TransferDstOptimal, sb::Image::Layout::TransferSrcOptimal, cur);

					cmd.imageMemoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::Transfer, {},
						sb::Access::TransferWrite, sb::Access::TransferRead,
						sb::Image::Layout::TransferSrcOptimal, sb::Image::Layout::ShaderReadOnlyOptimal, *(it - 1));
				}
			}

			cmd.imageMemoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::FragmentShader, {},
				sb::Access::TransferWrite, sb::Access::ShaderRead,
				sb::Image::Layout::TransferSrcOptimal, sb::Image::Layout::ShaderReadOnlyOptimal, *fb_depth_buffer_raw_fl_mips.rbegin());

			{
				size_t ndx = 0;
				for (auto &mip : fb_depth_buffer_fl_mips) {
					auto ex = mip.img.extent();
					cmd.setViewport({{0.0f, 0.0f}, {ex.x, ex.y}}, 0.0f, 1.0f);
					cmd.setScissor({{0, 0}, ex});
					cmd.render(mip.fb, {{0, 0}, ex},
						[&](auto &cmd){
							if (ndx == 0) {
								cmd.bind(m_first_depth_range);
								cmd.bind(m_first_depth_range, first_depth_range_in_fb, 0);
								cmd.draw(race.instance.screen_quad);
							} else {
								cmd.bind(m_compute_depth_range);
								cmd.bind(m_compute_depth_range, compute_depth_range_in_fb.at(ndx - 1), 0);
								cmd.draw(race.instance.screen_quad);
							}
						}
					);

					cmd.memoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::FragmentShader, {},
						sb::Access::ColorAttachmentWrite, sb::Access::ShaderRead);

					ndx++;
				}
			}

			/*{
				auto ex = img.cube_depth.extent();
				cmd.render(img.cube_depth_fb, {{0, 0}, ex},
					[&](auto &cmd){
						cmd.setViewport({{0.0f, 0.0f}, {ex.x, ex.y}}, 0.0f, 1.0f);
						cmd.setScissor({{0, 0}, ex});
						cmd.bind(m_cube_depth_shader);
						cmd.bind(m_cube_depth_shader, img.cube_depth_set, 0);
						cmd.draw(instance.screen_quad);
					}
				);
			}*/
		}

		void schedule(sb::CommandBuffer::Record::Primary<sb::Queue::Flag::Graphics> &cmd, Image &img) override
		{
			cmd.render(img.scheduling_fb, {{0, 0}, race.instance.swapchain->extent()},
				[&](auto &cmd){
					cmd.bind(m_scheduling_shader);
					cmd.bind(m_scheduling_shader, img.rt_set, 0);
					cmd.bind(m_scheduling_shader, img.env_set, 1);
					cmd.bind(m_scheduling_shader, img.scheduling_set, 2);
					cmd.draw(race.instance.screen_quad);
				}
			);
		}

	private:
		Race &race;
		decltype(race.instance.device.load(res.shaders().stereo().depth_inter_front())) m_depth_inter_front_shader;
		decltype(race.instance.device.load(res.shaders().stereo().depth_inter_back())) m_depth_inter_back_shader;

		decltype(race.instance.device.load(res.shaders().stereo().render_passes().depth_range())) m_depth_range_pass;
		decltype(race.instance.device.load(res.shaders().stereo().first_depth_range())) m_first_depth_range;
		decltype(race.instance.device.load(res.shaders().stereo().compute_depth_range())) m_compute_depth_range;

		decltype(race.instance.device.load(res.shaders().stereo().render_passes().depth_to_fl())) m_depth_to_fl_pass;
		decltype(race.instance.device.load(res.shaders().stereo().depth_to_fl())) m_depth_to_fl_shader;

		decltype(instance.device.load(res.shaders().stereo().scheduling())) m_scheduling_shader;

		sb::svec2 extent;

		sb::Image2D depth_inter_front;
		decltype(Race::m_depth_max_pass)::Framebuffer depth_inter_front_fb;
		decltype(m_depth_inter_front_shader.fb(race.instance.graphics)) depth_inter_front_set;
		sb::Image2D depth_inter_back;
		decltype(Race::m_depth_max_pass)::Framebuffer depth_inter_back_fb;
		decltype(m_depth_inter_back_shader.fb(race.instance.graphics)) depth_inter_back_set;

		sb::Image2D fb_depth_buffer_raw_fl;
		std::vector<sb::Image2D> fb_depth_buffer_raw_fl_mips;
		decltype(fb_depth_buffer_raw_fl_mips) getDepthBufferRawFlMips(void)
		{
			decltype(fb_depth_buffer_raw_fl_mips) res;

			for (size_t i = 0; i < fb_depth_buffer_raw_fl.mipLevels(); i++)
				res.emplace_back(fb_depth_buffer_raw_fl.view(sb::ComponentSwizzle::Identity, sb::Image::Aspect::Color, sb::Range(i, 1)));
			return res;
		}
		decltype(m_depth_to_fl_pass)::Framebuffer depth_to_fl_fb;
		decltype(m_depth_to_fl_shader.fb(race.instance.graphics)) depth_to_fl_set;
		sb::Image2D fb_depth_buffer_fl;
		struct DepthBufferMip {
			sb::Image2D img;
			decltype(m_depth_range_pass)::Framebuffer fb;
		};
		std::vector<DepthBufferMip> fb_depth_buffer_fl_mips;
		decltype(fb_depth_buffer_fl_mips) getDepthBufferFlMips(void)
		{
			decltype(fb_depth_buffer_fl_mips) res;

			for (size_t i = 0; i < fb_depth_buffer_fl.mipLevels(); i++) {
				auto img = fb_depth_buffer_fl.view(sb::ComponentSwizzle::Identity, sb::Image::Aspect::Color, sb::Range(i, 1));
				auto fb = m_depth_range_pass.framebuffer(img.extent(), 1, img);
				res.emplace_back(DepthBufferMip{std::move(img), std::move(fb)});
			}
			return res;
		}

		decltype(m_first_depth_range.fb(race.instance.graphics)) first_depth_range_in_fb;
		decltype(first_depth_range_in_fb) getFirstDepthRangeInFb(void)
		{
			auto res = m_first_depth_range.fb(race.instance.graphics);

			res.up.bind(race.m_fb_sampler, fb_depth_buffer_raw_fl_mips.at(0), sb::Image::Layout::ShaderReadOnlyOptimal);
			return res;
		}
		std::vector<decltype(m_compute_depth_range.fb(race.instance.graphics))> compute_depth_range_in_fb;
		decltype(compute_depth_range_in_fb) getComputeDepthRangeInFb(void)
		{
			decltype(compute_depth_range_in_fb) res;

			auto end = fb_depth_buffer_fl_mips.end();
			for (auto it = fb_depth_buffer_fl_mips.begin() + 1; it != end; it++) {
				auto in_fb = m_compute_depth_range.fb(race.instance.graphics);
				in_fb.up.bind(race.m_fb_sampler, (it - 1)->img, sb::Image::Layout::ShaderReadOnlyOptimal);
				res.emplace_back(std::move(in_fb));
			}
			return res;
		}
	};

	Image(Race &race, size_t rt_quality) :
		race(race),
		fb_albedo(race.instance.device.image2D(sb::Format::rgba8_unorm, race.instance.swapchain->extent(), 1, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, race.instance.graphics)),
		fb_emissive(race.instance.device.image2D(sb::Format::rgba16_sfloat, race.instance.swapchain->extent(), 1, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, race.instance.graphics)),
		fb_normal(race.instance.device.image2D(sb::Format::rgba16_sfloat, race.instance.swapchain->extent(), 1, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, race.instance.graphics)),
		fb_refl(race.instance.device.image2D(sb::Format::rgba8_unorm, race.instance.swapchain->extent(), 1, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, race.instance.graphics)),
		fb_depth_buffer(race.instance.device.image2D(sb::Format::d24un_or_32sf_spl_att_sfb, race.instance.swapchain->extent(), 1, sb::Image::Usage::DepthStencilAttachment | sb::Image::Usage::Sampled | sb::Image::Usage::TransferSrc, race.instance.graphics)),
		fb_depth_buffer_max(race.instance.device.image2D(sb::Format::d24un_or_32sf_spl_att_sfb, race.instance.swapchain->extent(), 1, sb::Image::Usage::DepthStencilAttachment | sb::Image::Usage::Sampled | sb::Image::Usage::TransferSrc, race.instance.graphics)),
		depth_buffer_max_fb(race.m_depth_max_pass.framebuffer(race.instance.swapchain->extent(), 1, fb_depth_buffer_max)),
		depth_buffer_trace_res(rt_quality),
		depth_range(new DepthStero(race, fb_depth_buffer, fb_depth_buffer_max)),
		depth_buffer_fl(depth_range->depthBufferFl()),
		opaque_fb(race.m_opaque_pass.framebuffer(race.instance.swapchain->extent(), 1, fb_albedo, fb_emissive, fb_normal, fb_refl, fb_depth_buffer)),
		primary(race.instance.device.image2D(sb::Format::rgba16_sfloat, race.instance.swapchain->extent(), 1, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, race.instance.graphics)),
		bounce0(race.instance.device.image2D(sb::Format::rgba16_sfloat, race.instance.swapchain->extent(), 1, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, race.instance.graphics)),
		bounce1(race.instance.device.image2D(sb::Format::rgba16_sfloat, race.instance.swapchain->extent(), 1, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, race.instance.graphics)),
		diffuse(race.instance.device.image2D(sb::Format::rgba16_sfloat, race.instance.swapchain->extent(), 1, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, race.instance.graphics)),
		diffuse_accum(race.instance.device.image2D(sb::Format::r32_sfloat, race.instance.swapchain->extent(), 1, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, race.instance.graphics)),
		env_set(race.m_env_shader.env(race.instance.graphics)),
		rt_set(race.m_rt_shader.rt_fb(race.instance.graphics)),
		swapchain_img_avail(race.instance.device.semaphore()),
		scheduling_fb(race.m_scheduling_pass.framebuffer(race.instance.swapchain->extent(), 1, primary, bounce0, bounce1, diffuse, diffuse_accum)),
		scheduling_set(race.m_scheduling_fb_shader.fb(race.instance.graphics)),
		buffer_to_wsi_screen_fbs(getBufferToWsiScreenFbs()),
		diffuse_to_wsi_screen_set(race.m_diffuse_to_wsi_screen.light(race.instance.graphics)),
		//cube_depth(race.instance.device.image2DArray(sb::Format::rg32_sfloat, {16, 16}, 6, sb::Image::allMipLevels, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, race.instance.graphics)),
		cube_depth(race.instance.device.image2DArray(sb::Format::rg32_sfloat, {512, 512}, 6, sb::Image::allMipLevels, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, race.instance.graphics)),
		cube_depth_mips(getCubeDepthMips()),
		cube_depth_fb(race.m_cube_depth_pass.framebuffer(cube_depth.extent(), 6, cube_depth_mips.at(0))),
		cube_depth_set(getCubeDepthSet()),
		render_done(race.instance.device.semaphore()),
		render_done_fence(race.instance.device.fence(false)),
		ever_rendered(false),
		cmd_prim(race.m_cmd_pool.primary())
	{
		env_set.map.bind(race.m_sampler, race.env, sb::Image::Layout::ShaderReadOnlyOptimal);
		rt_set.depth_buffer.bind(race.m_fb_sampler, fb_depth_buffer, sb::Image::Layout::ShaderReadOnlyOptimal);
		rt_set.depth_buffer_fl[0].bind(race.m_sampler_nearest, depth_buffer_fl, sb::Image::Layout::ShaderReadOnlyOptimal);
		rt_set.normal.bind(race.m_fb_sampler, fb_normal, sb::Image::Layout::ShaderReadOnlyOptimal);
		//rt_set.depth_buffer_fl_lin.bind(race.m_sampler, depth_buffer_fl, sb::Image::Layout::ShaderReadOnlyOptimal);
		rt_set.depth_buffer_fl_size = glm::vec2(1.0) / glm::vec2(depth_buffer_fl.extent());
		update_depth_buffer_trace_res(rt_quality);

		scheduling_set.albedo.bind(race.m_fb_sampler, fb_albedo, sb::Image::Layout::ShaderReadOnlyOptimal);
		scheduling_set.emissive.bind(race.m_fb_sampler, fb_emissive, sb::Image::Layout::ShaderReadOnlyOptimal);
		scheduling_set.normal.bind(race.m_fb_sampler, fb_normal, sb::Image::Layout::ShaderReadOnlyOptimal);

		diffuse_to_wsi_screen_set.diffuse.bind(race.m_fb_sampler, diffuse, sb::Image::Layout::ShaderReadOnlyOptimal);
		diffuse_to_wsi_screen_set.albedo.bind(race.m_fb_sampler, fb_albedo, sb::Image::Layout::ShaderReadOnlyOptimal);
		diffuse_to_wsi_screen_set.emissive.bind(race.m_fb_sampler, fb_emissive, sb::Image::Layout::ShaderReadOnlyOptimal);
		diffuse_to_wsi_screen_set.cube_depth.bind(race.m_sampler_nearest, cube_depth_mips.at(0), sb::Image::Layout::ShaderReadOnlyOptimal);

		auto cmd = race.m_cmd_pool.primary();
		cmd.record([&](auto &cmd){
			cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, fb_depth_buffer);
			cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, depth_buffer_fl);
			/*cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, depth_inter_front);
			cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, depth_inter_back);*/
			cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, primary);
			cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, bounce0);
			cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, bounce1);
			cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, diffuse);
			cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, fb_albedo);
			cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, fb_emissive);
			cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, diffuse_accum);
			cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {},
				sb::Access::MemoryWrite, sb::Access::MemoryRead,
				sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, cube_depth);
		});
		race.instance.graphics.submit(util::empty, cmd, util::empty);
		race.instance.graphics.waitIdle();
	}

	Race &race;

	sb::Image2D fb_albedo;
	sb::Image2D fb_emissive;
	sb::Image2D fb_normal;
	sb::Image2D fb_refl;
	sb::Image2D fb_depth_buffer;
	sb::Image2D fb_depth_buffer_max;
	decltype(Race::m_depth_max_pass)::Framebuffer depth_buffer_max_fb;

	size_t depth_buffer_trace_res;

	std::unique_ptr<DepthRange> depth_range;
	sb::Image2D &depth_buffer_fl;

	decltype(m_opaque_pass)::Framebuffer opaque_fb;
	sb::Image2D primary;
	sb::Image2D bounce0;
	sb::Image2D bounce1;
	sb::Image2D diffuse;
	sb::Image2D diffuse_accum;
	decltype(race.m_env_shader.env(race.instance.graphics)) env_set;
	decltype(race.m_rt_shader.rt_fb(race.instance.graphics)) rt_set;

	void update_depth_buffer_trace_res(size_t new_res)
	{
		rt_set.depth_buffer_trace_res = new_res;
		rt_set.depth_buffer_max_it = ((1 << (depth_buffer_fl.mipLevels() - new_res)) / 4) + 8;
		race.instance.cur_img_res->uploadDescSet(rt_set);
	}

	decltype(Race::instance.device.semaphore()) swapchain_img_avail;

	decltype(race.m_scheduling_pass)::Framebuffer scheduling_fb;
	decltype(race.m_scheduling_fb_shader.fb(race.instance.graphics)) scheduling_set;

	std::vector<decltype(race.m_buffer_to_wsi_screen)::Framebuffer> buffer_to_wsi_screen_fbs;
	decltype(race.m_diffuse_to_wsi_screen.light(race.instance.graphics)) diffuse_to_wsi_screen_set;
	decltype(buffer_to_wsi_screen_fbs) getBufferToWsiScreenFbs(void)
	{
		decltype(buffer_to_wsi_screen_fbs) res;

		for (auto &img : race.instance.swapchain->images())
			res.emplace_back(race.m_buffer_to_wsi_screen.framebuffer(race.instance.swapchain->extent(), 1, img));
		return res;
	}

	sb::Image2DArray cube_depth;
	std::vector<sb::Image2DArray> cube_depth_mips;
	decltype(cube_depth_mips) getCubeDepthMips(void)
	{
		decltype(cube_depth_mips) res;

		for (size_t i = 0; i < cube_depth.mipLevels(); i++)
			res.emplace_back(cube_depth.view(sb::ComponentSwizzle::Identity, sb::Image::Aspect::Color, sb::wholeRange, sb::Range(i, 1)));
		return res;
	}
	decltype(race.m_cube_depth_pass)::Framebuffer cube_depth_fb;
	decltype(race.m_cube_depth_shader.fb(race.instance.graphics)) cube_depth_set;
	decltype(cube_depth_set) getCubeDepthSet(void)
	{
		auto res = race.m_cube_depth_shader.fb(race.instance.graphics);

		res.cur_depth.bind(race.m_sampler_nearest, depth_buffer_fl, sb::Image::Layout::ShaderReadOnlyOptimal);
		return res;
	}

	decltype(race.instance.device.semaphore()) render_done;
	decltype(race.instance.device.fence()) render_done_fence;
	bool ever_rendered;
	decltype(m_cmd_pool.primary()) cmd_prim;
};

inline decltype(Race::images) Race::getImages(void)
{
	decltype(images) res;

	for (size_t i = 0; i < instance.img_count; i++)
		res.emplace_back(*this, m_rt_quality);
	{
		size_t ndx = 0;
		for (auto &i : res) {
			res.at((ndx + 1) % res.size()).cube_depth_set.last_cube.bind(m_sampler, i.cube_depth_mips.at(0), sb::Image::Layout::ShaderReadOnlyOptimal);

			auto &n = res.at((ndx + 1) % res.size());
			n.scheduling_set.last_albedo.bind(m_fb_sampler_linear, i.fb_albedo, sb::Image::Layout::ShaderReadOnlyOptimal);
			n.scheduling_set.last_emissive.bind(m_fb_sampler_linear, i.fb_emissive, sb::Image::Layout::ShaderReadOnlyOptimal);
			n.scheduling_set.last_depth_buffer.bind(m_fb_sampler_linear, i.fb_depth_buffer, sb::Image::Layout::ShaderReadOnlyOptimal);

			n.scheduling_set.last_primary.bind(m_fb_sampler_linear, i.primary, sb::Image::Layout::ShaderReadOnlyOptimal);
			n.scheduling_set.last_bounce0.bind(m_fb_sampler_linear, i.bounce0, sb::Image::Layout::ShaderReadOnlyOptimal);
			n.scheduling_set.last_bounce1.bind(m_fb_sampler_linear, i.bounce1, sb::Image::Layout::ShaderReadOnlyOptimal);
			n.scheduling_set.last_diffuse.bind(m_fb_sampler_linear, i.diffuse, sb::Image::Layout::ShaderReadOnlyOptimal);
			n.scheduling_set.last_diffuse_it.bind(m_fb_sampler_linear, i.diffuse_accum, sb::Image::Layout::ShaderReadOnlyOptimal);

			n.rt_set.depth_buffer_fl[1].bind(m_sampler_nearest, i.depth_buffer_fl, sb::Image::Layout::ShaderReadOnlyOptimal);

			ndx++;
		}
	}
	return res;
}

}