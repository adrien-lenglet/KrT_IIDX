#pragma once

#include "../Socket.hpp"
#include "Observer.hpp"

namespace Subtile {
namespace Event {
namespace World {

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