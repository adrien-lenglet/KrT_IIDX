#include "Track.hpp"
#include "Subtile/Binding.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <array>

#include <glm/gtx/projection.hpp>

namespace Krt {

Track::Track(void) :
	render(instance),
	entity(add<EntityTest>())
{
	bind(entity.just_died, [](const double &){
		//std::cout << "Just died event: " << val << std::endl;
	});

	bind(entity.got_score, [this](const size_t &){
		//std::cout << "Got score event: " << score << std::endl;
		trigger(done);
	});
}

Track::~Track(void)
{
	destroy_children();
}

void Track::Render::render(void)
{
	auto mat = glm::perspectiveLH_NO<float>(90.0, 16.0 / 9.0, 0.1, 1000.0);
	mat *= glm::lookAtLH(glm::vec3(0.0, 0.0, -7.0), glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));
	camera.vp = mat;
	camera.upload();
	static_cast<sb::Render::Pass&>(*this).render();

	m_render_done_fence.wait();
	m_render_done_fence.reset();

	auto img = m_instance.swapchain.acquireNextImage(m_swapchain_img_avail);

	m_cmd_sec.recordRender<decltype(m_render_pass)::Subpass::albedo>(m_framebuffers.at(img), [](auto&){
	});

	m_cmd_prim.record([&](auto &cmd){
		cmd.render(m_framebuffers.at(img), {{0, 0}, {1600, 900}},
			sb::Color::f32(0.5f), sb::Color::f32(0.0f), 1.0f,

			m_cmd_sec,
			[](auto&){
			}
		);
	});

	m_instance.graphics.submit(m_render_done_fence, std::pair {&m_swapchain_img_avail, sb::PipelineStage::ColorAttachmentOutput}, m_cmd_prim, m_render_done);
	m_instance.graphics.present(m_render_done, m_instance.swapchain.images().at(img));
}

}