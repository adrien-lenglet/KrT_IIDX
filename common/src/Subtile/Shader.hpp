#pragma once

#include "../Subtile.hpp"

namespace Subtile {

class Shader
{
public:
	enum class Stage {
		Tesselation,
		Geometry,
		Vertex,
		Fragment
	};

	enum class Sbi {  // shader binary interface
		Vulkan
	};

	class Compiler;
};

}