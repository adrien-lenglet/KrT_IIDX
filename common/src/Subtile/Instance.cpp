#include "Instance.hpp"

namespace Subtile {

Instance::Instance(size_t w, size_t h, bool isDebug, bool isProfile)
{
	static_cast<void>(w);
	static_cast<void>(h);
	static_cast<void>(isDebug);
	static_cast<void>(isProfile);
}

Instance::~Instance(void)
{
}

void Instance::run(void)
{
	/*while (true) {
		glfwPollEvents();
		if (vk.shouldClose())
			break;
		vk.render();
	}*/
}

}