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
};

}
}