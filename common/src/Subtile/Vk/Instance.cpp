#include <iostream>
#include "Instance.hpp"

namespace Subtile {
namespace Vk {

Instance::Instance(size_t w, size_t h, bool isDebug, bool doProfile) :
	context(w, h, isDebug, doProfile),
	device(context.instance, context.surface),
	queues(device),
	swapchain(context.surface, device, queues.graphics),
	renderer(swapchain, queues.present)
{
}

Instance::~Instance(void)
{
	vkQueueWaitIdle(queues.transfer.queue);
	vkQueueWaitIdle(queues.graphics.queue);
	vkQueueWaitIdle(queues.present.queue);
}

}
}