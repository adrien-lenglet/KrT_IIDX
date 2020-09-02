#include "Race.hpp"
#include "res.resdecl.hpp"

namespace Krt {

Race::Race(Instance &instance) :
	instance(instance),
	m_color_pass(instance.load(res.shaders().render_passes().color())),
	m_post_pass(instance.load(res.shaders().render_passes().post())),
	m_fb_color(instance.image2D(sb::Format::rgba32_sfloat, sb::Image::Sample::Count1, {1600, 900}, sb::Image::Usage::InputAttachment | sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, instance.graphics)),
	m_fb_depth_buffer(instance.image2D(sb::Format::d24un_or_32sf_spl_att_sfb, sb::Image::Sample::Count1, {1600, 900}, sb::Image::Usage::InputAttachment | sb::Image::Usage::DepthStencilAttachment | sb::Image::Usage::Sampled, instance.graphics)),
	m_color_fb(m_color_pass.framebuffer({1600, 900}, 1, m_fb_color, m_fb_depth_buffer)),
	m_post_fbs(createPostFramebuffers()),
	m_swapchain_img_avail(instance.semaphore()),
	m_render_done(instance.semaphore()),
	m_render_done_fence(instance.fence(false)),
	m_lighting_shader(instance.load(res.shaders().lighting())),
	m_sampler(instance.sampler(sb::Filter::Linear, sb::Filter::Nearest, sb::Sampler::MipmapMode::Linear, sb::Sampler::AddressMode::MirroredRepeat)),
	m_lighting_samplers(m_lighting_shader.fb(instance.graphics)),
	m_cmd_pool(instance.graphics.pool<true>()),
	m_cmd_prim(m_cmd_pool.primary()),

	m_track(instance.create<Track>())
{
	bind(m_track->done, [this](){
		m_is_done = true;
	});

	m_lighting_samplers.color.bind(m_sampler, m_fb_color, sb::Image::Layout::ShaderReadOnlyOptimal);
	m_lighting_samplers.depth_buffer.bind(m_sampler, m_fb_depth_buffer, sb::Image::Layout::ShaderReadOnlyOptimal);
	m_lighting_draw_list.insert(m_lighting_shader.render(instance.screen_quad, m_lighting_samplers, m_track->render.camera));
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

			cmd.render(m_color_fb, {{0, 0}, {1600, 900}},
				sb::Color::f32(0.5f), 1.0f,

				[&](auto &cmd){
					m_track->render.render(cmd);
				}
			);

			cmd.memoryBarrier(sb::PipelineStage::ColorAttachmentOutput | sb::PipelineStage::LateFragmentTests, sb::PipelineStage::FragmentShader, sb::Access::ColorAttachmentWrite | sb::Access::DepthStencilAttachmentWrite, sb::Access::InputAttachmentRead | sb::Access::ShaderRead, sb::DependencyFlag::ByRegion);

			cmd.render(m_post_fbs.at(img), {{0, 0}, {1600, 900}},
				[&](auto &cmd){
					m_lighting_draw_list.render(cmd);
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