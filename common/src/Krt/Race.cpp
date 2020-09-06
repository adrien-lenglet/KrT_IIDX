#include "Race.hpp"
#include "res.resdecl.hpp"

namespace Krt {

Race::Race(Instance &instance) :
	instance(instance),

	m_sampler(instance.sampler(sb::Filter::Linear, sb::Filter::Nearest, sb::Sampler::AddressMode::MirroredRepeat, sb::BorderColor::FloatOpaqueWhite, std::nullopt, sb::Sampler::MipmapMode::Linear, 0.0f, 64.0f, 0.0f, std::nullopt)),
	m_fb_sampler(instance.samplerUnnormalized(sb::Filter::Nearest, sb::Sampler::AddressMode::ClampToEdge, sb::BorderColor::FloatOpaqueWhite, 0.0f)),

	m_color_pass(instance.load(res.shaders().render_passes().color())),
	m_post_pass(instance.load(res.shaders().render_passes().post())),
	m_fb_color(instance.image2D(sb::Format::rgba32_sfloat, {1600, 900}, 1, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, instance.graphics)),
	m_fb_depth_buffer(instance.image2D(sb::Format::d24un_or_32sf_spl_att_sfb, {1600, 900}, 1, sb::Image::Usage::DepthStencilAttachment | sb::Image::Usage::Sampled, instance.graphics)),
	m_color_fb(m_color_pass.framebuffer({1600, 900}, 1, m_fb_color, m_fb_depth_buffer)),
	m_post_fbs(createPostFramebuffers()),
	m_swapchain_img_avail(instance.semaphore()),

	m_depth_range_pass(instance.load(res.shaders().render_passes().depth_range())),
	m_first_depth_range(instance.load(res.shaders().first_depth_range())),
	m_compute_depth_range(instance.load(res.shaders().compute_depth_range())),
	m_fb_depth_range(instance.image2D(sb::Format::rg16_sfloat, {1024, 512}, sb::Image::allMipLevels, sb::Image::Usage::ColorAttachment | sb::Image::Usage::Sampled, instance.graphics)),
	m_depth_range_mips(getDepthRangeMips()),
	m_first_depth_range_in_fb(m_first_depth_range.fb(instance.graphics)),
	m_compute_depth_range_in_fb(getComputeDepthRangeInFb()),

	m_render_done(instance.semaphore()),
	m_render_done_fence(instance.fence(false)),
	m_lighting_shader(instance.load(res.shaders().lighting())),
	m_lighting_samplers(m_lighting_shader.fb(instance.graphics)),
	m_cmd_pool(instance.graphics.pool<true>()),
	m_cmd_prim(m_cmd_pool.primary()),

	m_track(instance.create<Track>())
{
	bind(m_track->done, [this](){
		m_is_done = true;
	});

	m_lighting_samplers.color.bind(m_sampler, m_fb_color, sb::Image::Layout::ShaderReadOnlyOptimal);
	m_lighting_samplers.depth_buffer.bind(m_fb_sampler, m_fb_depth_buffer, sb::Image::Layout::ShaderReadOnlyOptimal);
	m_lighting_samplers.depth_range.bind(m_fb_sampler, m_fb_depth_range, sb::Image::Layout::ShaderReadOnlyOptimal);
	m_lighting_draw_list.insert(m_lighting_shader.render(instance.screen_quad, m_lighting_samplers, m_track->render.camera));

	m_first_depth_range_in_fb.depth_buffer.bind(m_fb_sampler, m_fb_depth_buffer, sb::Image::Layout::ShaderReadOnlyOptimal);

	auto cmd = m_cmd_pool.primary();
	cmd.record([&](auto &cmd){
		cmd.imageMemoryBarrier(sb::PipelineStage::BottomOfPipe, sb::PipelineStage::TopOfPipe, {}, sb::Access::MemoryWrite, sb::Access::MemoryRead, sb::Image::Layout::Undefined, sb::Image::Layout::ShaderReadOnlyOptimal, m_fb_depth_range);
	});
	instance.graphics.submit(util::empty, cmd, util::empty);
	instance.graphics.waitIdle();
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
			cmd.memoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::AllGraphics, {}, sb::Access::TransferWrite, sb::Access::MemoryRead);

			cmd.setViewport({{0.0f, 0.0f}, {1600.0f, 900.0f}}, 0.0f, 1.0f);
			cmd.setScissor({{0, 0}, {1600, 900}});
			cmd.render(m_color_fb, {{0, 0}, {1600, 900}},
				sb::Color::f32(0.5f), 1.0f,

				[&](auto &cmd){
					m_track->render.render(cmd);
				}
			);

			cmd.imageMemoryBarrier(sb::PipelineStage::ColorAttachmentOutput | sb::PipelineStage::LateFragmentTests, sb::PipelineStage::FragmentShader, {}, sb::Access::ColorAttachmentWrite | sb::Access::DepthStencilAttachmentWrite, sb::Access::ShaderRead, sb::Image::Layout::ShaderReadOnlyOptimal, sb::Image::Layout::General, m_fb_depth_range);

			{
				size_t ndx = 0;
				for (auto &mip : m_depth_range_mips) {
					auto ex = mip.img.extent();
					cmd.setViewport({{0.0f, 0.0f}, {ex.x, ex.y}}, 0.0f, 1.0f);
					cmd.setScissor({{0, 0}, ex});
					cmd.render(mip.fb, {{0, 0}, ex},
						[&](auto &cmd){
							if (ndx == 0) {
								cmd.bind(m_first_depth_range);
								cmd.bind(m_first_depth_range, m_first_depth_range_in_fb, 0);
								cmd.draw(instance.screen_quad);
							} else {
								cmd.bind(m_compute_depth_range);
								cmd.bind(m_compute_depth_range, m_compute_depth_range_in_fb.at(ndx - 1), 0);
								cmd.draw(instance.screen_quad);
							}
						}
					);

					cmd.imageMemoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::FragmentShader, {}, sb::Access::ColorAttachmentWrite, sb::Access::ShaderRead, sb::Image::Layout::General, sb::Image::Layout::General, mip.img);

					ndx++;
				}
			}

			cmd.imageMemoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::FragmentShader, {}, sb::Access::ColorAttachmentWrite, sb::Access::ShaderRead, sb::Image::Layout::General, sb::Image::Layout::ShaderReadOnlyOptimal, m_fb_depth_range);

			cmd.setViewport({{0.0f, 0.0f}, {1600.0f, 900.0f}}, 0.0f, 1.0f);
			cmd.setScissor({{0, 0}, {1600, 900}});
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