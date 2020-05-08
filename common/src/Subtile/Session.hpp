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

	template <class T>
	using Class = typename T::template Impl<T>;

	template <typename WorldType, typename ...ArgsTypes>
	WorldType& addWorld(ArgsTypes &&...args)
	{
		return World::m_systems.emplace_frame(std::function([&]() -> auto& {
			return Entity::m_ctx.emplace_frame(std::function([&]() -> auto& {
				return m_worlds.emplace<WorldType>(std::forward<ArgsTypes>(args)...);
			}), nullptr, nullptr);
		}), m_events);
	}

	template <class LayoutType, typename ...Args>
	std::unique_ptr<Screen::Layout> createLayout(Args &&...args)
	{
		return util::make_derived<Class<LayoutType>, Screen::Layout>(std::forward<Args>(args)...);
	}

private:
	friend Instance;

	static thread_local util::stack<Ctx> m_ctx;
	static thread_local util::stack<std::reference_wrapper<SessionBase>> m_session_stack;

	ISystem &m_system;
	Event::System::Observer &m_events;
	util::unique_set<World> m_worlds;
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
		m_session_stack.emplace(*this);
	}
	~Session(void) override
	{
	}

	using Layout = Screen::Section::UserDerive<Screen::Layout>;

	class Subsection : public Screen::Section::UserDerive<Screen::Subsection>
	{
	public:
		Subsection(Camera &camera) :
			Screen::Section::UserDerive<Screen::Subsection>(camera)
		{
		}
		Subsection(const std::function<Camera& (FinalType&)> &resolver) :
			Screen::Section::UserDerive<Screen::Subsection>(resolver(static_cast<FinalType&>(m_session_stack.top().get())))
		{
		}
		~Subsection(void)
		{
		}
	};
};

}