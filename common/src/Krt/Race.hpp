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

	decltype(instance.load(res.shaders().render_passes().color())) m_color_pass;
	decltype(instance.load(res.shaders().render_passes().post())) m_post_pass;
	sb::Image2D m_fb_color;
	sb::Image2D m_fb_depth_buffer;
	sb::Image2D m_fb_w;
	decltype(m_color_pass)::Framebuffer m_color_fb;
	std::vector<decltype(m_post_pass)::Framebuffer> m_post_fbs;
	decltype(instance.semaphore()) m_swapchain_img_avail;
	decltype(instance.semaphore()) m_render_done;
	decltype(instance.fence()) m_render_done_fence;

	decltype(res.shaders().lighting().loaded()) m_lighting_shader;
	sb::Render::Pass m_lighting_draw_list;
	sb::Sampler::Handle m_sampler;
	decltype(m_lighting_shader.fb(instance.graphics)) m_lighting_samplers;

	decltype(instance.graphics.pool<true>()) m_cmd_pool;
	decltype(m_cmd_pool.primary()) m_cmd_prim;

	decltype(m_post_fbs) createPostFramebuffers(void)
	{
		decltype(m_post_fbs) res;

		for (auto &img : instance.swapchain.images())
			res.emplace_back(m_post_pass.framebuffer({1600, 900}, 1, img));
		return res;
	}

	bool m_is_done = false;
	std::unique_ptr<Track> m_track;
};

}