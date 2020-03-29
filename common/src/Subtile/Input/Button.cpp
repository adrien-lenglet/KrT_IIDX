#include "Button.hpp"
#include "NButton/Adapter/Disconnected.hpp"
#include "NButton/Adapter/Analog.hpp"
#include "NButton/Adapter/Button.hpp"

namespace Subtile {
namespace Input {

Button::Button(bool isStrict, double analogThreshold) :
	m_is_strict(isStrict),
	m_analog_threshold(analogThreshold),
	m_observer([this](auto &signal) {
		if (m_adapter)
			signal(m_adapter->read());
	})
{
}

Button::~Button(void)
{
}

void Button::update(void)
{
	m_observer.update();
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

}
}