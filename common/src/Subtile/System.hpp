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
	class Input : public Event::Observer
	{
	public:
		virtual void update(void) override = 0;

		virtual const std::string& getName(void) const = 0;
		virtual double getActivity(void) const = 0;

		class Analog;
		class Button;
		class Keyboard;
	};

	virtual ~System(void) = default;

	virtual void scanInputs(void) = 0;
	virtual const std::map<std::string, System::Input&>& getInputs(void) = 0;

	virtual std::unique_ptr<Surface> createSurface(const svec2 &extent, const std::string &title) = 0;
	virtual std::unique_ptr<Device> createDevice(Surface &surface, const sb::Queue::Set &queues) = 0;
};

class System::Input::Analog : public System::Input
{
public:
	virtual double getState(void) const = 0;
};

class System::Input::Button : public System::Input
{
public:
	virtual bool getState(void) const = 0;
};

class System::Input::Keyboard : public System::Input
{
public:
	virtual std::vector<uint32_t> poll(void) const = 0;
};

}