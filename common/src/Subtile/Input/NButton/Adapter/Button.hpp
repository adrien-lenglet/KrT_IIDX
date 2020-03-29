#pragma once

#include "../IAdapter.hpp"
#include "../../../System/Input/IButton.hpp"

namespace Subtile {
namespace Input {
namespace NButton {
namespace Adapter {

class Button : public IAdapter
{
public:
	Button(System::Input::IButton &input);
	~Button(void) override;

	bool read(void) override;

private:
	System::Input::IButton &m_input;
};

}
}
}
}