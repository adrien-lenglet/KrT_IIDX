#include "Instance.hpp"
#include "System/Input/IButton.hpp"
#include "System/Input/IKeyboard.hpp"
#include "System/Vk.hpp"

namespace Subtile {

Instance::Instance(void) :
	m_system(new System::Vk()),
	m_events(*m_system)
{
}

Instance::~Instance(void)
{
}

void Instance::setInputs(const std::function<void (const Event::System::Observer::Input::Setter &setter)> &binder)
{
	return m_events.input.set(binder);
}

}