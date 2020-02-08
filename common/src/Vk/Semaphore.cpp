#include "Semaphore.hpp"
#include "Vk/Misc.hpp"

namespace Vk {

VkSemaphore Semaphore::createSemaphore(void)
{
	VkSemaphore res;
	VkSemaphoreCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;

	vkAssert(vkCreateSemaphore(getDevice(), &createInfo, nullptr, &res));

	return res;
}

Semaphore::Semaphore(VkDevice dev) :
	Dep::Device(dev),
	semaphore(createSemaphore())
{
}

Semaphore::Semaphore(Semaphore &&other) :
	Dep::Device(other.getDevice()),
	semaphore(other.semaphore)
{
	other.semaphore = VK_NULL_HANDLE;
}

Semaphore::~Semaphore(void)
{
	vkDestroySemaphore(getDevice(), semaphore, nullptr);
}

}