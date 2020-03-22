#include "Instance.hpp"
#include "System/CGlfwVulkan.hpp"

namespace Subtile {

Instance::Instance(size_t w, size_t h, bool isDebug, bool doProfile) :
	m_system(new System::CGlfwVulkan(w, h, isDebug, doProfile))
{
}

Instance::~Instance(void)
{
}

void Instance::run(void)
{
	while (true) {
		m_system->scanInputs();
		if (m_system->getInputs().at("close_window").isActive())
			break;
		m_system->render();
	}
}

}