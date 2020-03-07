#include <iostream>
#include "Instance.hpp"

namespace Vk {

Instance::Instance(bool doProfile) :
	context(1600, 900, doProfile),
	device(context.instance, context.surface),
	queues(device),
	swapchain(context.surface, device, queues.graphics.commandPool),
	renderer(swapchain)
{
	std::cout << "Vk init done." << std::endl;
}

Instance::~Instance(void)
{
}

}