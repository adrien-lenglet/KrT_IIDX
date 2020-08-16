#pragma once

#include "../Subtile.hpp"

namespace Subtile {

enum class Format {
	bgra4_unorm_pack16,
	r5g6b5_unorm_pack16,
	a1rgb5_unorm_pack16,

	r8_unorm,
	r8_snorm,
	r8_uint,
	r8_sint,

	rg8_unorm,
	rg8_snorm,
	rg8_uint,
	rg8_sint,

	rgba8_unorm,
	rgba8_snorm,
	rgba8_uint,
	rgba8_sint,
	rgba8_srgb,

	bgra8_unorm,
	bgra8_srgb,

	abgr8_unorm_pack32,
	abgr8_snorm_pack32,
	abgr8_uint_pack32,
	abgr8_sint_pack32,
	abgr8_srgb_pack32,

	a2bgr10_unorm_pack32,
	a2bgr10_uint_pack32,

	r16_uint,
	r16_sint,
	r16_sfloat,

	rg16_uint,
	rg16_sint,
	rg16_sfloat,

	rgba16_uint,
	rgba16_sint,
	rgba16_sfloat,

	r32_uint,
	r32_sint,
	r32_sfloat,

	rg32_uint,
	rg32_sint,
	rg32_sfloat,

	rgba32_uint,
	rgba32_sint,
	rgba32_sfloat,

	d16_unorm,
	d32_sfloat,

	/* special conditional formats, they must be resolved by ISystem */
	d24un_or_32sf_spl_att,  // sampled and depth attachment, d24_unorm preferred
	d32sf_or_24un_spl_att,	// d32_sfloat preferred

	d24un_or_32sf_spl_att_sfb,	// stencil fallback: stencil formats may be used if depth only if !(sampled && depth_attachment)
	d32sf_or_24un_spl_att_sfb,

	d24un_or_32sf_spl_att_s8_uint,	// with stencil
	d32sf_or_24un_spl_att_s8_uint
};

}