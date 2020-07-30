#pragma once

#include "Subtile/Entity.hpp"
#include "EntityTest2.hpp"
#include "res.resdecl.hpp"

namespace Krt {

class EntityTest : public sb::Entity
{
public:
	EntityTest(void);
	~EntityTest(void) override;

	Event<double> just_died;
	Event<size_t> got_score;

private:
	EntityTest2 &entity1;
	EntityTest2 &entity2;
	sb::Instance::Shader<decltype(res.shaders().diffuse())> m_shader;
	decltype(m_shader.material()) m_material;
	decltype(m_shader.object()) m_object;
	decltype(m_shader.model()) m_model;

	decltype(m_model) createModel(void);
};

}