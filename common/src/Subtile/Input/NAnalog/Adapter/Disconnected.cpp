#include "Disconnected.hpp"

namespace Subtile {
namespace Input {
namespace NAnalog {
namespace Adapter {

Disconnected::Disconnected(double value) :
	m_value(value)
{
}

Disconnected::~Disconnected(void)
{
}

double Disconnected::read(void)
{
	return m_value;
}

}
}
}
}