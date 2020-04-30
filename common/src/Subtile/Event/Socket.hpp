#pragma once

#include <vector>
#include <memory>
#include "Observer.hpp"
#include "../Binding.hpp"

namespace Subtile {

class Entity;

namespace Event {

class Socket
{
public:
	Socket(void);
	~Socket(void);

	template <typename L, typename ObserverType, typename ...ArgsType>
	void listen(const Descriptor<ObserverType, ArgsType...> &req, const L &callback)
	{
		m_listeners.insert(req.observer.listen(req.args, callback));
	}

	template <typename T, typename ...PayloadTypes>
	void trigger(T &triggered, PayloadTypes &&...args)
	{
		triggered.trigger(*this, std::forward<PayloadTypes>(args)...);
	}

private:
	friend Entity;
	util::unique_set<Listener> m_listeners;
	Binding::Dependency::Socket m_dependencies;
};

}
}