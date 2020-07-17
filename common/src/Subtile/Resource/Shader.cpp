#include <filesystem>
#include <fstream>
#include "Shader.hpp"

namespace Subtile {
namespace Resource {

Shader::Shader(const std::set<sb::Shader::Stage> &stages) :
	File(false),
	m_stages_folder(Folder::Mod(getParent()).add<Folder::Hidden>(getId() + std::string("_stages"))),
	m_stages(createStages(stages))
{
}

Shader::~Shader(void)
{
}

const std::map<sb::Shader::Stage, Shader::Stage>& Shader::getStages(void) const
{
	return m_stages;
}

std::map<sb::Shader::Stage, Shader::Stage> Shader::createStages(const std::set<sb::Shader::Stage> &stages)
{
	std::map<sb::Shader::Stage, Stage> res;

	for (auto &s : stages)
		res.emplace(std::piecewise_construct, std::forward_as_tuple(s), std::forward_as_tuple(m_stages_folder, s)); // stage will decide of its own name
	return res;
}

const std::string& Shader::Stage::getStageName(sb::Shader::Stage stage)
{
	static const std::map<sb::Shader::Stage, std::string> table {
		{sb::Shader::Stage::TesselationControl, "tesc"},
		{sb::Shader::Stage::TesselationEvaluation, "tese"},
		{sb::Shader::Stage::Geometry, "geom"},
		{sb::Shader::Stage::Vertex, "vert"},
		{sb::Shader::Stage::Fragment, "frag"}
	};

	return table.at(stage);
}

Shader::Stage::Stage(Folder &folder, sb::Shader::Stage stage) :
	m_vk(Folder::Mod(folder).add<VkSource>(Folder::Mod::no_name, folder, stage, sb::Shader::Sbi::Vulkan))
{
}

const Shader::Stage::VkSource& Shader::Stage::getVk(void) const
{
	return m_vk;
}

const std::string& Shader::Stage::Source::getSbiName(sb::Shader::Sbi sbi)
{
	static const std::map<sb::Shader::Sbi, std::string> table {
		{sb::Shader::Sbi::Vulkan, "vk"}
	};

	return table.at(sbi);
}

Shader::Stage::Source::Source(sb::Shader::Stage stage, sb::Shader::Sbi sbi) :
	File(getFileName(stage, sbi), false)
{
}

std::string Shader::Stage::Source::getFileName(sb::Shader::Stage stage, sb::Shader::Sbi sbi)
{
	static const std::string p(".");
	static const std::string glsl("glsl");

	return getSbiName(sbi) + p + getStageName(stage) + p + glsl;
}

Shader::Stage::VkSource::VkSource(Folder &folder, sb::Shader::Stage stage, sb::Shader::Sbi sbi) :
	Source(stage, sbi),
	m_compiled(Folder::Mod(folder).add<Compiled>(getCompiledName(stage, sbi), *this))
{
}

std::string Shader::Stage::VkSource::getCompiledName(sb::Shader::Stage stage, sb::Shader::Sbi sbi)
{
	static const std::string p(".");
	static const std::string spv("spv");

	return getSbiName(sbi) + p + getStageName(stage) + p + spv;
}

const Shader::Stage::VkSource::Compiled& Shader::Stage::VkSource::getCompiled(void) const
{
	return m_compiled;
}

Shader::Stage::VkSource::Compiled::Compiled(Shader::Stage::Source &src) :
	Target({src}, true),
	m_src(src)
{
}

void Shader::Stage::VkSource::Compiled::build(std::ostream &o) const
{
	auto output = std::string("tmp.spv");
	auto cmd = std::string("glslangValidator.exe ") + m_src.getPath() + std::string(" -V -o ") + output;
	if (system(cmd.c_str()) != 0)
		throw std::runtime_error("Vulkan shader compilation failed");

	{
		std::ifstream file(output, std::ios::binary);
		o << file.rdbuf();
	}

	std::filesystem::remove(output);
}

}
}