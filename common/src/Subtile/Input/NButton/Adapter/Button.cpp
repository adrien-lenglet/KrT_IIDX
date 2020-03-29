#include "Button.hpp"

namespace Subtile {
namespace Input {
namespace NButton {
namespace Adapter {

Button::Button(System::Input::IButton &input) :
	m_input(input)
{
}

Button::~Button(void)
{
}

bool Button::read(void)
{
	return m_input.getState();
}

}
}
}
}