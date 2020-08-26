#include "Krt.hpp"
#include "Krt/EntityTest.hpp"
#include "Krt/Track.hpp"
#include "Krt/Race.hpp"
#include "util.hpp"

#include <iostream>

namespace Krt {

Instance::Instance(bool isDebug, const std::vector<std::string> &args) :
	sb::Instance<Instance>("SUNREN®", isDebug, Config(args).isProfile, {
		{m_graphics_family, {1.0f}}
	}),
	graphics(queue<m_graphics_family>(0)),
	swapchain(static_cast<sb::InstanceBase&>(*this).swapchain({1600, 900}, sb::Image::Usage::ColorAttachment, graphics)),
	m_transfer_pool(graphics.pool<true>()),
	m_transfer_cmd_buf(m_transfer_pool.primary()),
	transfer_unsafe(m_transfer_cmd_buf),
	transfer(m_transfer_cmd_buf),
	m_staging_buffer(mappableBuffer(256000000, sb::Buffer::Usage::TransferSrc | sb::Buffer::Usage::TransferDst, graphics))
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