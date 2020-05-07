#include "Subsection.hpp"

namespace Subtile {
namespace Screen {

Subsection::Subsection(Camera &camera) :
	m_camera(camera)
{
}

Subsection::~Subsection(void)
{
}

rect2 Subsection::part(const vec2 &size)
{
	return rect2(vec2(0.0), size);
}

void Subsection::onRender(void)
{
}

}
}