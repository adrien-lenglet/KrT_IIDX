#pragma once

#include "File.hpp"
#include "Target.hpp"
#include "../Model.hpp"
#include "../Math.hpp"

namespace Subtile {
namespace Resource {

class Model : public File
{
public:
	Model(void);
	~Model(void) override;

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;
	};

	class Compiled : public Target
	{
	public:
		Compiled(Model &parent);
		~Compiled(void) override;

		std::vector<Vertex> read(void) const;

	protected:
		void build(std::ostream &o) const override;

	private:
		Model &m_parent;
	};

	auto& getCompiled(void)
	{
		return m_compiled;
	}

private:
	Compiled &m_compiled;
};

}
}