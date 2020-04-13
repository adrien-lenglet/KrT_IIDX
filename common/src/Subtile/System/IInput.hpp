#pragma once

#include <string>
#include "../Event/Observer.hpp"

namespace Subtile {
namespace System {

class IInput : Event::Observer
{
public:
	virtual ~IInput(void) = default;

	virtual void update(void) override = 0;

	virtual const std::string& getName(void) const = 0;
	virtual double getActivity(void) const = 0;
};

}
}