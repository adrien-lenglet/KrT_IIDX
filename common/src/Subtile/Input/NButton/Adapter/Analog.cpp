#include "Analog.hpp"

namespace Subtile {
namespace Input {
namespace NButton {
namespace Adapter {

Analog::Analog(System::Input::IAnalog &input, double threshold) :
	m_input(input),
	m_threshold(threshold)
{
}

Analog::~Analog(void)
{
}

bool Analog::read(void)
{
	return m_input.getState() >= m_threshold;
}

}
}
}
}