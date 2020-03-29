#pragma once

#include "../IAdapter.hpp"
#include "../../../System/Input/IAnalog.hpp"

namespace Subtile {
namespace Input {
namespace NButton {
namespace Adapter {

class Analog : public IAdapter
{
public:
	Analog(System::Input::IAnalog &input, double threshold);
	~Analog(void) override;

	bool read(void) override;

private:
	System::Input::IAnalog &m_input;
	double m_threshold;
};

}
}
}
}