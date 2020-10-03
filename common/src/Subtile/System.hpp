#pragma once

#include <vector>
#include <string>
#include <map>
#include <optional>
#include "../Subtile.hpp"
#include "Shader.hpp"
#include "Image.hpp"
#include "Swapchain.hpp"
#include "Semaphore.hpp"
#include "Fence.hpp"
#include "Buffer.hpp"
#include "Queue.hpp"
#include "Surface.hpp"
#include "Device.hpp"
#include "Event/Observer.hpp"

namespace Subtile {

class System
{
public:
	virtual ~System(void) = default;

	virtual void scanInputs(void) = 0;

	virtual std::unique_ptr<Surface> createSurface(const svec2 &extent, const std::string &title) = 0;
	virtual const std::vector<Monitor::Handle>& getMonitors(void) const = 0;
	virtual std::unique_ptr<Device> createDevice(Surface &surface, const sb::Queue::Set &queues) = 0;
};

}