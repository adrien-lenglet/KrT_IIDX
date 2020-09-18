#include <chrono>
#include <thread>
#include "Race.hpp"
#include "res.resdecl.hpp"

namespace Krt {

Race::Race(Instance &instance) :
	instance(instance),

	m_sampler(instance.device.sampler(sb::Filter::Linear, sb::Filter::Nearest, sb::Sampler::AddressMode::MirroredRepeat, sb::BorderColor::FloatOpaqueWhite, std::nullopt, sb::Sampler::MipmapMode::Linear, 0.0f, 64.0f, 0.0f, std::nullopt)),
	m_sampler_clamp(instance.device.sampler(sb::Filter::Linear, sb::Filter::Linear, sb::Sampler::AddressMode::ClampToEdge, sb::BorderColor::FloatOpaqueWhite, std::nullopt, sb::Sampler::MipmapMode::Nearest, 0.0f, 64.0f, 0.0f, std::nullopt)),
	m_sampler_nearest(instance.device.sampler(sb::Filter::Nearest, sb::Filter::Nearest, sb::Sampler::AddressMode::ClampToEdge, sb::BorderColor::FloatOpaqueWhite, std::nullopt, sb::Sampler::MipmapMode::Nearest, 0.0f, 64.0f, 0.0f, std::nullopt)),
	m_fb_sampler(instance.device.samplerUnnormalized(sb::Filter::Nearest, sb::Sampler::AddressMode::ClampToEdge, sb::BorderColor::FloatOpaqueWhite, 0.0f)),
	m_fb_sampler_linear(instance.device.samplerUnnormalized(sb::Filter::Linear, sb::Sampler::AddressMode::ClampToEdge, sb::BorderColor::FloatOpaqueWhite, 0.0f)),
	m_opaque_pass(instance.device.load(res.shaders().render_passes().opaque())),
	m_lighting_pass(instance.device.load(res.shaders().render_passes().lighting())),
	m_depth_range_pass(instance.device.load(res.shaders().render_passes().depth_range())),
	m_first_depth_range(instance.device.load(res.shaders().first_depth_range())),
	m_compute_depth_range(instance.device.load(res.shaders().compute_depth_range())),
	m_depth_buffer_module(instance.device.load(res.shaders().modules().depth_buffer())),
	m_depth_to_fl_pass(instance.device.load(res.shaders().render_passes().depth_to_fl())),
	m_depth_to_fl_shader(instance.device.load(res.shaders().depth_to_fl())),
	m_diffuse_bounce_pass(instance.device.load(res.shaders().render_passes().diffuse_bounce())),
	m_diffuse_bounce_shader(instance.device.load(res.shaders().diffuse_bounce())),
	m_gather_bounces_pass(instance.device.load(res.shaders().render_passes().gather_bounces())),
	m_gather_bounces_shader(instance.device.load(res.shaders().gather_bounces())),
	m_buffer_to_wsi_screen(instance.device.load(res.shaders().render_passes().buffer_to_wsi_screen())),
	m_diffuse_to_wsi_screen(instance.device.load(res.shaders().diffuse_to_wsi_screen())),
	m_lighting_shader(instance.device.load(res.shaders().lighting())),
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
	auto &esc = *instance.surface->buttonsId().at("KB_ESCAPE");
	bool cursor_mode = false;
	while (!m_is_done) {
		auto t_start = std::chrono::high_resolution_clock::now();

		instance.scanInputs();
		m_track->events.updateEvents();
		esc.update();
		if (esc.released()) {
			cursor_mode = !cursor_mode;
			m_track->render.base_cursor = instance.surface->cursor();
			instance.surface->cursorMode(cursor_mode);
			if (!cursor_mode)
				m_track->render.base_cursor = instance.surface->cursor();
		}
		if (instance.surface->shouldClose())
			break;

		auto resized = instance.surface->resized();
		if (resized) {
			instance.graphics.waitIdle();
			images.clear();
			instance.swapchain.reset();
			/*instance.surface.reset();
			instance.surface = static_cast<sb::InstanceBase&>(instance).surface(*resized, "SUNREN®");
			instance.device.newSurface(*instance.surface);*/
			while (resized->x * resized->y == 0) {
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				instance.scanInputs();
				resized = instance.surface->resized();
			}
			instance.swapchain = instance.device.swapchain(*instance.surface, instance.surface->extent(), 2, sb::Image::Usage::ColorAttachment, instance.graphics);
			images = getImages();
			last_frame = nullptr;
		}
		auto &img = images.at(instance.cur_img);

		auto t_before_ac = std::chrono::high_resolution_clock::now();
		auto swapchain_img = instance.swapchain->acquireNextImage(img.swapchain_img_avail);
		auto t_begin_record = std::chrono::high_resolution_clock::now();

		img.cmd_prim.record([&](auto &cmd){
			cmd.memoryBarrier(sb::PipelineStage::Transfer, sb::PipelineStage::AllGraphics, {},
				sb::Access::TransferWrite, sb::Access::MemoryRead);

			auto srgb_lin = [](double val){
				constexpr float unorm = 1.0 / 255.0;

				return std::pow(val * unorm, 2.2);
			};

			auto viewport = sb::rect2({0.0f, 0.0f}, {instance.swapchain->extent().x, instance.swapchain->extent().y});

			cmd.setViewport(viewport, 0.0f, 1.0f);
			cmd.setScissor({{0, 0}, instance.swapchain->extent()});
			cmd.render(img.opaque_fb, {{0, 0}, instance.swapchain->extent()},
				sb::Color::f32(0.0f), sb::Color::f32(srgb_lin(2.0), srgb_lin(145.0), srgb_lin(223.0), 0.0f), sb::Color::f32(0.0f), 1.0f,

				[&](auto &cmd){
					auto &cam = m_track->render.camera;
					auto &s = img.gather_bounces_set;
					s.last_cam_proj = cam.proj;
					glm::mat4 last_view = cam.view;
					glm::vec3 last_pos = m_track->render.camera_pos;
					m_track->render.render(cmd, cursor_mode);
					glm::mat4 view = cam.view;

					auto view_to_last = last_view * glm::inverse(view);
					auto view_to_last_normal = view_to_last;
					for (size_t i = 0; i < 3; i++)
						view_to_last_normal[3][i] = 0.0f;
					s.cur_cam_delta = m_track->render.camera_pos - last_pos;
					s.cur_cam_to_last = view_to_last;
					s.cur_cam_a = cam.a;
					s.cur_cam_b = cam.b;
					s.cur_cam_ratio = cam.ratio;
					instance.cur_img_res->uploadDescSet(s);
				}
			);

			cmd.memoryBarrier(sb::PipelineStage::ColorAttachmentOutput | sb::PipelineStage::LateFragmentTests, sb::PipelineStage::FragmentShader, {},
				sb::Access::ColorAttachmentWrite | sb::Access::DepthStencilAttachmentWrite, sb::Access::ShaderRead);

			{
				size_t ndx = 0;
				for (auto &mip : img.fb_depth_buffer_fl_mips) {
					auto ex = mip.img.extent();
					cmd.setViewport({{0.0f, 0.0f}, {ex.x, ex.y}}, 0.0f, 1.0f);
					cmd.setScissor({{0, 0}, ex});
					cmd.render(mip.fb, {{0, 0}, ex},
						[&](auto &cmd){
							if (ndx == 0) {
								cmd.bind(m_first_depth_range);
								cmd.bind(m_first_depth_range, img.first_depth_range_in_fb, 0);
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

			for (auto &d : img.lighting_samplers.sun_dir)
				d = sb::genDiffuseVector(*m_track, glm::normalize(glm::vec3(1.0, 1.0, 1.0)), 2000.0);
			instance.cur_img_res->uploadDescSet(img.lighting_samplers);

			cmd.setViewport(viewport, 0.0f, 1.0f);
			cmd.setScissor({{0, 0}, instance.swapchain->extent()});
			cmd.render(img.lighting_fb, {{0, 0}, instance.swapchain->extent()},
				[&](auto &cmd){
					cmd.bind(m_lighting_shader);
					cmd.bind(m_lighting_shader, img.lighting_samplers, 0);
					cmd.bind(m_lighting_shader, m_track->render.camera, 1);
					cmd.draw(instance.screen_quad);
				}
			);

			cmd.memoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::FragmentShader, {},
				sb::Access::ColorAttachmentWrite, sb::Access::ShaderRead);

			for (auto &normal : img.diffuse_bounce_random.normals)
				normal = sb::genDiffuseVector(*m_track, glm::vec3(0.0, 0.0, 1.0), 1.0);
			instance.cur_img_res->uploadDescSet(img.diffuse_bounce_random);

			for (auto &b : img.diffuse_bounces) {
				cmd.render(b.fb, {{0, 0}, instance.swapchain->extent()},
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

			cmd.render(img.gather_bounces_fb, {{0, 0}, instance.swapchain->extent()},
				[&](auto &cmd){
					cmd.bind(m_gather_bounces_shader);
					cmd.bind(m_gather_bounces_shader, img.gather_bounces_set, 0);
					cmd.draw(instance.screen_quad);
				}
			);

			cmd.memoryBarrier(sb::PipelineStage::ColorAttachmentOutput, sb::PipelineStage::FragmentShader, {},
				sb::Access::ColorAttachmentWrite, sb::Access::ShaderRead);

			cmd.render(img.buffer_to_wsi_screen_fbs.at(swapchain_img), {{0, 0}, instance.swapchain->extent()},
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
		instance.graphics.present(img.render_done, instance.swapchain->images().at(swapchain_img));
		img.ever_rendered = true;

		auto t_next_frame = std::chrono::high_resolution_clock::now();
		last_frame = &img;
		instance.nextFrame();
		auto &next_img = images.at(instance.cur_img);
		if (next_img.ever_rendered) {
			next_img.render_done_fence.wait();
			next_img.render_done_fence.reset();
		}
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