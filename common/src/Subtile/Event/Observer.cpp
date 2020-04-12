#include "Observer.hpp"

namespace Subtile {
namespace Event {

void Observer::Cluster::update(void)
{
	for (auto &o : m_observers)
		o.get().update();
}

void Observer::Cluster::add(Observer &observer)
{
	m_observers.emplace_back(observer);
}

}
}