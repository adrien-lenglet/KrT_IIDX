#pragma once

#include <vector>
#include <tuple>
#include "util/enum_class_bitmask.hpp"

namespace Subtile {

class Queue
{
public:
	virtual ~Queue(void) = default;

	enum class Flag {
		Present = 0x10000000,
		Graphics = 0x00000001,
		Compute = 0x00000002,
		Transfer = 0x00000004
	};

	using Set = std::vector<std::pair<Queue::Flag, std::vector<float>>>;
};

}

template <>
struct util::enable_bitmask<sb::Queue::Flag>
{
	static inline constexpr bool value = true;
};