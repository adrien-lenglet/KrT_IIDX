#include "Socket.hpp"

namespace Subtile {
namespace Event {
namespace World {

Socket::Socket(Observer &events) :
	m_events(events)
{
}

Socket::~Socket(void)
{
}

Observer& Socket::events(void) const
{
	return m_events;
}

}
}
}