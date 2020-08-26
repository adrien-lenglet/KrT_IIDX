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
	decltype(res.shaders().render_passes().deffered().loaded()) m_render_pass;
	sb::Image2D m_fb_color;
	sb::Image2D m_fb_normal;
	sb::Image2D m_fb_depth_buffer;
	std::vector<decltype(m_render_pass)::Framebuffer> m_framebuffers;
	decltype(instance.semaphore()) m_swapchain_img_avail;
	decltype(instance.semaphore()) m_render_done;
	decltype(instance.fence()) m_render_done_fence;
	decltype(res.shaders().lighting().loaded()) m_lighting_shader;
	decltype(instance.graphics.pool<true>()) m_cmd_pool;
	decltype(m_cmd_pool.primary()) m_cmd_prim;

	decltype(m_framebuffers) createFramebuffers(void)
	{
		decltype(m_framebuffers) res;

		for (auto &img : instance.swapchain.images())
			res.emplace_back(m_render_pass.framebuffer({1600, 900}, 1, img, m_fb_color, m_fb_normal, m_fb_depth_buffer));
		return res;
	}

	bool m_is_done = false;
	std::unique_ptr<Track> m_track;
};

}