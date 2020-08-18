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
template <typename>
class Session;

class SessionBase : public Event::Socket
{
public:
	SessionBase(InstanceBase &instance);
	virtual ~SessionBase(void);

	void run(void);

protected:
	void done(void);

	virtual void render(void) = 0;
	using VecWorldRef = std::vector<util::ref_wrapper<WorldBase>>;
	virtual VecWorldRef updated_worlds(void) = 0;

private:
	template <typename>
	friend class Instance;
	friend InstanceBase;
	template <typename>
	friend class Session;

	static util::stack<std::reference_wrapper<InstanceBase>>& getCtx(void);
	static util::stack<std::reference_wrapper<SessionBase>>& getSessionStack(void);

	InstanceBase &m_instance;
	bool m_done;
};

}

namespace Subtile {

template <typename InstanceType>
class Session : public SessionBase
{
public:
	Session(void) :
		SessionBase(getCtx().top()),
		instance(reinterpret_cast<InstanceType&>(getCtx().top().get()))
	{
		getSessionStack().emplace(*this);
	}
	~Session(void) override
	{
	}

	using instance_type = InstanceType;

protected:
	InstanceType &instance;
};

}

#include "Instance.hpp"