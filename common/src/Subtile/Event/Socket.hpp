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

	template <typename ReqType, typename ...Args>
	void bind(const ReqType &req, Args &&...args)
	{
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