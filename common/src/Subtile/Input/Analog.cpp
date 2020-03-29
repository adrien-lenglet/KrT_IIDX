#include "Analog.hpp"
#include "NAnalog/Adapter/Disconnected.hpp"
#include "NAnalog/Adapter/Analog.hpp"
#include "NAnalog/Adapter/Button.hpp"

namespace Subtile {
namespace Input {

Analog::Analog(double min, double max, bool isStrict) :
	m_min(min),
	m_max(max),
	m_is_strict(isStrict),
	m_observer([this](auto &signal) {
		if (m_adapter)
			signal(m_adapter->read());
	}),
	m_adapter(new NAnalog::Adapter::Disconnected(min))
{
}

Analog::~Analog(void)
{
}

void Analog::update(void)
{
	m_observer.update();
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

Observer<double>::Listener Analog::listen(const std::function<void (double)> &callback)
{
	return m_observer.listen(callback);
}

}
}