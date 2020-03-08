#pragma once

#include "Context.hpp"
#include "Device.hpp"
#include "Queue.hpp"
#include "Swapchain.hpp"
#include "Renderer.hpp"

namespace Subtile {
namespace Vk {

class Instance
{
public:
	Instance(size_t w, size_t h, bool isDebug, bool doProfile);
	~Instance(void);

	Context context;
	Device device;
	Queues queues;
	Swapchain swapchain;
	Renderer renderer;
};

}
}