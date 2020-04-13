#include "Instance.hpp"
#include "System/Input/IButton.hpp"
#include "System/Input/IKeyboard.hpp"
#include "System/CGlfwVulkan.hpp"

namespace Subtile {

Instance::Instance(size_t w, size_t h, bool isDebug, bool doProfile) :
	m_system(new System::CGlfwVulkan(w, h, isDebug, doProfile)),
	m_events(*m_system)
{
}

Instance::~Instance(void)
{
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
		m_system->scanInputs();
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