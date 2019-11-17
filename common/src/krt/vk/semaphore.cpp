
#include "vk.hpp"

VkSemaphore Semaphore::createSemaphore(void)
{
	VkSemaphore res;
	VkSemaphoreCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;

	vkAssert(vkCreateSemaphore(vk.device.device, &createInfo, nullptr, &res));

	return res;
}

Semaphore::Semaphore(Vk &vk) :
	vk(vk),
	semaphore(createSemaphore())
{
}

Semaphore::Semaphore(Semaphore &&that) :
	vk(that.vk),
	semaphore(that.semaphore)
{
	that.semaphore = VK_NULL_HANDLE;
}

Semaphore::~Semaphore(void)
{
	vkDestroySemaphore(vk.device.device, semaphore, nullptr);
}
