#include "RenderPass.hpp"
#include "Instance.hpp"

namespace Subtile {
namespace Resource {

RenderPass::RenderPass(void) :
	File(false)
{
}

RenderPass::~RenderPass(void)
{
}

}

RenderPass::Cache::Ref InstanceBase::loadRenderPassRef(rs::RenderPass &renderpassres)
{
	auto got = m_render_passes.find(renderpassres);
	if (got == m_render_passes.end())
		return m_render_passes.emplace(renderpassres, m_system->createRenderPass(renderpassres));
	else
		return got->second.new_ref();
}

}