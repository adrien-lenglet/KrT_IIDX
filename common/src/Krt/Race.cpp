#include "Race.hpp"
#include "res.resdecl.hpp"

namespace Krt {

Race::Race(Instance &instance) :
	instance(instance),
	m_render_pass(instance.load(res.shaders().render_passes().deffered())),
	m_fb_color(instance.image2D(sb::Format::rgba32_sfloat, sb::Image::Sample::Count1, {1600, 900}, sb::Image::Usage::InputAttachment | sb::Image::Usage::ColorAttachment, instance.graphics)),
	m_fb_normal(instance.image2D(sb::Format::rgba8_unorm, sb::Image::Sample::Count1, {1600, 900}, sb::Image::Usage::InputAttachment | sb::Image::Usage::ColorAttachment, instance.graphics)),
	m_fb_depth_buffer(instance.image2D(sb::Format::d24un_or_32sf_spl_att_sfb, sb::Image::Sample::Count1, {1600, 900}, sb::Image::Usage::InputAttachment | sb::Image::Usage::DepthStencilAttachment, instance.graphics)),
	m_framebuffers(createFramebuffers()),
	m_swapchain_img_avail(instance.semaphore()),
	m_render_done(instance.semaphore()),
	m_render_done_fence(instance.fence(false)),
	m_lighting_shader(instance.load(res.shaders().lighting())),
	m_cmd_pool(instance.graphics.pool<true>()),
	m_cmd_prim(m_cmd_pool.primary()),

	m_track(instance.create<Track>())
{
	bind(m_track->done, [this](){
		m_is_done = true;
	});
}
Race::~Race(void)
{
}

void Race::run(void)
{
	while (!m_is_done) {
		instance.scanInputs();
		m_track->events.updateEvents();

		auto img = instance.swapchain.acquireNextImage(m_swapchain_img_avail);

		m_cmd_prim.record([&](auto &cmd){
			cmd.memoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::AllGraphics, sb::Access::TransferWrite, sb::Access::MemoryRead, sb::DependencyFlag::None);

			cmd.render(m_framebuffers.at(img), {{0, 0}, {1600, 900}},
				sb::Color::f32(0.5f), 1.0f,

				[&](auto &cmd){
					m_track->render.render(cmd);
				},
				[&](auto &cmd){
					cmd.bind(m_lighting_shader);
					cmd.draw(instance.screen_quad);
				}
			);
		});

		instance.transfer_unsafe.end();

		instance.graphics.submit(m_render_done_fence, std::pair {&m_swapchain_img_avail, sb::PipelineStage::ColorAttachmentOutput}, std::array{&instance.m_transfer_cmd_buf, &m_cmd_prim}, m_render_done);
		instance.graphics.present(m_render_done, instance.swapchain.images().at(img));

		m_render_done_fence.wait();
		m_render_done_fence.reset();
		instance.resetStagingOff();
		instance.transfer_unsafe.begin(sb::CommandBuffer::Usage::OneTimeSubmit);
	}
}

}