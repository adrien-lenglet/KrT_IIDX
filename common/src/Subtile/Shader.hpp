#pragma once

#include <set>
#include "../Subtile.hpp"

namespace Subtile {

class Shader
{
public:
	virtual ~Shader(void) = default;

	enum class Stage {
		TesselationControl,
		TesselationEvaluation,
		Geometry,
		Vertex,
		Fragment
	};

	enum class Sbi {  // shader binary interface
		Vulkan
	};

	class Compiler;

	enum class DescriptorType
	{
		UniformBuffer,
		CombinedImageSampler
	};

	class DescriptorSet
	{
	public:
		class LayoutBinding
		{
		public:
			size_t binding;
			size_t descriptorCount;
			DescriptorType descriptorType;
			std::set<Stage> stages;
		};

		class Layout
		{
		public:
			Layout(std::initializer_list<LayoutBinding> init) :
				m_bindings(init)
			{
			}

			auto& getBindings(void) const
			{
				return m_bindings;
			}

		private:
			std::vector<LayoutBinding> m_bindings;
		};
	};
};

}