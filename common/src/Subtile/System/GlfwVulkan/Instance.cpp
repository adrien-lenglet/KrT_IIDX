#include <iostream>
#include "Instance.hpp"

namespace Subtile {
namespace Vk {

Instance::Instance(size_t w, size_t h, bool isDebug, bool doProfile) :
	m_context(w, h, isDebug, doProfile),
	m_device(m_context.instance, m_context.surface),
	m_queues(m_device),
	m_swapchain(m_context.surface, m_device, m_queues.graphics),
	m_renderer(m_swapchain, m_queues.present)
{
}

Instance::~Instance(void)
{
	vkQueueWaitIdle(m_queues.transfer.queue);
	vkQueueWaitIdle(m_queues.graphics.queue);
	vkQueueWaitIdle(m_queues.present.queue);
}

bool Instance::shouldClose(void)
{
	return m_context.shouldClose();
}

void Instance::render(void)
{
	return m_renderer.render();
}

}
}