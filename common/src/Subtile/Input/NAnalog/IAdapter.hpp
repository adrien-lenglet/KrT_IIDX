#pragma once

namespace Subtile {
namespace Input {
namespace NAnalog {

class IAdapter
{
public:
	virtual ~IAdapter(void) = default;

	virtual double read(void) = 0;
};

}
}
}