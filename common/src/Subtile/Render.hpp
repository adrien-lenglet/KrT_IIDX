#pragma once

#include "../Subtile.hpp"
#include "Shader.hpp"
#include "Binding.hpp"
#include "Event/Socket.hpp"

namespace Subtile {
namespace Render {

class Pass
{
	class ShaderPass
	{
	public:
		ShaderPass(void)
		{
		}

		ShaderPass& resolve_direct(Shader::DescriptorSet &set)
		{
			return m_subpasses[set];
		}

		ShaderPass& resolve(Shader::DescriptorSet::BaseHandle *last_set)
		{
			Shader::DescriptorSet::BaseHandle *sets[32];
			size_t size = 0;

			while (last_set) {
				sets[size++] = last_set;
				last_set = Shader::DescriptorSet::BaseHandle::Getter(*last_set).getParent();
			}
			ShaderPass *res = this;
			for (size_t i = 0; i < size; i++) {
				size_t i_inv = size - 1 - i;
				res = &res->resolve_direct(Shader::DescriptorSet::BaseHandle::Getter(*sets[i_inv]).getSet());
			}
			return *res;
		}

		void bind(Binding::Dependency::Socket &socket, const Shader::Model &model)
		{
			m_to_render.bind(socket, model);
		}

	private:
		std::map<util::ref_wrapper<Shader::DescriptorSet>, ShaderPass> m_subpasses;
		Binding::Weak<util::ref_wrapper<const Shader::Model>> m_to_render;
	};

public:
	Pass(void)
	{
	}

private:
	std::map<util::ref_wrapper<Shader>, ShaderPass> m_shaderpasses;

	ShaderPass& resolve(Shader &shader)
	{
		return m_shaderpasses[shader];
	}

	friend Event::Socket;
	void bind(Binding::Dependency::Socket &socket, const Shader::Render &render)
	{
		resolve(render.getShader()).resolve(render.getLastSet()).bind(socket, render.getModel());
	}
};

}
}