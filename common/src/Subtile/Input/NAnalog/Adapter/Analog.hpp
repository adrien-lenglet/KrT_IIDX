#pragma once

#include "../IAdapter.hpp"
#include "../../../System/Input/IAnalog.hpp"

namespace Subtile {
namespace Input {
namespace NAnalog {
namespace Adapter {

class Analog : public IAdapter
{
public:
	Analog(System::Input::IAnalog &input, double min, double max);
	~Analog(void) override;

	double read(void) override;

private:
	System::Input::IAnalog &m_input;
	double m_min;
	double m_max;
};

}
}
}
}