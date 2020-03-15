#pragma once

#include "../IInput.hpp"

namespace Subtile {
namespace System {
namespace Input {

class ITrigger : IInput
{
public:
	virtual ~ITrigger(void) = default;

	double getState(void) const;
};

}
}
}