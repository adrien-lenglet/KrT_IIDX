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

Observer::Input::Input(void) :
	analog(*this),
	button(*this)
{
	add(static_cast<Cluster&>(analog));
	add(static_cast<Cluster&>(button));
	add(m_input_update);
}

Observer::Input::~Input(void)
{
}


Observer::Input::Analog::Analog(Input &input) :
	Group<Analog, std::tuple<std::string>, std::tuple<util::ref_wrapper<Subtile::Input::Analog>>, std::tuple<double>>([this](const std::string &inputName){
		return util::ref_wrapper(dynamic_cast<Subtile::Input::Analog&>(*m_input.m_inputs.at(inputName)));
	}, [](const util::ref_wrapper<Subtile::Input::Analog> &input) {
		return input.get().getState();
	}, [this](void) -> Observer::Cluster& {
		return m_input.m_input_update;
	}),
	m_input(input)
{
}

Observer::Input::Analog::~Analog(void)
{
}

Observer::Input::Button::Button(Input &input) :
	Group<Button, std::tuple<std::string>, std::tuple<util::ref_wrapper<Subtile::Input::Button>>, std::tuple<bool>>([this](const std::string &inputName){
		return util::ref_wrapper(dynamic_cast<Subtile::Input::Button&>(*m_input.m_inputs.at(inputName)));
	}, [](const util::ref_wrapper<Subtile::Input::Button> &input) {
		return input.get().getState();
	}, [this](void) -> Observer::Cluster& {
		return m_input.m_input_update;
	}),
	m_input(input)
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