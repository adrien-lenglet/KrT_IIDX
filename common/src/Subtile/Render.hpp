#pragma once

#include "../Subtile.hpp"
#include "Shader.hpp"
#include "Binding.hpp"

namespace Subtile {
namespace Render {

class CommandBuffer
{
public:
	virtual ~CommandBuffer(void) = default;

	virtual void beginRenderPass(void) = 0;
	virtual void endRenderPass(void) = 0;
	virtual void bindShader(sb::Shader &shader) = 0;
	virtual void bindDescriptorSet(sb::Shader &shader, sb::Shader::DescriptorSet &set, size_t ndx) = 0;
	virtual void draw(const Shader::Model &model) = 0;

	virtual void submit(void) = 0;
};

}
}

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

		void bind(Binding::Dependency::Socket &socket, const Shader::Model &model);

	protected:
		void render_models(CommandBuffer &cmd);

		virtual void destroy(void) = 0;

		void remove_subpass(Shader::DescriptorSet &set);
		friend SubShader;

		std::map<util::ref_wrapper<Shader::DescriptorSet>, SubShader> m_subpasses;
		Binding::Weak<util::ref_wrapper<const Shader::Model>, true> m_to_render;
	};

	class ShaderPass : public ShaderBase
	{
	public:
		ShaderPass(Pass &parent, Shader &shader);

		void render(CommandBuffer &cmd);

	protected:
		void destroy(void) override;

	private:
		Pass &m_parent;
		Shader &m_shader;
	};

public:
	Pass(void);
	~Pass(void);

	void render(void);

protected:
	void remove_shaderpass(Shader &shader);

private:
	ISystem &m_system;
	std::map<util::ref_wrapper<Shader>, ShaderPass> m_shaderpasses;

	ShaderPass& resolve(Shader &shader);

	friend Event::Socket;
	template <size_t SetCount>
	void bind(Binding::Dependency::Socket &socket, const Shader::Render<SetCount> &render)
	{
		resolve(render.getShader()).resolve(render.getSets().data(), render.getSets().size()).bind(socket, render.getModel());
	}
};

class Pass::SubShader : public Pass::ShaderBase
{
public:
	SubShader(ShaderBase &parent, Shader::DescriptorSet &set);

	void render(CommandBuffer &cmd, Shader &shader, Shader::DescriptorSet &set, size_t depth);

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
void Socket::bind(Render::Pass &pass, const RenderType &render)
{
	pass.bind(m_dependencies, render);
}

}
}