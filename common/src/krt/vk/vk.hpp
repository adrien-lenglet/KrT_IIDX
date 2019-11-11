
#pragma once

#include <vector>
#include <string>

#include <vulkan/vulkan.h>
#include "vk_mem_alloc.h"

class Vk;
class Krt;

#include "context.hpp"
#include "queue.hpp"
#include "device.hpp"
#include "swapchain.hpp"
#include "pipeline/pipeline.hpp"

void vkAssert_real(VkResult res, const char *file, int line, const char *fun);
#define vkAssert(res) vkAssert_real(res, __FILE__, __LINE__, __func__)

class Vk
{
public:
	Vk(Krt &krt);
	~Vk(void);

	Krt &krt;

	Context context;
	Device device;
	Queues queues;
	Swapchain swapchain;
	Pipeline pipeline;

private:
};
