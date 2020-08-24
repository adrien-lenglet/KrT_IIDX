#pragma once

#include "Math.hpp"

namespace Subtile {

union Color
{
	using f32 = glm::vec4;
	using u32 = glm::uvec4;
	using i32 = glm::ivec4;

	Color(void) = default;
	Color(const f32 &fl) :
		fl(fl)
	{
	}
	Color(const u32 &u) :
		u(u)
	{
	}
	Color(const i32 &i) :
		i(i)
	{
	}

	f32 fl;
	u32 u;
	i32 i;
};

struct DepthStencil
{
	DepthStencil(void) = default;
	DepthStencil(float depth, uint32_t stencil) :
		depth(depth),
		stencil(stencil)
	{
	}

	float depth;
	uint32_t stencil;
};

union ClearValue
{
public:
	ClearValue(void) = default;
	ClearValue(const Color::f32 &vec) :
		color(vec)
	{
	}
	ClearValue(const Color::u32 &vec) :
		color(vec)
	{
	}
	ClearValue(const Color::i32 &vec) :
		color(vec)
	{
	}
	ClearValue(float depth) :
		depthStencil(depth, 0)
	{
	}
	ClearValue(uint32_t stencil) :
		depthStencil(0.0f, stencil)
	{
	}
	ClearValue(const DepthStencil &ds) :
		depthStencil(ds)
	{
	}

	Color color;
	DepthStencil depthStencil;
};

}