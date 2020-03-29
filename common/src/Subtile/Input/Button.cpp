#include "Button.hpp"
#include "NButton/Adapter/Disconnected.hpp"
#include "NButton/Adapter/Analog.hpp"
#include "NButton/Adapter/Button.hpp"

namespace Subtile {
namespace Input {

Button::Button(bool isStrict, double analogThreshold) :
	m_is_strict(isStrict),
	m_analog_threshold(analogThreshold),
	m_last_state(false),
	m_state(false),
	m_observer([this](auto &signal) {
		if (m_adapter) {
			m_last_state = m_state;
			m_state = m_adapter->read();
			signal(m_state);
		}
	}),
	m_observer_pressed([this](auto &signal) {
		if (!m_last_state && m_state)
			signal();
	}),
	m_observer_released([this](auto &signal) {
		if (m_last_state && !m_state)
			signal();
	})
{
}

Button::~Button(void)
{
}

void Button::update(void)
{
	m_observer.update();
	m_observer_pressed.update();
	m_observer_released.update();
}

bool Button::bind(System::IInput &input)
{
	if (!m_is_strict) {
		try {
			m_adapter.reset(new NButton::Adapter::Analog(dynamic_cast<System::Input::IAnalog&>(input), m_analog_threshold));
			return true;
		} catch (std::bad_cast&) {
		}
	}
	try {
		m_adapter.reset(new NButton::Adapter::Button(dynamic_cast<System::Input::IButton&>(input)));
		return true;
	} catch (std::bad_cast&) {
	}
	return false;
}

Observer<bool>::Listener Button::listen(const std::function<void (bool)> &callback)
{
	return m_observer.listen(callback);
}

Observer<>::Listener Button::listenPressed(const std::function<void (void)> &callback)
{
	return m_observer_pressed.listen(callback);
}

Observer<>::Listener Button::listenReleased(const std::function<void (void)> &callback)
{
	return m_observer_released.listen(callback);
}

}
}