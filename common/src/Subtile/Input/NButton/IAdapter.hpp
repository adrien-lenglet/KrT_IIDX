#pragma once

namespace Subtile {
namespace Input {
namespace NButton {

class IAdapter
{
public:
	virtual ~IAdapter(void) = default;

	virtual bool read(void) = 0;
};

}
}
}