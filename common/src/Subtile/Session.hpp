#pragma once

#include "ISystem.hpp"
#include "Event/System/Observer.hpp"
#include "Screen/Layout.hpp"
#include "Screen/Subsection.hpp"
#include "Math.hpp"
#include "util.hpp"

namespace Subtile {

class SessionBase : public Event::Socket
{
	struct Ctx {
		Ctx(ISystem &system, Event::System::Observer &events) :
			system(system),
			events(events)
		{
		}
		~Ctx(void)
		{
		}

		ISystem &system;
		Event::System::Observer &events;
	};

public:
	SessionBase(const Ctx &ctx);
	virtual ~SessionBase(void) = 0;

	void run(void);

protected:

	virtual Screen::Layout& getScreenLayout(void) = 0;
	void done(void);

	template <typename WorldType, typename ...ArgsTypes>
	std::unique_ptr<WorldType> createWorld(ArgsTypes &&...args)
	{
		return World::m_systems.emplace_frame(std::function([&](){
			return EntityBase::m_ctx.emplace_frame(std::function([&](){
				return std::make_unique<WorldType>(std::forward<ArgsTypes>(args)...);
			}), nullptr, nullptr);
		}), m_events);
	}

	template <class LayoutType, typename ...Args>
	std::unique_ptr<Screen::Layout> createLayout(Args &&...args)
	{
		return util::make_derived<LayoutType, Screen::Layout>(std::forward<Args>(args)...);
	}

private:
	friend Instance;

	static thread_local util::stack<Ctx> m_ctx;

	ISystem &m_system;
	Event::System::Observer &m_events;
	bool m_done;
};

#include "Camera.hpp"

template <typename FinalType>
class Session : public SessionBase
{
public:
	Session(void) :
		SessionBase(m_ctx.top())
	{
	}
	~Session(void) override
	{
	}

	template <class FinalLayoutType>
	class Layout : public Screen::Layout
	{
	public:
		Layout(void)
		{
		}
		~Layout(void) override
		{
		}

		using Class = Screen::Section::Top<FinalLayoutType>;
	};

	template <class FinalSubsectionType>
	class Subsection : public Screen::Subsection
	{
	public:
		Subsection(Camera &camera) :
			Screen::Subsection(camera)
		{
		}
		~Subsection(void) override
		{
		}

		using Class = Screen::Section::Top<FinalSubsectionType>;
	};
};

}