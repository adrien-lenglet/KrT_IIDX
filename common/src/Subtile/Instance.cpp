#include "Instance.hpp"
#include "System/Input/IButton.hpp"
#include "System/Input/IKeyboard.hpp"
#include "System/CGlfwVulkan.hpp"

namespace Subtile {

Instance::Instance(size_t w, size_t h, bool isDebug, bool doProfile) :
	m_system(new System::CGlfwVulkan(w, h, isDebug, doProfile))
{
}

Instance::~Instance(void)
{
}

Input::Analog& Instance::addAnalog(const std::string &name, double min, double max, bool isStrict)
{
	auto in = new Input::Analog(min, max, isStrict);

	m_inputs.emplace(name, in);
	return *in;
}

Input::Button& Instance::addButton(const std::string &name, bool isStrict, double analogThreshold)
{
	auto in = new Input::Button(isStrict, analogThreshold);

	m_inputs.emplace(name, in);
	return *in;
}

void Instance::removeInput(const std::string &name)
{
	auto got = m_inputs.find(name);

	if (got != m_inputs.end())
		m_inputs.erase(got);
	else
		throw std::runtime_error(std::string("Can't remove input '") + name + std::string("'"));
}

void Instance::scanInputs(void)
{
	for (auto &i : m_inputs)
		i.second->update();
}

World Instance::createWorld(void)
{
	return World(*this);
}

void Instance::run(void)
{
	/*auto &close_button = dynamic_cast<const System::Input::IButton&>(m_system->getInputs().at("close_window"));
	auto &keyboard = dynamic_cast<const System::Input::IKeyboard&>(m_system->getInputs().at("keyboard"));*/

	//std::cout << sizeof(Event::Socket) << std::endl;
	//std::cout << sizeof(Event::World::Socket) << std::endl;
	//std::cout << sizeof(Event::World::Socket::Input) << std::endl;
	//std::cout << sizeof(Event::World::Socket::Input::Data) << std::endl;
	while (true) {
		//scanInputs();
		static_cast<Event::Observer&>(m_events).update();
		/*for (const auto &k : keyboard.poll())
			std::cout << static_cast<char>(k) << std::endl;*/
		/*if (close_button.isPressed())
			break;*/
		m_system->render();
	}
}

Event::World::Observer& Instance::getEvents(void)
{
	return m_events;
}

}