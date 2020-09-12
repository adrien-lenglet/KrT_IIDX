#pragma once

#include "Track.hpp"

namespace Krt {

class Race : public sb::Event::Socket
{
public:
	Race(Instance &instance);
	~Race(void);

	void run(void);

private:
	Instance &instance;

	sb::Sampler::Handle m_sampler;
	sb::Sampler::Handle m_sampler_clamp;
	sb::Sampler::Handle m_fb_sampler;
	sb::Sampler::Handle m_fb_sampler_linear;

	decltype(instance.load(res.shaders().render_passes().opaque())) m_opaque_pass;
	decltype(instance.load(res.shaders().render_passes().lighting())) m_lighting_pass;
	sb::Image2D m_fb_albedo;
	sb::Image2D m_fb_emissive;
	sb::Image2D m_fb_normal;
	sb::Image2D m_fb_depth_buffer;
	sb::Image2D m_fb_depth_buffer_fl;
	std::vector<sb::Image2D> m_fb_depth_buffer_fl_mips;
	decltype(m_fb_depth_buffer_fl_mips) getDepthBufferFlMips(void)
	{
		decltype(m_fb_depth_buffer_fl_mips) res;

		for (size_t i = 0; i < m_fb_depth_buffer_fl.mipLevels(); i++)
			res.emplace_back(m_fb_depth_buffer_fl.view(sb::ComponentSwizzle::Identity, sb::Image::Aspect::Color, sb::Range(i, 1)));
		return res;
	}

	decltype(m_opaque_pass)::Framebuffer m_opaque_fb;
	sb::Image2D m_lighting_img;
	decltype(m_lighting_pass)::Framebuffer m_lighting_fb;

	decltype(instance.semaphore()) m_swapchain_img_avail;

	decltype(instance.load(res.shaders().render_passes().depth_range())) m_depth_range_pass;
	decltype(instance.load(res.shaders().first_depth_range())) m_first_depth_range;
	decltype(instance.load(res.shaders().compute_depth_range())) m_compute_depth_range;
	sb::Image2D m_fb_depth_range;

	struct DepthRangeMip {
		sb::Image2D img;
		decltype(m_depth_range_pass)::Framebuffer fb;
	};

	std::vector<DepthRangeMip> m_depth_range_mips;
	decltype(m_depth_range_mips) getDepthRangeMips(void)
	{
		decltype(m_depth_range_mips) res;

		for (size_t i = 0; i < m_fb_depth_range.mipLevels(); i++) {
			auto img = m_fb_depth_range.view(sb::ComponentSwizzle::Identity, sb::Image::Aspect::Color, sb::Range(i, 1));
			auto fb = m_depth_range_pass.framebuffer(img.extent(), 1, img);

			res.emplace_back(DepthRangeMip{std::move(img), std::move(fb)});
		}
		return res;
	}

	decltype(instance.load(res.shaders().modules().depth_buffer())) m_depth_buffer_module;
	decltype(m_depth_buffer_module.depth_buffer(instance.graphics)) m_depth_buffer_set;
	decltype(instance.load(res.shaders().render_passes().depth_to_fl())) m_depth_to_fl_pass;
	decltype(m_depth_to_fl_pass)::Framebuffer m_depth_to_fl_fb;
	decltype(instance.load(res.shaders().depth_to_fl())) m_depth_to_fl_shader;
	std::vector<decltype(m_compute_depth_range.fb(instance.graphics))> m_compute_depth_range_in_fb;
	decltype(m_compute_depth_range_in_fb) getComputeDepthRangeInFb(void)
	{
		decltype(m_compute_depth_range_in_fb) res;

		auto end = m_depth_range_mips.end();
		for (auto it = m_depth_range_mips.begin() + 1; it != end; it++) {
			auto in_fb = m_compute_depth_range.fb(instance.graphics);
			in_fb.up.bind(m_fb_sampler, (it - 1)->img, sb::Image::Layout::ShaderReadOnlyOptimal);
			res.emplace_back(std::move(in_fb));
		}
		return res;
	}

	decltype(instance.load(res.shaders().render_passes().diffuse_bounce())) m_diffuse_bounce_pass;
	decltype(instance.load(res.shaders().diffuse_bounce())) m_diffuse_bounce_shader;
	decltype(m_diffuse_bounce_shader.random(instance.graphics)) m_diffuse_bounce_random;

	struct DiffuseBounce {
		sb::Image2D img;
		decltype(m_diffuse_bounce_pass)::Framebuffer fb;
		decltype(m_diffuse_bounce_shader.fb(instance.graphics)) set;
	};
	std::vector<DiffuseBounce> m_diffuse_bounces;
	std::vector<DiffuseBounce> getDiffuseBounces(size_t count)
	{
		std::vector<DiffuseBounce> res;

		for (size_t i = 0; i < count; i++) {
			auto img = instance.image2D(sb::Format::rgba32_sfloat, {1600, 900}, 1, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, instance.graphics);
			auto fb = m_diffuse_bounce_pass.framebuffer({1600, 900}, 1, img);
			auto set = m_diffuse_bounce_shader.fb(instance.graphics);
			set.albedo.bind(m_fb_sampler, m_fb_albedo, sb::Image::Layout::ShaderReadOnlyOptimal);
			set.normal.bind(m_fb_sampler, m_fb_normal, sb::Image::Layout::ShaderReadOnlyOptimal);
			if (i == 0)
				set.last_diffuse.bind(m_fb_sampler, m_lighting_img, sb::Image::Layout::ShaderReadOnlyOptimal);
			else
				set.last_diffuse.bind(m_fb_sampler, res.at(i - 1).img, sb::Image::Layout::ShaderReadOnlyOptimal);
			set.depth_buffer.bind(m_fb_sampler_linear, m_fb_depth_buffer, sb::Image::Layout::ShaderReadOnlyOptimal);
			set.depth_buffer_fl.bind(m_sampler_clamp, m_fb_depth_buffer_fl, sb::Image::Layout::ShaderReadOnlyOptimal);
			set.depth_range.bind(m_fb_sampler, m_fb_depth_range, sb::Image::Layout::ShaderReadOnlyOptimal);
			res.emplace_back(DiffuseBounce{std::move(img), std::move(fb), std::move(set)});
		}
		return res;
	}

	decltype(instance.load(res.shaders().render_passes().gather_bounces())) m_gather_bounces_pass;
	decltype(instance.load(res.shaders().gather_bounces())) m_gather_bounces_shader;
	decltype(m_gather_bounces_shader.light(instance.graphics)) m_gather_bounces_set;

	std::vector<decltype(m_gather_bounces_pass)::Framebuffer> m_gather_bounces_fbs;
	decltype(m_gather_bounces_fbs) getGatherBouncesFbs(void)
	{
		decltype(m_gather_bounces_fbs) res;

		for (auto &img : instance.swapchain.images())
			res.emplace_back(m_gather_bounces_pass.framebuffer({1600, 900}, 1, img));
		return res;
	}

	decltype(instance.semaphore()) m_render_done;
	decltype(instance.fence()) m_render_done_fence;

	decltype(res.shaders().lighting().loaded()) m_lighting_shader;
	sb::Render::Pass m_lighting_draw_list;
	decltype(m_lighting_shader.fb(instance.graphics)) m_lighting_samplers;

	decltype(instance.graphics.pool<true>()) m_cmd_pool;
	decltype(m_cmd_pool.primary()) m_cmd_prim;

	bool m_is_done = false;
	std::unique_ptr<Track> m_track;
};

}