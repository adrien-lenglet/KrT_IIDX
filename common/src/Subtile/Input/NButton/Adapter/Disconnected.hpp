#pragma once

#include "../IAdapter.hpp"

namespace Subtile {
namespace Input {
namespace NButton {
namespace Adapter {

class Disconnected : public IAdapter
{
public:
	Disconnected(void);
	~Disconnected(void) override;

	bool read(void) override;
};

}
}
}
}