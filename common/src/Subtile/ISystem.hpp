#pragma once

#include <vector>
#include <string>
#include <map>
#include "System/IInput.hpp"
#include "Resource/Shader.hpp"
#include "Render.hpp"

namespace Subtile {

class ISystem
{
public:
	virtual ~ISystem(void) = default;

	virtual void scanInputs(void) = 0;
	virtual const std::map<std::string, System::IInput&>& getInputs(void) = 0;

	virtual std::unique_ptr<Shader> loadShader(rs::Shader &shader) = 0;
	virtual std::unique_ptr<Shader::DescriptorSet::Layout> createDescriptorSetLayout(const Shader::DescriptorSet::Layout::Description &desc) = 0;
	virtual std::unique_ptr<Render::CommandBuffer> createRenderCommandBuffer(void) = 0;
	virtual void acquireNextImage(void) = 0;
	virtual void presentImage(void) = 0;
};

}