
#include "krt/krt.hpp"

Renderer::Renderer(Vk& vk) :
	pipeline(vk, std::vector<Pipeline::ShaderStageCreateInfo>{
		{VK_SHADER_STAGE_VERTEX_BIT, "common/shaders/vert.spv"},
		{VK_SHADER_STAGE_FRAGMENT_BIT, "common/shaders/frag.spv"}
	})
{
}
