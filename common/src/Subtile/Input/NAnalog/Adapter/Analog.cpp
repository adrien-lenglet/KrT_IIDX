#include "Analog.hpp"

namespace Subtile {
namespace Input {
namespace NAnalog {
namespace Adapter {

Analog::Analog(System::Input::IAnalog &input, double min, double max) :
	m_input(input),
	m_min(min),
	m_max(max)
{
}

Analog::~Analog(void)
{
}

double Analog::read(void)
{
	return m_min + m_input.getState() * (m_max - m_min);
}

}
}
}
}