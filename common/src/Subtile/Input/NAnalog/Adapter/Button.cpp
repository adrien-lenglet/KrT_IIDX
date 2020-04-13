#include "Button.hpp"

namespace Subtile {
namespace Input {
namespace NAnalog {
namespace Adapter {

Button::Button(System::Input::IButton &input, double min, double max) :
	m_input(input),
	m_min(min),
	m_max(max)
{
}

Button::~Button(void)
{
}

double Button::read(void)
{
	m_input.update();
	return m_input.getState() ? m_max : m_min;
}

}
}
}
}