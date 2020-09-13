#include <chrono>
#include "Race.hpp"
#include "res.resdecl.hpp"

namespace Krt {

Race::Race(Instance &instance) :
	instance(instance),

	m_sampler(instance.sampler(sb::Filter::Linear, sb::Filter::Nearest, sb::Sampler::AddressMode::MirroredRepeat, sb::BorderColor::FloatOpaqueWhite, std::nullopt, sb::Sampler::MipmapMode::Linear, 0.0f, 64.0f, 0.0f, std::nullopt)),
	m_sampler_clamp(instance.sampler(sb::Filter::Linear, sb::Filter::Linear, sb::Sampler::AddressMode::ClampToEdge, sb::BorderColor::FloatOpaqueWhite, std::nullopt, sb::Sampler::MipmapMode::Nearest, 0.0f, 64.0f, 0.0f, std::nullopt)),
	m_fb_sampler(instance.samplerUnnormalized(sb::Filter::Nearest, sb::Sampler::AddressMode::ClampToEdge, sb::BorderColor::FloatOpaqueWhite, 0.0f)),
	m_fb_sampler_linear(instance.samplerUnnormalized(sb::Filter::Linear, sb::Sampler::AddressMode::ClampToEdge, sb::BorderColor::FloatOpaqueWhite, 0.0f)),
	m_opaque_pass(instance.load(res.shaders().render_passes().opaque())),
	m_lighting_pass(instance.load(res.shaders().render_passes().lighting())),
	m_depth_range_pass(instance.load(res.shaders().render_passes().depth_range())),
	m_first_depth_range(instance.load(res.shaders().first_depth_range())),
	m_compute_depth_range(instance.load(res.shaders().compute_depth_range())),
	m_depth_buffer_module(instance.load(res.shaders().modules().depth_buffer())),
	m_depth_to_fl_pass(instance.load(res.shaders().render_passes().depth_to_fl())),
	m_depth_to_fl_shader(instance.load(res.shaders().depth_to_fl())),
	m_diffuse_bounce_pass(instance.load(res.shaders().render_passes().diffuse_bounce())),
	m_diffuse_bounce_shader(instance.load(res.shaders().diffuse_bounce())),
	m_gather_bounces_pass(instance.load(res.shaders().render_passes().gather_bounces())),
	m_gather_bounces_shader(instance.load(res.shaders().gather_bounces())),
	m_buffer_to_wsi_screen(instance.load(res.shaders().render_passes().buffer_to_wsi_screen())),
	m_diffuse_to_wsi_screen(instance.load(res.shaders().diffuse_to_wsi_screen())),
	m_lighting_shader(instance.load(res.shaders().lighting())),
	m_cmd_pool(instance.graphics.pool<true>()),
	images(getImages()),

