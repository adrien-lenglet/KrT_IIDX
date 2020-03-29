#pragma once

#include <memory>
#include "ISystem.hpp"
#include "IInput.hpp"
#include "Observer.hpp"
#include "Input/Analog.hpp"
#include "Input/Button.hpp"

namespace Subtile {

class World;

class Instance
{
public:
	Instance(size_t w, size_t h, bool isDebug, bool doProfile);
	~Instance(void);

	Input::Analog& addAnalog(const std::string &name, double min = -1.0, double max = 1.0, bool isStrict = true);
	Input::Button& addButton(const std::string &name, bool isStrict = true, double analogThreshold = 0.5);
	void removeInput(const std::string &name);

	World createWorld(void);
	void run(void);

private:
	friend World;

	std::unique_ptr<ISystem> m_system;
	std::map<std::string, std::unique_ptr<IInput>> m_inputs;

	void scanInputs(void);
	Observer<bool>::Listener listenInput(const std::string &input, const std::function<void (bool)> &callback);
	Observer<double>::Listener listenInput(const std::string &input, const std::function<void (double)> &callback);
};

}

#include "World.hpp"