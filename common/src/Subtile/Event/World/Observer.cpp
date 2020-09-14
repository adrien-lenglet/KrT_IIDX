#include <fstream>
#include "Observer.hpp"

namespace Subtile {
namespace Event {
namespace World {

Observer::Observer(void)
{
	add(static_cast<Observer::Cluster&>(update));
}

Observer::~Observer(void)
{
}

void Observer::updateEvents(void)
{
	Event::Observer::Cluster::update();
}

Observer::Update::Update(void) :
	Observer::Group<Update, std::tuple<>, std::tuple<double>>([this](){
		auto now = std::chrono::high_resolution_clock::now();
		double res = std::chrono::duration<double>(now - m_time_before).count();
		m_time_before = now;
		return res;
	}),
	m_time_before(std::chrono::high_resolution_clock::now())
{
}

Observer::Update::~Update(void)
{
}

}
}
}