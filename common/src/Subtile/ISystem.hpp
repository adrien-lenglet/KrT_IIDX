#pragma once

#include <vector>
#include <string>
#include <map>
#include "ISystem/IInput.hpp"

namespace Subtile {

class ISystem
{
public:
	virtual ~ISystem(void) = default;

	virtual void scanInputs(void) = 0;
	virtual const std::map<std::string, System::IInput&> getInputs(void) = 0;
};

}