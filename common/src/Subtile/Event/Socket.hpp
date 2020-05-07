#pragma once

#include <vector>
#include <memory>
#include "Observer.hpp"

namespace Subtile {

namespace Event {

class Socket
{
public:
	Socket(void);
	~Socket(void);

	template <typename ...ReqTypes, typename ...Args>
	void bind(const Descriptor<ReqTypes...> &req, Args &&...args)
	{
		req.observer.bind(m_dependencies, req.args, std::forward<Args>(args)...);
	}

	template <typename ObserverType, typename ...Args>
	void bind(DescGen<ObserverType> &reqGen, Args &&...args)
	{
		auto req = reqGen();
		req.observer.bind(m_dependencies, req.args, std::forward<Args>(args)...);
	}

	template <typename T, typename ...PayloadTypes>
	void trigger(T &triggered, PayloadTypes &&...args)
	{
		triggered.trigger(*this, std::forward<PayloadTypes>(args)...);
	}

private:
	Binding::Dependency::Socket m_dependencies;
};

}
}