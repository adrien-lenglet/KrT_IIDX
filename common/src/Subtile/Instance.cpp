#include "Instance.hpp"
#include "System/Input/IButton.hpp"
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
	auto &close_button = dynamic_cast<const System::Input::IButton&>(m_system->getInputs().at("close_window"));

	while (true) {
		m_system->scanInputs();
		if (close_button.isPressed())
			break;
		m_system->render();
	}
}

}