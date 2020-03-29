#include "Instance.hpp"
#include "System/Input/IButton.hpp"
#include "System/Input/IKeyboard.hpp"
#include "System/CGlfwVulkan.hpp"

#include <iostream>

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

	while (true) {
		scanInputs();
		/*for (const auto &k : keyboard.poll())
			std::cout << static_cast<char>(k) << std::endl;*/
		/*if (close_button.isPressed())
			break;*/
		m_system->render();
	}
}

Observer<bool>::Listener Instance::listenInput(const std::string &input, const std::function<void (bool)> &callback)
{
	return dynamic_cast<Input::Button&>(*m_inputs.at(input)).listen(callback);
}

Observer<double>::Listener Instance::listenInput(const std::string &input, const std::function<void (double)> &callback)
{
	return dynamic_cast<Input::Analog&>(*m_inputs.at(input)).listen(callback);
}

}