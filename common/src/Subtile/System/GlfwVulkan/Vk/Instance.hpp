#pragma once

#include "Context.hpp"
#include "Device.hpp"
#include "Queue.hpp"
#include "Swapchain.hpp"
#include "Renderer.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {

class Instance
{
public:
	Instance(size_t w, size_t h, bool isDebug, bool doProfile);
	~Instance(void);

	bool shouldClose(void);
	void render(void);
	GLFWwindow* getWindow(void) const { return m_context.window; };

private:
	Context m_context;
	Device m_device;
	Queues m_queues;
	Swapchain m_swapchain;
	Renderer m_renderer;
};

}
}
}