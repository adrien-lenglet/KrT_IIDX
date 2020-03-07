#pragma once

#include "Context.hpp"
#include "Device.hpp"
#include "Queue.hpp"
#include "Swapchain.hpp"
#include "Renderer.hpp"

namespace Vk {

class Instance
{
public:
	Instance(bool doProfile);
	~Instance(void);

	Context context;
	Device device;
	Queues queues;
	Swapchain swapchain;
	Renderer renderer;
};

}