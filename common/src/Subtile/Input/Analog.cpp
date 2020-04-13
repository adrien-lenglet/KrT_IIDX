#include "Analog.hpp"
#include "NAnalog/Adapter/Disconnected.hpp"
#include "NAnalog/Adapter/Analog.hpp"
#include "NAnalog/Adapter/Button.hpp"

namespace Subtile {
namespace Input {

Analog::Analog(double min, double max, bool isStrict, std::optional<double> def) :
	m_min(min),
	m_max(max),
	m_is_strict(isStrict),
	m_default(def ? *def : max * 0.5 + min * 0.5),
	m_adapter(new NAnalog::Adapter::Disconnected(m_default)),
	m_value(m_default)
{
}

Analog::~Analog(void)
{
}

void Analog::update(void)
{
	m_value = m_adapter->read();
}

double Analog::getState(void) const
{
	return m_value;
}

bool Analog::bind(System::IInput &input)
{
	if (!m_is_strict) {
		try {
			m_adapter.reset(new NAnalog::Adapter::Button(dynamic_cast<System::Input::IButton&>(input), m_min, m_max));
			return true;
		} catch (std::bad_cast&) {
		}
	}
	try {
		m_adapter.reset(new NAnalog::Adapter::Analog(dynamic_cast<System::Input::IAnalog&>(input), m_min, m_max));
		return true;
	} catch (std::bad_cast&) {
	}
	return false;
}

}
}