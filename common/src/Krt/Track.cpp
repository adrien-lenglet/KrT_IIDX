#include "Track.hpp"
#include "Subtile/Binding.hpp"
#include <glm/gtx/transform.hpp>

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

void Track::Render::render(sb::CommandBuffer::Record::RenderPass &cmd)
{
	const double ang_rad = sb::pi / 180.0;

	const double near = 0.1, far = 1000.0,
	ratio = static_cast<double>(m_instance.swapchain->extent().x) / static_cast<double>(m_instance.swapchain->extent().y),
	fov = 120.0 * ang_rad;
	auto proj = glm::perspectiveLH_ZO<float>(fov, ratio, near, far);
	proj[1][1] *= -1.0;

	//auto view = glm::lookAtLH(glm::vec3(0.0, 0.0, -7.0), glm::vec3(0.0), glm::vec3(0.0, 1.0, 0.0));
	auto cursor = m_instance.surface->cursor() - base_cursor;
	const float sensi = 0.1;
	const float move = 2.0;
	auto view_rot = glm::rotate(static_cast<float>(-cursor.x * ang_rad) * sensi, glm::vec3(0.0, 1.0, 0.0));
	view_rot = glm::rotate(static_cast<float>(std::clamp(-cursor.y * sensi, -90.0, 90.0) * ang_rad), glm::vec3(1.0, 0.0, 0.0)) * view_rot;
	auto view_rot_inverse = glm::inverse(view_rot);
	auto dir_fwd_w = view_rot_inverse * glm::vec4(0.0, 0.0, 1.0, 0.0);
	auto dir_fwd = glm::vec3(dir_fwd_w.x, dir_fwd_w.y, dir_fwd_w.z);
	auto dir_side_w = view_rot_inverse * glm::vec4(1.0, 0.0, 0.0, 0.0);
	auto dir_side = glm::vec3(dir_side_w.x, dir_side_w.y, dir_side_w.z);
	auto &w = m_instance.surface->buttonsId().at("KB_W");
	w->update();
	auto &s = m_instance.surface->buttonsId().at("KB_S");
	s->update();
	auto &a = m_instance.surface->buttonsId().at("KB_A");
	a->update();
	auto &d = m_instance.surface->buttonsId().at("KB_D");
	d->update();
	static auto time_before = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	double delta_time = std::chrono::duration<double>(now - time_before).count();
	time_before = now;
	if (w->state())
		camera_pos += dir_fwd * move * static_cast<float>(delta_time);
	if (s->state())
		camera_pos -= dir_fwd * move * static_cast<float>(delta_time);
	if (a->state())
		camera_pos -= dir_side * move * static_cast<float>(delta_time);
	if (d->state())
		camera_pos += dir_side * move * static_cast<float>(delta_time);
	auto view = view_rot * glm::translate(-camera_pos);

	camera.vp = proj * view;
	camera.view = view;
	camera.view_normal = view;
	for (size_t i = 0; i < 3; i++)
		camera.view_normal[3][i] = 0.0f;
	camera.proj = proj;
	camera.inv_proj = glm::inverse(proj);
	camera.near = near;
	camera.far = far;
	camera.a = far / (far - near);
	camera.b = -(far * near) / (far - near);
	camera.ratio = glm::vec2(ratio, -1.0) * glm::vec2(std::tan(fov / 2.0));
	m_instance.cur_img_res->uploadDescSet(camera);
	static_cast<sb::RenderList&>(*this).draw(cmd);
}

}