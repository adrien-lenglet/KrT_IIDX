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

	template <typename L, typename ObserverType, typename ...ArgsType>
	void listen(const Descriptor<ObserverType, ArgsType...> &req, const L &callback)
	{
		m_listeners.push_back(req.observer.listen(req.args, callback));
	}

private:
	std::vector<std::unique_ptr<Listener>> m_listeners;
};

}
}