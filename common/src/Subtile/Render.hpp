#pragma once

namespace Subtile {
namespace Render {

class CommandBuffer
{
public:
	virtual ~CommandBuffer(void) = default;

	virtual void submit(void) = 0;
};

}
}

#include "../Subtile.hpp"
#include "Shader.hpp"
#include "Binding.hpp"

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
		ShaderBase& resolve(Shader::DescriptorSet::BaseHandle *last_set);

		void bind(Binding::Dependency::Socket &socket, const Shader::Model &model);

	protected:
		virtual void destroy(void) = 0;

		void remove_subpass(Shader::DescriptorSet &set);
		friend SubShader;

	public:
		std::map<util::ref_wrapper<Shader::DescriptorSet>, SubShader> m_subpasses;
		Binding::Weak<util::ref_wrapper<const Shader::Model>, true> m_to_render;
	};

	class ShaderPass : public ShaderBase
	{
	public:
		ShaderPass(Pass &parent, Shader &shader);

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
	void bind(Binding::Dependency::Socket &socket, const Shader::Render &render);
};

class Pass::SubShader : public Pass::ShaderBase
{
public:
	SubShader(ShaderBase &parent, Shader::DescriptorSet &set);

protected:
	void destroy(void) override;

private:
	ShaderBase &m_parent;
	Shader::DescriptorSet &m_set;
};

}
}