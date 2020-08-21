#pragma once

#include "../Subtile.hpp"
#include "Math.hpp"
#include "Format.hpp"
#include "util/enum_class_bitmask.hpp"

namespace Subtile {

class Queue;

class Image
{
public:
	enum class Layout {
		Undefined = 0,
		General = 1,

		ColorAttachmentOptimal = 2,
		DepthStencilAttachmentOptimal = 3,
		DepthStencilReadOnlyOptimal = 4,
		ShaderReadOnlyOptimal = 5,
		TransferSrcOptimal = 6,
		TransferDstOptimal = 7,

		Preinitialized = 8,

		PresentSrc = 1000001002
	};

	enum class Sample {
		Count1 = 0x00000001,
		Count2 = 0x00000002,
		Count4 = 0x00000004,
		Count8 = 0x00000008,
		Count16 = 0x00000010,
		Count32 = 0x00000020,
		Count64 = 0x00000040
	};
	
	enum class LoadOp {
		DontCare,
		Load,
		Clear
	};

	enum class StoreOp {
		DontCare,
		Store
	};

	enum class Usage {
		TransferSrc = 0x00000001,
		TransferDst = 0x00000002,
		Sampled = 0x00000004,
		Storage = 0x00000008,
		ColorAttachment = 0x00000010,
		DepthStencilAttachment = 0x00000020,
		TranscientAttachment = 0x00000040,
		InputAttachment = 0x00000080
	};

	enum class Type {
		Image1D = 0,
		Image2D = 1,
		Image3D = 2,
		Cube = 3,
		Image1DArray = 4,
		Image2DArray = 5,
		CubeArray = 6
	};

	virtual ~Image(void) = default;
};

class Image2D
{
public:
	Image2D(std::unique_ptr<Image> &&image) :
		m_image(std::move(image))
	{
	}

private:
	std::unique_ptr<Image> m_image;
};

class Image2DArray
{
public:
	Image2DArray(std::unique_ptr<Image> &&image) :
		m_image(std::move(image))
	{
	}

private:
	std::unique_ptr<Image> m_image;
};

}

template <>
struct util::enable_bitmask<sb::Image::Usage>
{
	static inline constexpr bool value = true;
};