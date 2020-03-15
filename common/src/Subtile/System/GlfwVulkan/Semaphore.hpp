#pragma once

#include <vulkan/vulkan.h>

#include "Dep/Device.hpp"

namespace Subtile {
namespace Vk {

class Semaphore : public Dep::Device
{
public:
	Semaphore(VkDevice dev);
	Semaphore(Semaphore &&other);
	~Semaphore(void);

	VkSemaphore semaphore;

private:
	VkSemaphore createSemaphore(void);
};

}
}