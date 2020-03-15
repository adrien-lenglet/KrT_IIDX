#pragma once

#include "../ISystem.hpp"

namespace Subtile {
namespace System {

class CGlfwVulkan : public ISystem
{
public:
	CGlfwVulkan(void);
	~CGlfwVulkan(void) override;

	void scanInputs(void) override;
	const std::map<std::string, System::IInput&> getInputs(void) override;

private:
	const std::map<std::string, System::IInput&> m_inputs;
};

}
}