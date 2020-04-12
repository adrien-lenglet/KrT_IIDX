#pragma once

#include <vector>
#include <memory>
#include "Listener.hpp"
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
		req.observer.listen(std::get<ArgsType>(req.args)..., callback);
	}

private:
	std::vector<std::unique_ptr<Listener>> m_listeners;
};

}
}