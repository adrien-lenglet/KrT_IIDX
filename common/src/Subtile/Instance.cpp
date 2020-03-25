#include "Instance.hpp"
#include "System/Input/IButton.hpp"
#include "System/Input/IKeyboard.hpp"
#include "System/CGlfwVulkan.hpp"

#include <iostream>
#include <map>
#include <string>
#include <tuple>

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
	auto &close_button = dynamic_cast<const System::Input::IButton&>(m_system->getInputs().at("close_window"));
	auto &keyboard = dynamic_cast<const System::Input::IKeyboard&>(m_system->getInputs().at("keyboard"));
	//auto listener = Listener<std::tuple<bool>, std::tuple<double>>(false);

	auto lol = std::map<std::tuple<>, std::string>();

	lol.emplace(std::make_tuple(), "xd");
	lol.emplace(std::make_tuple(), "lol");

	for (auto &l : lol)
		std::cout << l.second << std::endl;
	while (true) {
		m_system->scanInputs();
		for (const auto &k : keyboard.poll())
			std::cout << static_cast<char>(k) << std::endl;
		if (close_button.isPressed())
			break;
		m_system->render();
	}
}

}