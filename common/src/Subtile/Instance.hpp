#pragma once

#include <memory>
#include "ISystem.hpp"

namespace Subtile {

class World;

class Instance
{
public:
	Instance(size_t w, size_t h, bool isDebug, bool doProfile);
	~Instance(void);

	World world(void);
	void run(void);

private:
	std::unique_ptr<ISystem> m_system;
};

}

#include "World.hpp"