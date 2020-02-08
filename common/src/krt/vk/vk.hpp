#pragma once

#include <vector>
#include <string>

#include <vulkan/vulkan.h>
#include "vk_mem_alloc.h"

class Vk;

#include "context.hpp"
#include "queue.hpp"
#include "device.hpp"
#include "swapchain.hpp"
#include "semaphore.hpp"

void vkAssert_real(VkResult res, const char *file, int line, const char *fun);
#define vkAssert(res) vkAssert_real(res, __FILE__, __LINE__, __func__)

class Vk
{
public:
	Vk(bool doProfile);
	~Vk(void);

	Context context;
	Device device;
	Queues queues;
	Swapchain swapchain;

private:
};
