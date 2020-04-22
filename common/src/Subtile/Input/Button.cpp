#include "Button.hpp"
#include "NButton/Adapter/Disconnected.hpp"
#include "NButton/Adapter/Analog.hpp"
#include "NButton/Adapter/Button.hpp"

namespace Subtile {
namespace Input {

Button::Button(bool isStrict, double analogThreshold) :
	m_is_strict(isStrict),
	m_analog_threshold(analogThreshold),
	m_adapter(new NButton::Adapter::Disconnected()),
	m_last_state(false),
	m_state(false)
{
	update();
}

Button::~Button(void)
{
}

void Button::update(void)
{
	m_last_state = m_state;
	m_state = m_adapter->read();
}

bool Button::getState(void) const
{
	return m_state;
}

bool Button::isPressed(void) const
{
	return !m_last_state && m_state;
}

bool Button::isReleased(void) const
{
	return m_last_state && !m_state;
}

bool Button::bind(System::IInput &input)
{
	if (!m_is_strict) {
		try {
			m_adapter.reset(new NButton::Adapter::Analog(dynamic_cast<System::Input::IAnalog&>(input), m_analog_threshold));
			return true;
		} catch (const std::bad_cast&) {
		}
	}
	try {
		m_adapter.reset(new NButton::Adapter::Button(dynamic_cast<System::Input::IButton&>(input)));
		return true;
	} catch (const std::bad_cast&) {
	}
	return false;
}

}
}