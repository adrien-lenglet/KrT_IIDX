#pragma once

#include "../IInput.hpp"

namespace Subtile {
namespace System {
namespace Input {

class IAnalog : IInput
{
public:
	virtual ~IAnalog(void) override = default;

	virtual double getState(void) const = 0;
};

}
}
}