#pragma once

#include "Event/System/Observer.hpp"
#include "Event/Socket.hpp"
#include "Math.hpp"
#include "util.hpp"

namespace Subtile {

template <typename>
class Instance;
class InstanceBase;
class WorldBase;
class Session;

class SessionBase : public Event::Socket
{
public:
	SessionBase(InstanceBase &instance);
	virtual ~SessionBase(void) = 0;

	void run(void);

protected:
	void done(void);

	template <typename WorldType, typename ...ArgsTypes>
	auto& add(ArgsTypes &&...args);

	virtual void render(void) = 0;

private:
	template <typename>
	friend class Instance;
	friend InstanceBase;
	friend Session;

	static util::stack<std::reference_wrapper<InstanceBase>>& getCtx(void);
	static util::stack<std::reference_wrapper<SessionBase>>& getSessionStack(void);

	InstanceBase &m_instance;
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