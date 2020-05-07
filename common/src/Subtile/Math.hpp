#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Subtile {

// Logical vector types
// Double are suited for their precision
using vec2 = glm::dvec2;
using vec3 = glm::dvec3;

// Render vector types
// Floats are the only option
using rvec2 = glm::vec2;
using rvec3 = glm::vec3;

template <typename FloatVec2Type>
class frect2
{
public:
	using vec2_type = FloatVec2Type;
	using value_type = typename vec2_type::value_type;

	frect2(const FloatVec2Type &pos, const FloatVec2Type &size) :
		pos(pos),
		size(size)
	{
	}
	~frect2(void)
	{
	}

	frect2 operator*(const value_type &value) const
	{
		return frect2(pos * value, size * value);
	}

	frect2 operator*(const vec2_type &value) const
	{
		return frect2(pos * value, size * value);
	}

	FloatVec2Type pos;
	FloatVec2Type size;
};

using rect2 = frect2<vec2>;
using rrect2 = frect2<rvec2>;

}