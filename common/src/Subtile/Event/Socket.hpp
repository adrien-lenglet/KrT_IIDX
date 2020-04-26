#pragma once

#include <vector>
#include <memory>
#include "Observer.hpp"

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
		m_listeners.push_back(req.observer.listen(req.args, callback));
	}

	template <typename T, typename ...PayloadTypes>
	void trigger(T &triggered, PayloadTypes &&...args)
	{
		triggered.trigger(*this, std::forward<PayloadTypes>(args)...);
	}

private:
	friend Entity;
	std::vector<std::unique_ptr<Listener>> m_listeners;

	template <typename T>
	void addListener(T &&to_add)
	{
		m_listeners.push_back(std::move(to_add));
	}
};

}
}