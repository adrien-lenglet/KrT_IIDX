#include <fstream>
#include "Observer.hpp"
#include "Subtile/scp.hpp"

namespace Subtile {
namespace Event {
namespace World {

root_scc(Observer,
	scp::Observer(Subtile::Event::System::Observer &system) :
		system(system)
	{
		add(static_cast<Observer::Cluster&>(update));
	}

	scp::~Observer(void)
	{
	}

	void scp::updateEvents(void)
	{
		Event::Observer::Cluster::update();
	}

	scc(Update,
		scp::Update(void) :
			Observer::Group<Update, std::tuple<>, std::tuple<double>>([this](){
				auto now = std::chrono::high_resolution_clock::now();
				double res = std::chrono::duration<double>(now - m_time_before).count();
				m_time_before = now;
				return res;
			}),
			m_time_before(std::chrono::high_resolution_clock::now())
		{
		}

		scp::~Update(void)
		{
		}
	)
)

}
}
}