#include "AButton.hpp"

namespace Subtile {
namespace System {
namespace GlfwVulkan {
namespace Input {

AButton::AButton(const std::string &name, std::function<bool (void)> read_fun) :
	m_name(name),
	m_read_fun(read_fun),
	m_last_state(false),
	m_state(false)
{
}

AButton::~AButton(void)
{
}

const std::string& AButton::getName(void) const
{
	return m_name;
}

double AButton::getActivity(void) const
{
	return m_last_state != m_state ? 1.0 : 0.0;
}

bool AButton::getState(void) const
{
	return m_state;
}

void AButton::update(void)
{
	m_last_state = m_state;
	m_state = m_read_fun();
}

}
}
}
}