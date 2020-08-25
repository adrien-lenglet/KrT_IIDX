#pragma once

#include "Krt.hpp"
#include "Subtile/RenderList.hpp"
#include "res.resdecl.hpp"

namespace Krt {

class EntityTest;

class Track : public Instance::World<Track>
{
public:
	Track(void);
	~Track(void) override;

	Event<> done;
	int track_data = 96;

	class Render : public sb::Render::Pass
	{
		Instance &m_instance;
		decltype(res.shaders().modules().camera().loaded()) m_camera_shader;
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
		decltype(m_cmd_pool.secondary()) m_cmd_sec;

		decltype(m_framebuffers) createFramebuffers(void)
		{
			decltype(m_framebuffers) res;

			for (auto &img : m_instance.swapchain.images())
				res.emplace_back(m_render_pass.framebuffer({1600, 900}, 1, img, m_fb_color, m_fb_normal, m_fb_depth_buffer));
			return res;
		}

	public:
		Render(Instance &instance) :
			m_instance(instance),
			m_camera_shader(instance.load(res.shaders().modules().camera())),
			m_render_pass(instance.load(res.shaders().render_passes().deffered())),
			m_fb_color(instance.image2D(sb::Format::rgba32_sfloat, sb::Image::Sample::Count1, {1600, 900}, sb::Image::Usage::InputAttachment | sb::Image::Usage::ColorAttachment, instance.graphics)),
			m_fb_normal(instance.image2D(sb::Format::rgba8_unorm, sb::Image::Sample::Count1, {1600, 900}, sb::Image::Usage::InputAttachment | sb::Image::Usage::ColorAttachment, instance.graphics)),
			m_fb_depth_buffer(instance.image2D(sb::Format::d24un_or_32sf_spl_att_sfb, sb::Image::Sample::Count1, {1600, 900}, sb::Image::Usage::InputAttachment | sb::Image::Usage::DepthStencilAttachment, instance.graphics)),
			m_framebuffers(createFramebuffers()),
			m_swapchain_img_avail(instance.semaphore()),
			m_render_done(instance.semaphore()),
			m_render_done_fence(instance.fence(true)),
			m_lighting_shader(instance.load(res.shaders().lighting())),
			m_cmd_pool(instance.graphics.pool<true>()),
			m_cmd_prim(m_cmd_pool.primary()),
			m_cmd_sec(m_cmd_pool.secondary()),
			camera(m_camera_shader.camera())
		{
		}
		~Render(void)
		{
			m_instance.graphics.waitIdle();
		}

		void render(void);

		decltype(m_camera_shader.camera()) camera;
	};

	Render render;

private:
	EntityTest &entity;
};

}

#include "EntityTest.hpp"