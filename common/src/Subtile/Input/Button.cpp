#include "Button.hpp"

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
	static_cast<void>(input);
	return false;
}

Observer<bool>::Listener Button::listen(const std::function<void (bool)> &callback)
{
	return m_observer.listen(callback);
}

}
}