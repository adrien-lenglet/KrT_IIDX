#pragma once

#include "../IAdapter.hpp"
#include "../../../System/Input/IButton.hpp"

namespace Subtile {
namespace Input {
namespace NAnalog {
namespace Adapter {

class Button : public IAdapter
{
public:
	Button(System::Input::IButton &input, double min, double max);
	~Button(void) override;

	double read(void) override;

private:
	System::Input::IButton &m_input;
	double m_min;
	double m_max;
};

}
}
}
}