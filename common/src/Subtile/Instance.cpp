#include "Instance.hpp"

namespace Subtile {

Instance::Instance(size_t w, size_t h, bool isDebug, bool isProfile) :
	vk(w, h, isDebug, isProfile)
{
}

Instance::~Instance(void)
{
}

void Instance::run(void)
{
	while (true) {
		glfwPollEvents();
		if (vk.context.shouldClose())
			break;
		vk.renderer.render();
	}
}

}