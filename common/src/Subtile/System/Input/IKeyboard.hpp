#pragma once

#include <vector>
#include "../IInput.hpp"

namespace Subtile {
namespace System {
namespace Input {

class IKeyboard : public IInput
{
public:
	virtual ~IKeyboard(void) override = default;

	virtual std::vector<uint32_t> poll(void) const = 0;
};

}
}
}