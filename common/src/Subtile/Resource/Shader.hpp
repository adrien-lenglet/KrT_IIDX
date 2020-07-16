#pragma once

#include "File.hpp"
#include "../Shader.hpp"

namespace Subtile {
namespace Resource {

class Shader : public File
{
public:
	Shader(void);
	~Shader(void) override;

	virtual sb::Shader::DescriptorSet::Layout material(void) const = 0;
	virtual sb::Shader::DescriptorSet::Layout object(void) const = 0;
};

}
}