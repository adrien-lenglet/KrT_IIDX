#pragma once

#include "util/enum_class_bitmask.hpp"
#include "../Subtile.hpp"

namespace Subtile {

enum class DependencyFlag {
	None = 0,
	ByRegion = 0x00000001
};

}

template <>
struct util::enable_bitmask<sb::DependencyFlag>
{
	static inline constexpr bool value = true;
};