	m_track(instance.create<Track>())
{
	bind(m_track->done, [this](){
		m_is_done = true;
	});
}

Race::~Race(void)
{
	instance.graphics.waitIdle();
}

void Race::run(void)
{
	Image *last_frame = nullptr;
	while (!m_is_done) {
		auto t_start = std::chrono::high_resolution_clock::now();

		auto &img = images.at(instance.cur_img);
		instance.scanInputs();
		m_track->events.updateEvents();

		auto t_before_ac = std::chrono::high_resolution_clock::now();
		auto swapchain_img = instance.swapchain.acquireNextImage(img.swapchain_img_avail);
		auto t_begin_record = std::chrono::high_resolution_clock::now();

		img.cmd_prim.record([&](auto &cmd){
			cmd.memoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::AllGraphics, {}, sb::Access::TransferWrite, sb::Access::MemoryRead);

			auto srgb_lin = [](double val){
				constexpr float unorm = 1.0 / 255.0;

				return std::pow(val * unorm, 2.2);
			};

			cmd.setViewport({{0.0f, 0.0f}, {1600.0f, 900.0f}}, 0.0f, 1.0f);
			cmd.setScissor({{0, 0}, {1600, 900}});
			cmd.render(img.opaque_fb, {{0, 0}, {1600, 900}},
				sb::Color::f32(0.0f), sb::Color::f32(srgb_lin(2.0), srgb_lin(145.0), srgb_lin(223.0), 0.0f), sb::Color::f32(0.0f), 1.0f,

				[&](auto &cmd){
					m_track->render.render(cmd);
				}
			);

			cmd.memoryBarrier(sb::PipelineStage::ColorAttachmentOutput | sb::PipelineStage::LateFragmentTests, sb::PipelineStage::FragmentShader, {},
				sb::Access::ColorAttachmentWrite | sb::Access::DepthStencilAttachmentWrite, sb::Access::ShaderRead);

			cmd.setViewport({{0.0f, 0.0f}, {2048.0f, 1024.0f}}, 0.0f, 1.0f);
			cmd.setScissor({{0, 0}, {2048, 1024}});
			cmd.render(img.depth_to_fl_fb, {{0, 0}, {2048, 1024}}, [&](auto &cmd){
				cmd.bind(m_depth_to_fl_shader);
				cmd.bind(m_depth_to_fl_shader, img.depth_buffer_set, 0);
				cmd.draw(instance.screen_quad);
			});

			cmd.imageMemoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::Transfer, {},
				sb::Access::ColorAttachmentWrite, sb::Access::TransferRead,
				sb::Image::Layout::ShaderReadOnlyOptimal, sb::Image::Layout::TransferSrcOptimal, img.fb_depth_buffer_fl_mips.at(0));

			{
				auto end = img.fb_depth_buffer_fl_mips.end();
				for (auto it = img.fb_depth_buffer_fl_mips.begin() + 1; it != end; it++) {

					auto &prev_mip = *(it - 1);
					auto &cur_mip = *it;

					cmd.imageMemoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::Transfer, {},
						sb::Access::TransferWrite, sb::Access::TransferRead,
						sb::Image::Layout::ShaderReadOnlyOptimal, sb::Image::Layout::TransferDstOptimal, cur_mip);

					cmd.blit(prev_mip, sb::Image::Layout::TransferSrcOptimal, prev_mip.blitRegion({0, 0}, prev_mip.extent()),
					cur_mip, sb::Image::Layout::TransferDstOptimal, cur_mip.blitRegion({0, 0}, cur_mip.extent()), sb::Filter::Linear);

					cmd.imageMemoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::Transfer, {},
						sb::Access::TransferWrite, sb::Access::TransferRead,
						sb::Image::Layout::TransferDstOptimal, sb::Image::Layout::TransferSrcOptimal, cur_mip);
				}
			}

