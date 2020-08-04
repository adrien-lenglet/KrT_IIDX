#include "Render.hpp"
#include "World.hpp"

namespace Subtile {
namespace Render {

Pass::ShaderBase::ShaderBase(void) :
	m_to_render([this](){
		if (m_subpasses.size() == 0)
			destroy();
	})
{
}

Pass::ShaderBase& Pass::ShaderBase::resolve_direct(Shader::DescriptorSet &set)
{
	auto got = m_subpasses.find(set);
	if (got == m_subpasses.end()) {
		auto [it, suc] = m_subpasses.emplace(std::piecewise_construct, std::forward_as_tuple(set), std::forward_as_tuple(*this, set));
		if (!suc)
			throw std::runtime_error("Can't emplace shader subpass");
		got = it;
	}
	return got->second;
}

Pass::ShaderBase& Pass::ShaderBase::resolve(Shader::DescriptorSet::BaseHandle *last_set)
{
	Shader::DescriptorSet::BaseHandle *sets[32];
	size_t size = 0;

	while (last_set) {
		sets[size++] = last_set;
		last_set = Shader::DescriptorSet::BaseHandle::Getter(*last_set).getParent();
	}
	ShaderBase *res = this;
	for (size_t i = 0; i < size; i++) {
		size_t i_inv = size - 1 - i;
		res = &res->resolve_direct(Shader::DescriptorSet::BaseHandle::Getter(*sets[i_inv]).getSet());
	}
	return *res;
}

void Pass::ShaderBase::bind(Binding::Dependency::Socket &socket, const Shader::Model &model)
{
	m_to_render.bind(socket, model);
}

void Pass::ShaderBase::render_models(CommandBuffer &cmd)
{
	for (auto &m : m_to_render)
		cmd.draw(m);
}

void Pass::ShaderBase::remove_subpass(Shader::DescriptorSet &set)
{
	auto got = m_subpasses.find(set);
	if (got == m_subpasses.end())
		throw std::runtime_error("Can't find child in shaderpasses");
	m_subpasses.erase(got);
	
	if (m_to_render.size() == 0 && m_subpasses.size() == 0)
		destroy();
}

Pass::ShaderPass::ShaderPass(Pass &parent, Shader &shader) :
	m_parent(parent),
	m_shader(shader)
{
}

void Pass::ShaderPass::render(CommandBuffer &cmd)
{
	cmd.bindShader(m_shader);
	render_models(cmd);
	for (auto &sp : m_subpasses)
		sp.second.render(cmd, m_shader, sp.first, 0);
}

void Pass::ShaderPass::destroy(void)
{
	m_parent.remove_shaderpass(m_shader);
}

Pass::Pass(void) :
	m_system(World::getInstanceStack().top().get().system())
{
}

void Pass::render(void)
{
	auto renderCmd = m_system.createRenderCommandBuffer();

	renderCmd->beginRenderPass();
	for (auto &sp : m_shaderpasses)
		sp.second.render(*renderCmd);
	renderCmd->endRenderPass();
	renderCmd->submit();
}

Pass::~Pass(void)
{
	if (m_shaderpasses.size() > 0)
		util::fatal_throw([](){
			throw std::runtime_error("Shader passes still in pass");
		});
}

void Pass::remove_shaderpass(Shader &shader)
{
	auto got = m_shaderpasses.find(shader);
	if (got == m_shaderpasses.end())
		throw std::runtime_error("Can't find child in shaderpasses");
	m_shaderpasses.erase(got);
}

Pass::ShaderPass& Pass::resolve(Shader &shader)
{
	auto got = m_shaderpasses.find(shader);
	if (got == m_shaderpasses.end()) {
		auto [it, suc] = m_shaderpasses.emplace(std::piecewise_construct, std::forward_as_tuple(shader), std::forward_as_tuple(*this, shader));
		if (!suc)
			throw std::runtime_error("Can't emplace shader pass");
		got = it;
	}
	return got->second;
}

void Pass::bind(Binding::Dependency::Socket &socket, const Shader::Render &render)
{
	resolve(render.getShader()).resolve(render.getLastSet()).bind(socket, render.getModel());
}

Pass::SubShader::SubShader(Pass::ShaderBase &parent, Shader::DescriptorSet &set) :
	m_parent(parent),
	m_set(set)
{
}

void Pass::SubShader::render(CommandBuffer &cmd, Shader &shader, Shader::DescriptorSet &set, size_t depth)
{
	cmd.bindDescriptorSet(shader, set, depth);
	render_models(cmd);
	for (auto &sp : m_subpasses)
		sp.second.render(cmd, shader, sp.first, depth++);
}

void Pass::SubShader::destroy(void)
{
	m_parent.remove_subpass(m_set);
}

}
}