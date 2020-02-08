#pragma once

#include "Context.hpp"
#include "Device.hpp"
#include "Queue.hpp"
#include "Swapchain.hpp"

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

private:
};

}