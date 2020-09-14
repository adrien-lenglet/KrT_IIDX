#pragma once

#include "../Socket.hpp"

namespace Subtile {
namespace Event {
namespace World {

class Socket : public Event::Socket
{
public:
	Socket(void) = default;
	~Socket(void) = default;
};

}
}
}