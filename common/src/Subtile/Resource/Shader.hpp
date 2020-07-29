#pragma once

#include <set>
#include <map>
#include "File.hpp"
#include "Target.hpp"
#include "../Shader.hpp"

namespace Subtile {
namespace Resource {

class Shader : public File
{
public:
	Shader(const std::set<sb::Shader::Stage> &stages);
	~Shader(void) override;

	virtual sb::Shader::DescriptorSet::Layout material(void) const = 0;
	virtual sb::Shader::DescriptorSet::Layout object(void) const = 0;
	virtual sb::Shader::VertexInput vertexInput(void) const = 0;

	class Stage
	{
		static const std::string& getStageName(sb::Shader::Stage stage);

	public:
		Stage(Folder &folder, sb::Shader::Stage stage);

		class Source : public File
		{
		public:
			static std::string getFileName(sb::Shader::Stage stage, sb::Shader::Sbi sbi);

			Source(sb::Shader::Stage stage, sb::Shader::Sbi sbi);

			decltype(auto) getPath(void) const
			{
				return File::getPath();
			}

		protected:
			static const std::string& getSbiName(sb::Shader::Sbi sbi);
		};

		class VkSource : public Source
		{
		public:
			VkSource(Folder &folder, sb::Shader::Stage stage, sb::Shader::Sbi sbi);

			class Compiled : public Target
			{
			public:
				Compiled(Source &src);

			protected:
				void build(std::ostream &o) const override;

			private:
				Source &m_src;
			};

			const Compiled& getCompiled(void) const;

		private:
			Compiled &m_compiled;

			static std::string getCompiledName(sb::Shader::Stage stage, sb::Shader::Sbi sbi);
		};

		const VkSource& getVk(void) const;

	private:
		VkSource &m_vk;
	};

	const std::map<sb::Shader::Stage, Stage>& getStages(void) const;

private:
	Folder &m_stages_folder;
	const std::map<sb::Shader::Stage, Stage> m_stages;

	std::map<sb::Shader::Stage, Stage> createStages(const std::set<sb::Shader::Stage> &stages);
};

}
}