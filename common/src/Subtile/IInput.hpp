#pragma once

#include "System/IInput.hpp"

namespace Subtile {

class IInput
{
public:
	virtual ~IInput(void) = default;

	virtual void update(void) = 0;
	virtual bool bind(System::IInput &input) = 0;
};

}