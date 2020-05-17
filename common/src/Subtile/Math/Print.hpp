#pragma once

#include "../Math.hpp"

#include <iostream>

template <Subtile::math::length_t w, Subtile::math::length_t h, typename Contained>
std::ostream& operator<<(std::ostream &o, const Subtile::math::mat<w, h, Contained> &mat)
{
	for (size_t i = 0; i < h; i++) {
		for (size_t j = 0; j < w; j++)
			o  << mat[j][i] << "\t";
		o << std::endl;
	}
	return o;
}