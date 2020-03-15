#include "Semaphore.hpp"
#include "Misc.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {

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
	Dep::VulkanDevice(dev),
	semaphore(createSemaphore())
{
}

Semaphore::Semaphore(Semaphore &&other) :
	Dep::VulkanDevice(other.getDevice()),
	semaphore(other.semaphore)
{
	other.semaphore = VK_NULL_HANDLE;
}

Semaphore::~Semaphore(void)
{
	vkDestroySemaphore(getDevice(), semaphore, nullptr);
}

}
}
}