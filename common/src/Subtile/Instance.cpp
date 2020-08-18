#include "Instance.hpp"
#include "System/Input/IButton.hpp"
#include "System/Input/IKeyboard.hpp"
#include "System/Vk.hpp"

namespace Subtile {

InstanceBase::InstanceBase(const std::string &name, bool isDebug, bool isProfile) :
	m_system(new System::Vk(*this, name, isDebug, isProfile)),
	m_events(*m_system)
{
}

InstanceBase::~InstanceBase(void)
{
}

void InstanceBase::setInputs(const std::function<void (const Event::System::Observer::Input::Setter &setter)> &binder)
{
	return m_events.input.set(binder);
}

ISystem& InstanceBase::system(void)
{
	return *m_system;
}

}