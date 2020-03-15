#include "CGlfwVulkan.hpp"

namespace Subtile {
namespace System {

CGlfwVulkan::CGlfwVulkan(void)
{
}

CGlfwVulkan::~CGlfwVulkan(void)
{
}

void CGlfwVulkan::scanInputs(void)
{
	/*for (auto &input : m_inputs)
		input.second.scan();*/
}

const std::map<std::string, System::IInput&> CGlfwVulkan::getInputs(void)
{
	return m_inputs;
}

}
}