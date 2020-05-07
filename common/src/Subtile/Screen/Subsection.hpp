#pragma once

#include "Section.hpp"
#include "../Camera.hpp"
#include "../Math.hpp"

namespace Subtile {
namespace Screen {

class Subsection : public Section
{
public:
	Subsection(Camera &camera);
	virtual ~Subsection(void) = 0;

	virtual rect2 part(const vec2 &size);

private:
	Camera &m_camera;

	void onRender(void) override final;
};

}
}