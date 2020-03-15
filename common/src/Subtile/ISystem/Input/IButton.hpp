#pragma once

#include "../IInput.hpp"

namespace Subtile {
namespace System {
namespace Input {

class IButton : IInput
{
public:
	virtual ~IButton(void) = default;

	bool getState(void) const;
};

}
}
}