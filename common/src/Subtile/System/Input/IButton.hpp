#pragma once

#include "../IInput.hpp"

namespace Subtile {
namespace System {
namespace Input {

class IButton : public IInput
{
public:
	virtual ~IButton(void) override = default;

	virtual bool getState(void) const = 0;
	virtual bool isPressed(void) const = 0;
	virtual bool isReleased(void) const = 0;
};

}
}
}