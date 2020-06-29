#pragma once

#include <memory>
#include "ISystem.hpp"
#include "IInput.hpp"
#include "Event/System/Observer.hpp"
#include "World.hpp"
#include "Session.hpp"

namespace Subtile {

class Instance
{
public:
	Instance(bool isDebug = false);
	~Instance(void);

	void setInputs(const std::function<void (const Event::System::Observer::Input::Setter &setter)> &binder);

	template <typename SessionType, typename ...ArgsTypes>
	std::unique_ptr<SessionType> createSession(ArgsTypes &&...args)
	{
		auto res = SessionBase::getCtx().emplace_frame(std::function([&](){
			return std::make_unique<SessionType>(std::forward<ArgsTypes>(args)...);
		}), SessionBase::Ctx(*m_system, m_events));
		SessionBase::getSessionStack().pop();
		return res;
	}

private:
	std::unique_ptr<ISystem> m_system;
	Event::System::Observer m_events;

	void scanInputs(void);
};

}