#include <fstream>
#include "Observer.hpp"

namespace Subtile {
namespace Event {
namespace World {

Observer::Observer(Subtile::Event::System::Observer &system) :
	system(system)
{
}

Observer::~Observer(void)
{
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

void Observer::updateEvents(void)
{
	Event::Observer::Cluster::update();
}

}
}
}