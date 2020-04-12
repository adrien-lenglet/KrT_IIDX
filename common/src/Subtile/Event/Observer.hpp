#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "Listener.hpp"

namespace Subtile {

class Instance;

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
		args(std::forward_as_tuple<ArgsType>(args)...)
	{
	}
	~Descriptor(void) = default;

	ObserverType &observer;
	std::tuple<ArgsType...> args;
};

template <typename ObserverType>
class DescGen
{
public:
	DescGen(void) = default;
	~DescGen(void) = default;

	template <typename ...ArgsTypes>
	Descriptor<ObserverType, ArgsTypes...> operator()(ArgsTypes &&...args)
	{
		return Descriptor<ObserverType, ArgsTypes...>(getObserver(), std::forward<ArgsTypes...>(args)...);
	}

private:
	ObserverType& getObserver(void)
	{
		return static_cast<ObserverType&>(*this);
	}
};

class Observer::Cluster : public Observer
{
public:
	virtual ~Cluster(void) = default;

protected:
	void add(Observer &observer);

private:
	std::vector<std::reference_wrapper<Observer>> m_observers;

	friend Instance;
	void update(void) override;
};

}
}

#include "Socket.hpp"