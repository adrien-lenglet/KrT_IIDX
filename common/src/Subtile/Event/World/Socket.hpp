#pragma once

#include "../Socket.hpp"

namespace Subtile {
namespace Event {
namespace World {

class Observer;

class Socket : public Event::Socket
{
public:
	Socket(Observer &events);
	~Socket(void);

	Observer &events;
};

}
}
}

#include "Observer.hpp"