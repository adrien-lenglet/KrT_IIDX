#include <optional>
#include <bitset>
#include <iostream>
#include <exception>

#include "Queue.hpp"
#include "Misc.hpp"

namespace Vk {

VkCommandPool Queue::createCommandPool(void)
{
	VkCommandPool res;
	VkCommandPoolCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	createInfo.queueFamilyIndex = queueFamilyIndex;

	vkAssert(vkCreateCommandPool(getDevice(), &createInfo, nullptr, &res));

	return res;
}

Queue::Queue(::Vk::Device &dev, uint32_t queueFamilyIndex) :
	Dep::Device(dev.device),
	queueFamilyIndex(queueFamilyIndex),
	queue(dev.getQueue(queueFamilyIndex, 0)),
	commandPool(createCommandPool())
{
}

Queue::~Queue(void)
{
	vkDestroyCommandPool(getDevice(), commandPool, nullptr);
}

Queues::Queues(Device &dev) :
	present(Queue(dev, dev.queueFamilies.getIndexPresent())),
	graphics(Queue(dev, dev.queueFamilies.getIndex(VK_QUEUE_GRAPHICS_BIT))),
	transfer(Queue(dev, dev.queueFamilies.getIndex(VK_QUEUE_TRANSFER_BIT)))
{
}

Queues::~Queues(void)
{
}

}