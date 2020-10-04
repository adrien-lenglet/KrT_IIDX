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

	auto res = device.vertexBuffer<decltype(m_screen_quad_buffer)::value_type>(values.size(), graphics);
	cur_img_res->copyBuffer(values, res);
	return res;
}

Instance::Instance(bool isDebug, const Config &config) :
	sb::Instance<Instance>((isDebug && !config.isNoValidation) || config.forceValidation, config.isRenderDoc, config.isMonitor),
	surface(static_cast<sb::InstanceBase&>(*this).surface({1600, 900}, "SUNREN®")),
	device(static_cast<sb::InstanceBase&>(*this).device(*surface, {
		{m_graphics_family, {1.0f}}
	})),
	graphics(device.queue<m_graphics_family>(0)),
	swap_imgs(2),
	swapchain(device.swapchain(*surface, surface->extent(), swap_imgs, sb::Image::Usage::ColorAttachment, graphics)),
	m_transfer_pool(graphics.pool<true>()),
	img_count(std::max(swapchain->images().size(), static_cast<size_t>(2))),
	images(createImages()),
	cur_img(0),
	cur_img_res(&images.at(cur_img)),
	m_screen_quad_buffer((cur_img_res->transfer_unsafe.begin(sb::CommandBuffer::Usage::OneTimeSubmit), createScreenQuadBuffer())),
	screen_quad(device.model(m_screen_quad_buffer))
{
}

Instance::Instance(bool isDebug, const std::vector<std::string> &args) :
	Instance(isDebug, Config(args))
{
}

Instance::~Instance(void)
{
}

void Instance::run(void)
{
	auto race = Race(*this);
	race.run();
}

Config::Config(const std::vector<std::string> &argsRo)
{
	auto args = argsRo;

	if (util::erase_if_contains(args, "-nv") || util::erase_if_contains(args, "--no-validation"))
		isNoValidation = true;
	if (util::erase_if_contains(args, "-fv") || util::erase_if_contains(args, "--force-validation"))
		forceValidation = true;
	if (util::erase_if_contains(args, "-rd") || util::erase_if_contains(args, "--render-doc"))
		isRenderDoc = true;
	if (util::erase_if_contains(args, "-m") || util::erase_if_contains(args, "--monitor"))
		isMonitor = true;

	if (!args.empty())
		throw std::runtime_error(std::string("Unknown argument(s): " + util::join(args, std::string(", "))));
}

Config::~Config(void)
{
}

}