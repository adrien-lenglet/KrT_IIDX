#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "Listener.hpp"

namespace Subtile {
namespace Event {

class Observer
{
public:
	class Cluster;

	virtual ~Observer(void) = default;

private:
	virtual void update(void) = 0;
};

template <typename ObserverType, typename ...ArgsType>
struct Descriptor
{
	Descriptor(ObserverType &observer, ArgsType &&...args) :
		observer(observer),
		args(std::forward<ArgsType>(args)...)
	{
	}
	~Descriptor(void) = default;

	ObserverType &observer;
	std::tuple<ArgsType...> args;
};

class Observer::Cluster : public Observer
{
public:
	virtual ~Cluster(void) = default;

protected:
	void add(Observer &observer);

private:
	std::vector<std::reference_wrapper<Observer>> m_observers;

	void update(void) override;
};

}
}

#include "Socket.hpp"