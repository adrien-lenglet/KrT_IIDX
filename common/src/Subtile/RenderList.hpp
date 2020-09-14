#pragma once

#include "Shader.hpp"
#include "Binding.hpp"
#include "Queue.hpp"
#include "Event/Socket.hpp"

namespace Subtile {

namespace Event {
class Socket;
}

class RenderList
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
		ShaderPass(RenderList &parent, Shader &shader);

		void render(sb::CommandBuffer::Record::RenderPass &cmd);

	protected:
		void destroy(void) override;

	private:
		RenderList &m_parent;
		Shader &m_shader;
	};

public:
	RenderList(void);
	~RenderList(void);

	void draw(sb::CommandBuffer::Record::RenderPass &cmd);

	template <typename RenderShaderType, size_t SetCount>
	void insert(const Shader::Render<RenderShaderType, SetCount> &render)
	{
		resolve(render.shader).resolve(render.sets.data(), render.sets.size()).bind(m_inserted_models, render.model);
	}

protected:
	void remove_shaderpass(Shader &shader);

private:
	std::map<util::ref_wrapper<Shader>, ShaderPass> m_shaderpasses;
	Binding::Dependency::Socket m_inserted_models;

	ShaderPass& resolve(Shader &shader);

	friend Event::Socket;
	template <typename RenderShaderType, size_t SetCount>
	void bind(Binding::Dependency::Socket &socket, const Shader::Render<RenderShaderType, SetCount> &render)
	{
		resolve(render.shader).resolve(render.sets.data(), render.sets.size()).bind(socket, render.model);
	}
};

class RenderList::SubShader : public RenderList::ShaderBase
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

namespace Subtile {
namespace Event {

template <typename RenderType>
void Socket::bind(RenderList &renderList, RenderType &&render)
{
	renderList.bind(m_dependencies, render);
}

}
}