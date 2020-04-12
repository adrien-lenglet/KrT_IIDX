#include "Observer.hpp"

namespace Subtile {
namespace Event {
namespace World {

Observer::Observer(void)
{
	add(input);
}

Observer::~Observer(void)
{
}

Observer::Input::Input(void)
{
	add(static_cast<Cluster&>(analog));
}

Observer::Input::~Input(void)
{
}


Observer::Input::Analog::Analog(void) :
	Group<Analog, std::tuple<std::string>, std::tuple<double>>([](const std::string &inputName) {
		static_cast<void>(inputName);
		return std::optional<std::tuple<double>>();
	})
{
}

Observer::Input::Analog::~Analog(void)
{
}

}
}
}