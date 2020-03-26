#include "World.hpp"

namespace Subtile {

World::World(Instance &engine) :
	m_engine(engine)
{
}

World::~World(void)
{
}

void World::resetRoot(void)
{
	m_root.reset(nullptr);
}

Observer<bool>::Listener World::listenInput(const std::string &input, const std::function<void (bool)> &callback)
{
	return m_engine.listenInput(input, callback);
}

Observer<double>::Listener World::listenInput(const std::string &input, const std::function<void (double)> &callback)
{
	return m_engine.listenInput(input, callback);
}

}