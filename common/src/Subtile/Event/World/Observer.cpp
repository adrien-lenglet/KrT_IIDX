#include "Observer.hpp"

namespace Subtile {
namespace Event {
namespace World {

Observer::Observer(void)
{
	add(input);
	add(static_cast<Cluster&>(update));
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
		return std::optional<std::tuple<double>>(3.14);
	})
{
}

Observer::Input::Analog::~Analog(void)
{
}

Observer::Update::Update(void) :
	Group<Update, std::tuple<>, std::tuple<double>>([this](){
		auto now = std::chrono::high_resolution_clock::now();
		return std::optional<std::tuple<double>>(std::chrono::duration<double>(now - m_time_before).count());
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