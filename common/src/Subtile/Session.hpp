#pragma once

#include "Event/System/Observer.hpp"
#include "Event/Socket.hpp"
#include "Math.hpp"
#include "util.hpp"

namespace Subtile {

class Instance;
class WorldBase;
class Session;

class SessionBase : public Event::Socket
{
public:
	SessionBase(Instance &instance);
	virtual ~SessionBase(void) = 0;

	void run(void);

protected:
	void done(void);

	template <class T>
	using Class = typename T::template Impl<T>;

	template <typename WorldType, typename ...ArgsTypes>
	auto& add(ArgsTypes &&...args);

	virtual void render(void) = 0;

private:
	friend Instance;
	friend Session;

	static util::stack<std::reference_wrapper<Instance>>& getCtx(void);
	static util::stack<std::reference_wrapper<SessionBase>>& getSessionStack(void);

	Instance &m_instance;
	util::unique_set<WorldBase> m_worlds;
	bool m_done;
};

}

namespace Subtile {

class Session : public SessionBase
{
public:
	Session(void) :
		SessionBase(getCtx().top())
	{
		getSessionStack().emplace(*this);
	}
	~Session(void) override
	{
	}
};

}

#include "Instance.hpp"