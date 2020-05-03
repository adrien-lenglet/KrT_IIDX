#pragma once

#include <memory>
#include "ISystem.hpp"
#include "IInput.hpp"
#include "Event/System/Observer.hpp"
#include "World.hpp"

namespace Subtile {

class WorldBase;

class Instance
{
public:
	Instance(size_t w, size_t h, bool isDebug, bool doProfile);
	~Instance(void);

	void setInputs(const std::function<void (const Event::System::Observer::Input::Setter &setter)> &binder);

	template <typename WorldType, typename ...ArgsTypes>
	std::unique_ptr<WorldType> add(ArgsTypes &&...args)
	{
		return World::m_systems.emplace_frame(std::function([&](){
			return EntityBase::m_ctx.emplace_frame(std::function([&](){
				return std::make_unique<WorldType>(std::forward<ArgsTypes>(args)...);
			}), nullptr, nullptr);
		}), m_events);
	}
	void run(void);

private:
	friend WorldBase;

	std::unique_ptr<ISystem> m_system;
	Event::System::Observer m_events;

	void scanInputs(void);
};

}

#include "World.hpp"