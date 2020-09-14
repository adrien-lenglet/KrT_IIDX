#include "Instance.hpp"
#include "System/Vk.hpp"

namespace Subtile {

InstanceBase::InstanceBase(bool isDebug, bool isProfile) :
	m_system(new Vk(*this, isDebug, isProfile))
{
}

InstanceBase::~InstanceBase(void)
{
}

System& InstanceBase::system(void)
{
	return *m_system;
}

}