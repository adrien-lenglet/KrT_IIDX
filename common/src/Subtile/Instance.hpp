#pragma once

#include <memory>
#include "ISystem.hpp"
#include "IInput.hpp"
#include "Observer.hpp"

namespace Subtile {

class World;

class Instance
{
public:
	Instance(size_t w, size_t h, bool isDebug, bool doProfile);
	~Instance(void);

	void scanInputs(void);
	World createWorld(void);
	void run(void);

private:
	friend World;

	std::unique_ptr<ISystem> m_system;
	std::map<std::string, std::unique_ptr<IInput>> m_inputs;

	Observer<bool>::Listener listenInput(const std::string &input, const std::function<void (bool)> &callback);
	Observer<double>::Listener listenInput(const std::string &input, const std::function<void (double)> &callback);
};

}

#include "World.hpp"