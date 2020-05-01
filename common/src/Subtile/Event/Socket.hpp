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
	void bind(const Descriptor<ObserverType, ArgsType...> &req, const L &callback)
	{
		req.observer.bind(req.args, m_dependencies, callback);
	}

	template <typename T, typename ...PayloadTypes>
	void trigger(T &triggered, PayloadTypes &&...args)
	{
		triggered.trigger(*this, std::forward<PayloadTypes>(args)...);
	}

private:
	friend Entity;
	Binding::Dependency::Socket m_dependencies;
};

}
}