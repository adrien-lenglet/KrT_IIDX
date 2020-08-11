#include "Shader.hpp"

namespace Subtile {

const std::set<Shader::Sbi>& Shader::getSbi(void)
{
	static const std::set<Shader::Sbi> res {
		Shader::Sbi::Vulkan
	};

	return res;
}

template <>
void Shader::Type::Vec<Shader::Type::Bool, 2>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Bvec2);
}
template <>
void Shader::Type::Vec<Shader::Type::Int, 2>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Ivec2);
}
template <>
void Shader::Type::Vec<Shader::Type::Uint, 2>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Uvec2);
}
template <>
void Shader::Type::Vec<Shader::Type::Float, 2>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Vec2);
}
template <>
void Shader::Type::Vec<Shader::Type::Double, 2>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Dvec2);
}

template <>
void Shader::Type::Vec<Shader::Type::Bool, 3>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Bvec3);
}
template <>
void Shader::Type::Vec<Shader::Type::Int, 3>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Ivec3);
}
template <>
void Shader::Type::Vec<Shader::Type::Uint, 3>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Uvec3);
}
template <>
void Shader::Type::Vec<Shader::Type::Float, 3>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Vec3);
}
template <>
void Shader::Type::Vec<Shader::Type::Double, 3>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Dvec3);
}

template <>
void Shader::Type::Vec<Shader::Type::Bool, 4>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Bvec4);
}
template <>
void Shader::Type::Vec<Shader::Type::Int, 4>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Ivec4);
}
template <>
void Shader::Type::Vec<Shader::Type::Uint, 4>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Uvec4);
}
template <>
void Shader::Type::Vec<Shader::Type::Float, 4>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Vec4);
}
template <>
void Shader::Type::Vec<Shader::Type::Double, 4>::createVertexInput(Shader::VertexInput::Creator &creator) const
{
	creator.addAttr(this, VertexInput::Format::Dvec4);
}

bool Shader::descriptorTypeIsMapped(DescriptorType type)
{
	static const std::set<DescriptorType> table {
		DescriptorType::UniformBuffer
	};

	return table.find(type) != table.end();
}

Shader::DescriptorSet::~DescriptorSet(void)
{
}

bool Shader::DescriptorSet::Layout::DescriptionBinding::isMapped(void) const
{
	return descriptorTypeIsMapped(descriptorType);
}

Shader::DescriptorSet::BaseHandle::BaseHandle(std::unique_ptr<DescriptorSet> &&desc_set) :
	m_set(std::move(desc_set))
{
}

Shader::DescriptorSet& Shader::DescriptorSet::BaseHandle::getSet(void)
{
	return *m_set;
}

Shader::DescriptorSet::Layout::Resolver::Inline::Inline(Instance &ins, const Layout::Description &desc) :
	m_layout(Instance::Getter(ins).system().createDescriptorSetLayout(desc))
{
}

Shader::DescriptorSet::Layout::Resolver::Inline::~Inline(void)
{
}

const Shader::DescriptorSet::Layout& Shader::DescriptorSet::Layout::Resolver::Inline::resolve(void) const
{
	return *m_layout;
}

Shader::DescriptorSet::Layout::Resolver::ForeignBase::ForeignBase(const Shader::DescriptorSet::Layout &layout) :
	m_layout(layout)
{
}
Shader::DescriptorSet::Layout::Resolver::ForeignBase::~ForeignBase(void)
{
}

const Shader::DescriptorSet::Layout& Shader::DescriptorSet::Layout::Resolver::ForeignBase::resolve(void) const
{
	return m_layout;
}

Shader::Model::BaseHandle::BaseHandle(std::unique_ptr<Shader::Model> &&model) :
	m_model(std::move(model))
{
}

Shader::Model& Shader::Model::BaseHandle::getModel(void) const
{
	return *m_model;
}

Shader::UniqueRef Instance::loadShaderRef(rs::Shader &shaderres)
{
	auto got = m_shaders.find(shaderres);
	if (got == m_shaders.end())
		return m_shaders.emplace(shaderres, m_system->loadShader(shaderres));
	else
		return got->second.new_ref();
}

}