#include "Instance.hpp"
#include "System/Vk.hpp"

namespace Subtile {

InstanceBase::InstanceBase(bool validate, bool isRenderDoc, bool isMonitor) :
	m_system(new Vk(validate, isRenderDoc, isMonitor))
{
}

InstanceBase::~InstanceBase(void)
{
}

}