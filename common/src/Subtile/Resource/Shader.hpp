#pragma once

#include "Element.hpp"
#include "../Shader.hpp"

namespace Subtile {
namespace Resource {

class Shader : public Element
{
public:
	Shader(void);
	~Shader(void) override;

	virtual sb::Shader::DescriptorSet::Layout material(void) const = 0;
	virtual sb::Shader::DescriptorSet::Layout object(void) const = 0;
};

}
}