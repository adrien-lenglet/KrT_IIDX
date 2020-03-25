#include "../Entity.hpp"

namespace Subtile {

Entity::InputListener::InputListener(const std::string &input, std::function<void (bool)> &callback)
{
	static_cast<void>(input);
	static_cast<void>(callback);
}

Entity::InputListener::InputListener(const std::string &input, std::function<void (double)> &callback, bool isTrigger)
{
	static_cast<void>(input);
	static_cast<void>(callback);
	static_cast<void>(isTrigger);
}

Entity::InputListener::~InputListener(void)
{
}

}