#include "../Glfw.hpp"

namespace Subtile {
namespace System {

Glfw::Error::Error(const std::string &msg) :
	std::runtime_error(std::string("GLFW Error: ") + msg + std::string(": ") + Glfw::getError())
{
}

Glfw::Error::~Error(void)
{
}

}
}