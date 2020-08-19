#include "Input.hpp"

namespace Subtile {

Input::Button::Button(bool isStrict, double analogThreshold) :
	m_is_strict(isStrict),
	m_analog_threshold(analogThreshold),
	m_adapter(new Button::IAdapter::Disconnected()),
	m_last_state(false),
	m_state(false)
{
	update();
}

Input::Button::~Button(void)
{
}

void Input::Button::update(void)
{
	m_last_state = m_state;
	m_state = m_adapter->read();
}

bool Input::Button::getState(void) const
{
	return m_state;
}

bool Input::Button::isPressed(void) const
{
	return !m_last_state && m_state;
}

bool Input::Button::isReleased(void) const
{
	return m_last_state && !m_state;
}

bool Input::Button::bind(System::Input &input)
{
	if (!m_is_strict) {
		try {
			m_adapter.reset(new Button::IAdapter::Analog(dynamic_cast<System::Input::Analog&>(input), m_analog_threshold));
			return true;
		} catch (const std::bad_cast&) {
		}
	}
	try {
		m_adapter.reset(new Button::IAdapter::Button(dynamic_cast<System::Input::Button&>(input)));
		return true;
	} catch (const std::bad_cast&) {
	}
	return false;
}

Input::Button::IAdapter::Analog::Analog(System::Input::Analog &input, double threshold) :
	m_input(input),
	m_threshold(threshold)
{
}

Input::Button::IAdapter::Analog::~Analog(void)
{
}

bool Input::Button::IAdapter::Analog::read(void)
{
	m_input.update();
	return m_input.getState() >= m_threshold;
}

Input::Button::IAdapter::Button::Button(System::Input::Button &input) :
	m_input(input)
{
}

Input::Button::IAdapter::Button::~Button(void)
{
}

bool Input::Button::IAdapter::Button::read(void)
{
	m_input.update();
	return m_input.getState();
}

Input::Button::IAdapter::Disconnected::Disconnected(void)
{
}

Input::Button::IAdapter::Disconnected::~Disconnected(void)
{
}

bool Input::Button::IAdapter::Disconnected::read(void)
{
	return false;
}

Input::Analog::Analog(double min, double max, bool isStrict, std::optional<double> def) :
	m_min(min),
	m_max(max),
	m_is_strict(isStrict),
	m_default(def ? *def : max * 0.5 + min * 0.5),
	m_adapter(new Analog::IAdapter::Disconnected(m_default)),
	m_value(m_default)
{
}

Input::Analog::~Analog(void)
{
}

void Input::Analog::update(void)
{
	m_value = m_adapter->read();
}

double Input::Analog::getState(void) const
{
	return m_value;
}

bool Input::Analog::bind(System::Input &input)
{
	if (!m_is_strict) {
		try {
			m_adapter.reset(new Analog::IAdapter::Button(dynamic_cast<System::Input::Button&>(input), m_min, m_max));
			return true;
		} catch (std::bad_cast&) {
		}
	}
	try {
		m_adapter.reset(new Analog::IAdapter::Analog(dynamic_cast<System::Input::Analog&>(input), m_min, m_max));
		return true;
	} catch (std::bad_cast&) {
	}
	return false;
}

Input::Analog::IAdapter::Analog::Analog(System::Input::Analog &input, double min, double max) :
	m_input(input),
	m_min(min),
	m_max(max)
{
}

Input::Analog::IAdapter::Analog::~Analog(void)
{
}

double Input::Analog::IAdapter::Analog::read(void)
{
	m_input.update();
	return m_min + m_input.getState() * (m_max - m_min);
}

Input::Analog::IAdapter::Button::Button(System::Input::Button &input, double min, double max) :
	m_input(input),
	m_min(min),
	m_max(max)
{
}

Input::Analog::IAdapter::Button::~Button(void)
{
}

double Input::Analog::IAdapter::Button::read(void)
{
	m_input.update();
	return m_input.getState() ? m_max : m_min;
}

Input::Analog::IAdapter::Disconnected::Disconnected(double value) :
	m_value(value)
{
}

Input::Analog::IAdapter::Disconnected::~Disconnected(void)
{
}

double Input::Analog::IAdapter::Disconnected::read(void)
{
	return m_value;
}

}