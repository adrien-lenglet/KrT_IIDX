#include "Krt.hpp"
#include "Krt/EntityTest.hpp"
#include "Krt/Track.hpp"
#include "Krt/Race.hpp"
#include "util.hpp"

#include <iostream>

namespace Krt {

decltype(Instance::m_screen_quad_buffer) Instance::createScreenQuadBuffer(void)
{
	std::array vertices {
		glm::vec2(-1, -1),
		glm::vec2(1, -1),
		glm::vec2(1, 1),

		glm::vec2(-1, -1),
		glm::vec2(1, 1),
		glm::vec2(-1, 1)
	};
	std::vector<decltype(m_screen_quad_buffer)::value_type> values;
	for (auto &v : vertices) {
		decltype(m_screen_quad_buffer)::value_type cur;
		cur.pos = v;
		values.emplace_back(cur);
	}

	auto res = vertexBuffer<decltype(m_screen_quad_buffer)::value_type>(values.size(), graphics);
	cur_img_res->copyBuffer(values, res);
	return res;
}

Instance::Instance(bool isDebug, const std::vector<std::string> &args) :
	sb::Instance<Instance>(isDebug, Config(args).isProfile, {
		{m_graphics_family, {1.0f}}
	}),
	graphics(queue<m_graphics_family>(0)),
	m_transfer_pool(graphics.pool<true>()),
	surface(static_cast<sb::InstanceBase&>(*this).surface({1600, 900}, "SUNREN®")),
	swapchain(surface.swapchain({1600, 900}, 2, sb::Image::Usage::ColorAttachment, graphics)),
	img_count(std::max(swapchain.images().size(), static_cast<size_t>(2))),
	images(createImages()),
	cur_img(0),
	cur_img_res(&images.at(cur_img)),
	m_screen_quad_buffer((cur_img_res->transfer_unsafe.begin(sb::CommandBuffer::Usage::OneTimeSubmit), createScreenQuadBuffer())),
	screen_quad(model(m_screen_quad_buffer))
{
}

Instance::~Instance(void)
{
}

void Instance::run(void)
{
	setInputs([](const auto &s){
		s.addButton("quit");
	});

	auto race = Race(*this);
	race.run();
}

Config::Config(const std::vector<std::string> &argsRo)
{
	auto args = argsRo;

	if (util::erase_if_contains(args, "-p"))
		isProfile = true;
	if (util::erase_if_contains(args, "--profile"))
		isProfile = true;

	if (!args.empty())
		throw std::runtime_error(std::string("Unknown argument(s): " + util::join(args, std::string(", "))));
}

Config::~Config(void)
{
}

}