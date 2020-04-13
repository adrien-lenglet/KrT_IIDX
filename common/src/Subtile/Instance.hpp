#pragma once

#include <memory>
#include "ISystem.hpp"
#include "IInput.hpp"
#include "Observer.hpp"
#include "Input/Analog.hpp"
#include "Input/Button.hpp"
#include "Event/World/Observer.hpp"

namespace Subtile {

class World;

class Instance
{
public:
	Instance(size_t w, size_t h, bool isDebug, bool doProfile);
	~Instance(void);

	Event::World::Observer& getEvents(void);
	World createWorld(void);
	void run(void);

private:
	friend World;

	std::unique_ptr<ISystem> m_system;
	Event::World::Observer m_events;

	void scanInputs(void);
};

}

#include "World.hpp"