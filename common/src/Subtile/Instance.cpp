#include "Instance.hpp"
#include "System/Vk.hpp"

namespace Subtile {

InstanceBase::InstanceBase(bool isDebug, bool isProfile) :
	m_system(new Vk(*this, isDebug, isProfile)),
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

System& InstanceBase::system(void)
{
	return *m_system;
}

}