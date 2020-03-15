#pragma once

#include "../IInput.hpp"

namespace Subtile {
namespace System {
namespace Input {

class IAnalog : IInput
{
public:
	virtual ~IAnalog(void) = default;

	double getState(void) const;
};

}
}
}