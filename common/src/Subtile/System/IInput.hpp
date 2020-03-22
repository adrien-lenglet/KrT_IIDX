#pragma once

#include <string>

namespace Subtile {
namespace System {

class IInput
{
public:
	virtual ~IInput(void) = default;

	virtual const std::string& getName(void) const = 0;
	virtual double getActivity(void) const = 0;
};

}
}