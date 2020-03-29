#pragma once

#include "../IAdapter.hpp"

namespace Subtile {
namespace Input {
namespace NAnalog {
namespace Adapter {

class Disconnected : public IAdapter
{
public:
	Disconnected(double value);
	~Disconnected(void) override;

	double read(void) override;

public:
	double m_value;
};

}
}
}
}