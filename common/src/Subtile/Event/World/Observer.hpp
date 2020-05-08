#pragma once

#include "../System/Observer.hpp"

namespace Subtile {

class Entity;

namespace Event {
namespace World {

class Socket;

class Observer : public Event::Observer::Cluster
{
public:
	Observer(Subtile::Event::System::Observer &system);
	~Observer(void) override;

	Subtile::Event::System::Observer &system;

private:
	friend Entity;
	friend SessionBase;

	void updateEvents(void);
};

}
}
}