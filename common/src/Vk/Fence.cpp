#include "Fence.hpp"
#include "Vk/Misc.hpp"

namespace Vk {

VkFence Fence::createFence(void)
{
	VkFence res;
	VkFenceCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	vkAssert(vkCreateFence(getDevice(), &createInfo, nullptr, &res));
	return res;
}

Fence::Fence(VkDevice dev) :
	Dep::Device(dev),
	fence(createFence())
{
}

Fence::Fence(Fence &&other) :
	Dep::Device(other.getDevice()),
	fence(other.fence)
{
	other.fence = VK_NULL_HANDLE;
}

Fence::~Fence(void)
{
	vkDestroyFence(getDevice(), fence, nullptr);
}

}