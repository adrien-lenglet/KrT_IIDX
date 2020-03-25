#include "Instance.hpp"
#include "System/Input/IButton.hpp"
#include "System/Input/IKeyboard.hpp"
#include "System/CGlfwVulkan.hpp"

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include "Subtile/Listener.hpp"

namespace Subtile {

Instance::Instance(size_t w, size_t h, bool isDebug, bool doProfile) :
	m_system(new System::CGlfwVulkan(w, h, isDebug, doProfile))
{
}

Instance::~Instance(void)
{
}

World Instance::world(void)
{
	return World(*this);
}

void Instance::run(void)
{
	bool swit = false;
	auto &close_button = dynamic_cast<const System::Input::IButton&>(m_system->getInputs().at("close_window"));
	auto &keyboard = dynamic_cast<const System::Input::IKeyboard&>(m_system->getInputs().at("keyboard"));
	auto observer = Observer<double>([&](auto &signal) {
		swit = !swit;
		if (swit)
			signal(3.14);
		else
			signal(2.56);
	});
	Observer<double>::Listener listener = observer.listen([](double val){
		std::cout << "GOT VAL:" << val << std::endl;
	});

	while (true) {
		observer.update();
		m_system->scanInputs();
		for (const auto &k : keyboard.poll())
			std::cout << static_cast<char>(k) << std::endl;
		if (close_button.isPressed())
			break;
		m_system->render();
	}
}

}