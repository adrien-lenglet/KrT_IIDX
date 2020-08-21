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

	auto sec = m_cmd_pool.secondary();
	sec.record([](auto&){});

	auto prim = m_cmd_pool.primary();
	prim.record([&](decltype(prim)::Record &cmd){
		cmd.execute(sec);
	});

	auto image2D = m_instance.image2D(sb::Format::bgra8_srgb, sb::Image::Sample::Count1, {800, 600}, sb::Image::Usage::InputAttachment | sb::Image::Usage::ColorAttachment, m_instance.graphics);

	//cmd_buf.renderPass();

	/*cmd_buf [prim / sec]
		-> record [prim / sec, outside]
			-> renderPass [prim, inside]

		-> recordRenderPass [sec, inside]*/
}

}