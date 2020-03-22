#pragma once

#include <memory>
#include "../ISystem.hpp"
#include "GlfwVulkan/Vk/Instance.hpp"

namespace Subtile {
namespace System {

class CGlfwVulkan : public ISystem
{
public:
	CGlfwVulkan(size_t w, size_t h, bool isDebug, bool doProfile);
	~CGlfwVulkan(void) override;

	void scanInputs(void) override;
	const std::map<std::string, const System::IInput&>& getInputs(void) override;
	void render(void) override;

private:
	GlfwVulkan::Instance m_vk;
	std::vector<std::unique_ptr<System::IInput>> m_inputs;
	std::map<std::string, const System::IInput&> m_inputs_map;

	std::vector<std::unique_ptr<System::IInput>> createInputs(void);
	std::map<std::string, const System::IInput&> createInputsMap(void);
};

}
}