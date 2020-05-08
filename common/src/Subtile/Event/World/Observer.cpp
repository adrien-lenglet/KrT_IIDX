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

void Observer::updateEvents(void)
{
	Event::Observer::Cluster::update();
}

}
}
}