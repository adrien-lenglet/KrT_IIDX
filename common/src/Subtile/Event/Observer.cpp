#include "Observer.hpp"

namespace Subtile {
namespace Event {

void Observer::Cluster::update(void)
{
	for (auto &o : m_observers)
		o.first.get().update();
}

void Observer::Cluster::add(Observer &observer)
{
	m_observers[util::ref_wrapper(observer)]++;
}

void Observer::Cluster::remove(Observer &observer)
{
	auto got = m_observers.find(util::ref_wrapper(observer));

	if (got != m_observers.end()) {
		got->second--;
		if (got->second == 0)
			m_observers.erase(got);
	} else
		throw std::runtime_error("No instance of that observer in the cluster");
}

}
}