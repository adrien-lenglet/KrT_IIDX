#pragma once

#include <memory>
#include "../Subtile.hpp"
#include "util/enum_class_bitmask.hpp"

namespace Subtile {

enum class Filter {
	Nearest = 0,
	Linear = 1
};

class Sampler
{
public:
	virtual ~Sampler(void) = default;

	enum class MipmapMode {
		Nearest = 0,
		Linear = 1
	};

	enum class AddressMode {
		Repeat = 0,
		MirroredRepeat = 1,
		ClampToEdge = 2,
		ClampToBorder = 3
	};

	class Handle
	{
	public:
		Handle(std::unique_ptr<Sampler> &&sampler) :
			m_sampler(std::move(sampler))
		{
		}

		operator Sampler&(void)
		{
			return *m_sampler;
		}

	private:
		std::unique_ptr<Sampler> m_sampler;
	};
};

}