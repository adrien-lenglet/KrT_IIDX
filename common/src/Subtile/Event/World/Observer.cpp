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
	add(static_cast<Cluster&>(button));
}

Observer::Input::~Input(void)
{
}


Observer::Input::Analog::Analog(void) :
	Group<Analog, std::tuple<std::string>, std::tuple<std::string>, std::tuple<double>>([](const std::string &inputName){
		return std::make_tuple(inputName);
	}, [](const std::string &inputName) {
		static_cast<void>(inputName);
		return std::optional<std::tuple<double>>();
	})
{
}

Observer::Input::Analog::~Analog(void)
{
}

Observer::Input::Button::Button(void) :
	Group<Button, std::tuple<std::string>, std::tuple<bool>>([](const std::string &inputName) {
		static_cast<void>(inputName);
		return std::optional<std::tuple<bool>>(true);
	})
{
}

Observer::Input::Button::~Button(void)
{
}

Observer::Update::Update(void) :
	Group<Update, std::tuple<>, std::tuple<double>>([this](){
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