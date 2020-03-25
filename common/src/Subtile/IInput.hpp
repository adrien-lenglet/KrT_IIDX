#pragma once

namespace Subtile {

class IInput
{
public:
	virtual ~IInput(void) = default;

	virtual void update(void) = 0;
};

}