			cmd.imageMemoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::FragmentShader, {},
				sb::Access::TransferWrite, sb::Access::ShaderRead,
				sb::Image::Layout::TransferSrcOptimal, sb::Image::Layout::ShaderReadOnlyOptimal, img.fb_depth_buffer_fl);

			{
				size_t ndx = 0;
				for (auto &mip : img.depth_range_mips) {
					auto ex = mip.img.extent();
					cmd.setViewport({{0.0f, 0.0f}, {ex.x, ex.y}}, 0.0f, 1.0f);
					cmd.setScissor({{0, 0}, ex});
					cmd.render(mip.fb, {{0, 0}, ex},
						[&](auto &cmd){
							if (ndx == 0) {
								cmd.bind(m_first_depth_range);
								cmd.bind(m_first_depth_range, img.depth_buffer_set, 0);
								cmd.draw(instance.screen_quad);
							} else {
								cmd.bind(m_compute_depth_range);
								cmd.bind(m_compute_depth_range, img.compute_depth_range_in_fb.at(ndx - 1), 0);
								cmd.draw(instance.screen_quad);
							}
						}
					);

					cmd.memoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::FragmentShader, {},
						sb::Access::ColorAttachmentWrite, sb::Access::ShaderRead);

					ndx++;
				}
			}

			cmd.setViewport({{0.0f, 0.0f}, {1600.0f, 900.0f}}, 0.0f, 1.0f);
			cmd.setScissor({{0, 0}, {1600, 900}});
			cmd.render(img.lighting_fb, {{0, 0}, {1600, 900}},
				[&](auto &cmd){
					cmd.bind(m_lighting_shader);
					cmd.bind(m_lighting_shader, img.lighting_samplers, 0);
					cmd.bind(m_lighting_shader, m_track->render.camera, 1);
					cmd.draw(instance.screen_quad);
				}
			);

			cmd.memoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::FragmentShader, {},
				sb::Access::ColorAttachmentWrite, sb::Access::ShaderRead);

			for (auto &normal : img.diffuse_bounce_random.normals) {
				double n = 1.0;
				auto a0 = std::acos(std::pow(m_track->urandf(), 1.0 / (n + 1.0)));
				auto a1 = 2.0 * sb::pi * m_track->urandf();
				auto sa0 = std::sin(a0);
				auto ca0 = std::cos(a0);
				auto sa1 = std::sin(a1);
				auto ca1 = std::cos(a1);
				normal = glm::vec3(sa0 * ca1, sa0 * sa1, ca0);
			}
			instance.cur_img_res->uploadDescSet(img.diffuse_bounce_random);

			for (auto &b : img.diffuse_bounces) {
				cmd.render(b.fb, {{0, 0}, {1600, 900}},
					[&](auto &cmd){
						cmd.bind(m_diffuse_bounce_shader);
						cmd.bind(m_diffuse_bounce_shader, img.diffuse_bounce_random, 0);
						cmd.bind(m_diffuse_bounce_shader, b.set, 1);
						cmd.bind(m_diffuse_bounce_shader, m_track->render.camera, 2);
						cmd.draw(instance.screen_quad);
					}
				);

				cmd.memoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::FragmentShader, {},
					sb::Access::ColorAttachmentWrite, sb::Access::ShaderRead);
			}

			cmd.render(img.gather_bounces_fb, {{0, 0}, {1600, 900}},
				[&](auto &cmd){
					cmd.bind(m_gather_bounces_shader);
					cmd.bind(m_gather_bounces_shader, img.gather_bounces_set, 0);
					cmd.draw(instance.screen_quad);
				}
			);

			cmd.memoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::FragmentShader, {},
				sb::Access::ColorAttachmentWrite, sb::Access::ShaderRead);

			cmd.render(img.buffer_to_wsi_screen_fbs.at(swapchain_img), {{0, 0}, {1600, 900}},
				[&](auto &cmd){
					cmd.bind(m_diffuse_to_wsi_screen);
					cmd.bind(m_diffuse_to_wsi_screen, img.diffuse_to_wsi_screen_set, 0);
					cmd.draw(instance.screen_quad);
				}
			);

			cmd.memoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::BottomOfPipe, {},
				sb::Access::ColorAttachmentWrite, sb::Access::MemoryRead);
		});

		instance.cur_img_res->transfer_unsafe.end();

		auto t_before_submit = std::chrono::high_resolution_clock::now();

		if (last_frame) {
			auto img_wait = std::pair {&img.swapchain_img_avail, sb::PipelineStage::ColorAttachmentOutput};
			auto last_render_wait = std::pair {&last_frame->render_done, sb::PipelineStage::TopOfPipe};
			instance.graphics.submit(img.render_done_fence,
				std::array{&img_wait, &last_render_wait},
				std::array{&instance.cur_img_res->transfer_cmd_buf, &img.cmd_prim},
				img.render_done);
		} else
			instance.graphics.submit(img.render_done_fence,
				std::pair {&img.swapchain_img_avail, sb::PipelineStage::ColorAttachmentOutput},
				std::array{&instance.cur_img_res->transfer_cmd_buf, &img.cmd_prim},
				img.render_done);

		auto t_before_present = std::chrono::high_resolution_clock::now();
		instance.graphics.present(img.render_done, instance.swapchain.images().at(swapchain_img));

		auto t_next_frame = std::chrono::high_resolution_clock::now();
		last_frame = &img;
		instance.nextFrame();
		auto &next_img = images.at(instance.cur_img);
		next_img.render_done_fence.wait();
		next_img.render_done_fence.reset();
		instance.cur_img_res->resetStagingOff();
		instance.cur_img_res->transfer_unsafe.begin(sb::CommandBuffer::Usage::OneTimeSubmit);

		auto t_end = std::chrono::high_resolution_clock::now();

		static_cast<void>(t_start);
		static_cast<void>(t_before_ac);
		static_cast<void>(t_begin_record);
		static_cast<void>(t_before_submit);
		static_cast<void>(t_before_present);
		static_cast<void>(t_next_frame);
		static_cast<void>(t_end);
		/*std::cout << "before_ac: " << std::chrono::duration_cast<std::chrono::duration<double>>(t_before_ac - t_start).count() <<
		", rec: " << std::chrono::duration_cast<std::chrono::duration<double>>(t_before_submit - t_begin_record).count() <<
		", submit: " << std::chrono::duration_cast<std::chrono::duration<double>>(t_before_present - t_before_submit).count() <<
		", present: " << std::chrono::duration_cast<std::chrono::duration<double>>(t_next_frame - t_before_present).count() <<
		", next_frame: " << std::chrono::duration_cast<std::chrono::duration<double>>(t_end - t_next_frame).count() <<
		", FRAME_LEN: " << std::chrono::duration_cast<std::chrono::duration<double>>(t_end - t_start).count() << std::endl;*/
	}
}

}