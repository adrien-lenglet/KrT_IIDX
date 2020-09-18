#pragma once

#define GLM_CONFIG_ALIGNED_GENTYPES 1
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/quaternion_double.hpp>
#include <cmath>
#include "../Subtile.hpp"

namespace Subtile {

static inline constexpr double pi = 3.141592653589793238462643383279502884;

template <typename RndGen>
static inline glm::vec3 genDiffuseVector(RndGen &&gen, const glm::vec3 &up, double n)
{
	auto a0 = std::acos(std::pow(gen.urandf(), 1.0 / (n + 1.0)));
	auto a1 = 2.0 * sb::pi * gen.urandf();
	auto sa0 = std::sin(a0);
	auto ca0 = std::cos(a0);
	auto sa1 = std::sin(a1);
	auto ca1 = std::cos(a1);
	auto base_diffuse = glm::vec3(sa0 * ca1, sa0 * sa1, ca0);

	glm::vec3 nx = glm::vec3(-up.z, up.x, up.y);
	glm::vec3 ny = glm::vec3(up.x, -up.z, up.y);
	glm::vec3 nz = up;

	return base_diffuse.x * nx + base_diffuse.y * ny + base_diffuse.z * nz;
}

namespace math = glm;

// Logical vector types
// Double are suited for their precision
using vec2 = math::dvec2;
using vec3 = math::dvec3;

// Render vector types
// Floats are the only option
using rvec2 = math::vec2;
using rvec3 = math::vec3;

template <typename FloatVec2Type>
class frect2
{
public:
	using vec2_type = FloatVec2Type;
	using value_type = typename vec2_type::value_type;

	frect2(const FloatVec2Type &offset, const FloatVec2Type &extent) :
		offset(offset),
		extent(extent)
	{
	}
	~frect2(void)
	{
	}

	auto operator*(const value_type &value) const
	{
		return frect2(offset * value, extent * value);
	}

	auto operator*(const vec2_type &value) const
	{
		return frect2(offset * value, extent * value);
	}

	FloatVec2Type offset;
	FloatVec2Type extent;
};

using rect2 = frect2<vec2>;
using rrect2 = frect2<rvec2>;

using quat = math::dquat;

using mat4 = math::dmat4;
using rmat4 = math::mat4;

using svec2 = glm::vec<2, size_t>;
using svec3 = glm::vec<3, size_t>;

struct srect2
{
	srect2(const svec2 &offset, const svec2 &extent) :
		offset(offset),
		extent(extent)
	{
	}

	svec2 offset;
	svec2 extent;
};

struct srect3
{
	srect3(const svec3 &offset, const svec3 &extent) :
		offset(offset),
		extent(extent)
	{
	}

	svec3 offset;
	svec3 extent;
};

}