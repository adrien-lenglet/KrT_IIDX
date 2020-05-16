#include "Subsection.hpp"

#include <iostream>

namespace Subtile {
namespace Screen {

Subsection::Subsection(Camera &camera) :
	m_camera(camera)
{
	std::cout << "Camera: " << &m_camera << std::endl;
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