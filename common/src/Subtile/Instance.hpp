#pragma once

#include <memory>
#include "ISystem.hpp"
#include "IInput.hpp"
#include "Event/System/Observer.hpp"
#include "World.hpp"
#include "Session.hpp"

namespace Subtile {

class WorldBase;

class Instance
{
public:
	Instance(size_t w, size_t h, bool isDebug, bool doProfile);
	~Instance(void);

	void setInputs(const std::function<void (const Event::System::Observer::Input::Setter &setter)> &binder);

	template <typename SessionType, typename ...ArgsTypes>
	std::unique_ptr<SessionType> createSession(ArgsTypes &&...args)
	{
		return SessionBase::m_ctx.emplace_frame(std::function([&](){
			return std::make_unique<SessionType>(std::forward<ArgsTypes>(args)...);
		}), SessionBase::Ctx(*m_system, m_events));
	}

private:
	friend WorldBase;

	std::unique_ptr<ISystem> m_system;
	Event::System::Observer m_events;

	void scanInputs(void);
};

}