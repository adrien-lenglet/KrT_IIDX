#pragma once

#include "Event/Observer.hpp"
#include "System/IInput.hpp"

namespace Subtile {

class IInput : public Event::Observer
{
public:
	virtual ~IInput(void) = default;

	virtual bool bind(System::IInput &input) = 0;
};

}