#pragma once

#include "Shader.hpp"
#include "Binding.hpp"
#include "Queue.hpp"

namespace Subtile {

namespace Event {
class Socket;
}

namespace Render {

class Pass
{
	class SubShader;

	class ShaderBase
	{
	public:
		ShaderBase(void);

		ShaderBase& resolve_direct(Shader::DescriptorSet &set);
		ShaderBase& resolve(const util::ref_wrapper<Shader::DescriptorSet::BaseHandle> *sets, size_t set_count);

		void bind(Binding::Dependency::Socket &socket, Model &model);

	protected:
		void render_models(sb::CommandBuffer::Record::RenderPass &cmd);

		virtual void destroy(void) = 0;

		void remove_subpass(Shader::DescriptorSet &set);
		friend SubShader;

		std::map<util::ref_wrapper<Shader::DescriptorSet>, SubShader> m_subpasses;
		Binding::Weak<util::ref_wrapper<Model>, true> m_to_render;
	};

	class ShaderPass : public ShaderBase
	{
	public:
		ShaderPass(Pass &parent, Shader &shader);

		void render(sb::CommandBuffer::Record::RenderPass &cmd);

	protected:
		void destroy(void) override;

	private:
		Pass &m_parent;
		Shader &m_shader;
	};

public:
	Pass(void);
	~Pass(void);

	void render(sb::CommandBuffer::Record::RenderPass &cmd);

protected:
	void remove_shaderpass(Shader &shader);

private:
	System &m_system;
	std::map<util::ref_wrapper<Shader>, ShaderPass> m_shaderpasses;

	ShaderPass& resolve(Shader &shader);

	friend Event::Socket;
	template <size_t SetCount>
	void bind(Binding::Dependency::Socket &socket, const Shader::Render<SetCount> &render)
	{
		resolve(render.shader).resolve(render.sets.data(), render.sets.size()).bind(socket, render.model);
	}
};

class Pass::SubShader : public Pass::ShaderBase
{
public:
	SubShader(ShaderBase &parent, Shader::DescriptorSet &set);

	void render(sb::CommandBuffer::Record::RenderPass &cmd, Shader &shader, Shader::DescriptorSet &set, size_t depth);

protected:
	void destroy(void) override;

private:
	ShaderBase &m_parent;
	Shader::DescriptorSet &m_set;
};

}
}

#include "Event/Socket.hpp"

namespace Subtile {
namespace Event {

template <typename RenderType>
void Socket::bind(Render::Pass &pass, RenderType &&render)
{
	pass.bind(m_dependencies, render);
}

}
}