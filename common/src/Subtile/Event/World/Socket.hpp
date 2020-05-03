#pragma once

#include "../Socket.hpp"

namespace Subtile {
namespace Event {
namespace World {

class Observer;

class Socket : public Event::Socket
{
public:
	Socket(void);
	~Socket(void);
};

}
}
}

#include "Observer.hpp"