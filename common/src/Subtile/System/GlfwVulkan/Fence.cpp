#include "Fence.hpp"
#include "Misc.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {

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
	Dep::VulkanDevice(dev),
	fence(createFence())
{
}

Fence::Fence(Fence &&other) :
	Dep::VulkanDevice(other.getDevice()),
	fence(other.fence)
{
	other.fence = VK_NULL_HANDLE;
}

Fence::~Fence(void)
{
	vkDestroyFence(getDevice(), fence, nullptr);
}

}
}
}