#include "RenderList.hpp"
#include "World.hpp"
#include "Instance.hpp"

namespace Subtile {

RenderList::ShaderBase::ShaderBase(void) :
	m_to_render([this](){
		if (m_subpasses.size() == 0)
			destroy();
	})
{
}

RenderList::ShaderBase& RenderList::ShaderBase::resolve_direct(Shader::DescriptorSet &set)
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

RenderList::ShaderBase& RenderList::ShaderBase::resolve(const util::ref_wrapper<Shader::DescriptorSet::BaseHandle> *sets, size_t set_count)
{
	if (set_count == 0)
		return *this;

	return resolve_direct(Shader::DescriptorSet::BaseHandle::Getter().getSet(*sets)).resolve(&sets[1], set_count - 1);
}

void RenderList::ShaderBase::bind(Binding::Dependency::Socket &socket, Model &model)
{
	m_to_render.bind(socket, model);
}

void RenderList::ShaderBase::render_models(sb::CommandBuffer::Record::RenderPass &cmd)
{
	for (auto &m : m_to_render)
		m.get().draw(CommandBuffer::CmdGetter<sb::CommandBuffer::Record::RenderPass>().get(cmd));
}

void RenderList::ShaderBase::remove_subpass(Shader::DescriptorSet &set)
{
	auto got = m_subpasses.find(set);
	if (got == m_subpasses.end())
		throw std::runtime_error("Can't find child in shaderpasses");
	m_subpasses.erase(got);
	
	if (m_to_render.size() == 0 && m_subpasses.size() == 0)
		destroy();
}

RenderList::ShaderPass::ShaderPass(RenderList &parent, Shader &shader) :
	m_parent(parent),
	m_shader(shader)
{
}

void RenderList::ShaderPass::render(sb::CommandBuffer::Record::RenderPass &cmd)
{
	cmd.bind(m_shader);
	render_models(cmd);
	for (auto &sp : m_subpasses)
		sp.second.render(cmd, m_shader, sp.first, 0);
}

void RenderList::ShaderPass::destroy(void)
{
	m_parent.remove_shaderpass(m_shader);
}

RenderList::RenderList(void)
{
}

void RenderList::draw(sb::CommandBuffer::Record::RenderPass &cmd)
{
	for (auto &sp : m_shaderpasses)
		sp.second.render(cmd);
}

RenderList::~RenderList(void)
{
	m_inserted_models.clear();
	if (m_shaderpasses.size() > 0)
		util::fatal_throw([](){
			throw std::runtime_error("Shader passes still in render list");
		});
}

void RenderList::remove_shaderpass(Shader &shader)
{
	auto got = m_shaderpasses.find(shader);
	if (got == m_shaderpasses.end())
		throw std::runtime_error("Can't find child in shaderpasses");
	m_shaderpasses.erase(got);
}

RenderList::ShaderPass& RenderList::resolve(Shader &shader)
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

RenderList::SubShader::SubShader(RenderList::ShaderBase &parent, Shader::DescriptorSet &set) :
	m_parent(parent),
	m_set(set)
{
}

void RenderList::SubShader::render(sb::CommandBuffer::Record::RenderPass &cmd, Shader &shader, Shader::DescriptorSet &set, size_t depth)
{
	cmd.bind(shader, set, depth);
	render_models(cmd);
	for (auto &sp : m_subpasses)
		sp.second.render(cmd, shader, sp.first, depth + 1);
}

void RenderList::SubShader::destroy(void)
{
	m_parent.remove_subpass(m_set);
}

}