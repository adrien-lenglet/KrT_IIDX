#pragma once

#include <vulkan/vulkan.h>

#include "Dep/Device.hpp"

namespace Subtile {
namespace Vk {

class Fence : public Dep::Device
{
public:
	Fence(VkDevice dev);
	Fence(Fence &&other);
	~Fence(void);

	VkFence fence;

private:
	VkFence createFence(void);
};

}
}