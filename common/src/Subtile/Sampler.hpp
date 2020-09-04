#pragma once

#include <memory>
#include "../Subtile.hpp"
#include "util/enum_class_bitmask.hpp"

namespace Subtile {

enum class Filter {
	Nearest = 0,
	Linear = 1
};

enum class BorderColor {
	FloatTransparentBlack = 0,
	IntTransparentBlack = 1,
	FloatOpaqueBlack = 2,
	IntOpaqueBlack = 3,
	FloatOpaqueWhite = 4,
	IntOpaqueWhite = 5
};

enum class CompareOp {
	Never = 0,
	Less = 1,
	Equal = 2,
	LessOrEqual = 3,
	Greater = 4,
	NotEqual = 5,
	GreaterOrEqual = 6,
	Always = 7
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

	class AddressModeUVW : public glm::vec<3, AddressMode>
	{
	public:
		AddressModeUVW(AddressMode u, AddressMode v, AddressMode w) :
			glm::vec<3, AddressMode>(u, v, w)
		{
		}
		AddressModeUVW(AddressMode vec) :
			glm::vec<3, AddressMode>(vec, vec, vec)
		{
		}
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