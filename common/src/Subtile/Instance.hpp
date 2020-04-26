#pragma once

#include <memory>
#include "ISystem.hpp"
#include "IInput.hpp"
#include "Event/World/Observer.hpp"
#include "World.hpp"

namespace Subtile {

class World;

class Instance
{
public:
	Instance(size_t w, size_t h, bool isDebug, bool doProfile);
	~Instance(void);

	Event::World::Observer& getEvents(void);
	void setInputs(const std::function<void (const Event::World::Observer::Input::Setter &setter)> &binder);

	template <typename WorldType, typename ...ArgsTypes>
	std::unique_ptr<WorldType> add(ArgsTypes &&...args)
	{
		EntityImpl::pushCtx(nullptr, nullptr);
		World::pushEngine(*this);
		World::pushEngine(*this);
		return std::make_unique<WorldType>(std::forward<ArgsTypes>(args)...);
	}
	void run(void);

private:
	friend World;

	std::unique_ptr<ISystem> m_system;
	Event::World::Observer m_events;

	void scanInputs(void);
};

}

#include "World.hpp"