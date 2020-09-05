#pragma once

#include "../Subtile.hpp"
#include "Math.hpp"
#include "Format.hpp"
#include "util/enum_class_bitmask.hpp"

namespace Subtile {

class Queue;

enum class ComponentSwizzle {
	Identity = 0,
	Zero = 1,
	One = 2,
	R = 3,
	G = 4,
	B = 5,
	A = 6
};

class ComponentMapping : public glm::vec<4, ComponentSwizzle>
{
public:
	ComponentMapping(ComponentSwizzle r, ComponentSwizzle g, ComponentSwizzle b, ComponentSwizzle a) :
		glm::vec<4, ComponentSwizzle>(r, g, b, a)
	{
	}
	ComponentMapping(ComponentSwizzle vec) :
		glm::vec<4, ComponentSwizzle>(vec, vec, vec, vec)
	{
	}
};

struct WholeRange {};
static inline constexpr WholeRange wholeRange{};

struct Range
{
public:
	Range(size_t off, size_t size) :
		off(off),
		size(size),
		isWhole(false)
	{
	}

	Range(WholeRange) :
		off(0),
		size(0),
		isWhole(true)
	{
	}

	Range(size_t off, WholeRange) :
		off(off),
		size(0),
		isWhole(true)
	{
	}

	size_t off;
	size_t size;
	bool isWhole;
};

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

	enum class Aspect {
		Color = 0x00000001,
		Depth = 0x00000002,
		Stencil = 0x00000004
	};

	struct AllMipLevels {};
	static inline constexpr AllMipLevels allMipLevels{};

	struct MipmapLevels
	{
		MipmapLevels(size_t levels) :
			isFull(false),
			levels(levels)
		{
		}
		MipmapLevels(AllMipLevels) :
			isFull(true),
			levels(0)
		{
		}

		bool isFull;
		size_t levels;
	};

	class Handle;

	virtual ~Image(void) = default;

	virtual std::unique_ptr<Image> createView(Type type, const ComponentMapping &components, Aspect aspect, const Range &arrayRange, const Range &mipRange) const = 0;
	virtual size_t getArrayLayers(void) const = 0;
	virtual size_t getMipLevels(void) const = 0;
	virtual const svec3& getExtent(void) const = 0;
};

class Image::Handle
{
public:
	Handle(std::unique_ptr<Image> &&image) :
		m_image(std::move(image))
	{
	}

	operator Image&(void)
	{
		return *m_image;
	}

	size_t mipLevels(void) const
	{
		return image().getMipLevels();
	}

protected:
	Image& image(void)
	{
		return *m_image;
	}
	Image& image(void) const
	{
		return *m_image;
	}

private:
	std::unique_ptr<Image> m_image;
};

// layers = 1, mips >= 1, samples = 1
class Image2D : public Image::Handle
{
public:
	template <typename ...Args>
	Image2D(Args &&...args) :
		Image::Handle(std::forward<Args>(args)...)
	{
	}

	auto view(const ComponentMapping &components, Image::Aspect aspect, const Range &mipRange)
	{
		return Image2D(image().createView(Image::Type::Image2D, components, aspect, wholeRange, mipRange));
	}

	svec2 extent(void) const
	{
		auto &e = image().getExtent();
		return svec2(e.x, e.y);
	}
};

// layers = 1, mips >= 1, samples > 1
class Image2DMS : public Image::Handle
{
public:
	template <typename ...Args>
	Image2DMS(Args &&...args) :
		Image::Handle(std::forward<Args>(args)...)
	{
	}

	svec2 extent(void) const
	{
		auto &e = image().getExtent();
		return svec2(e.x, e.y);
	}

	auto view(const ComponentMapping &components, Image::Aspect aspect, const Range &mipRange)
	{
		return Image2DMS(image().createView(Image::Type::Image2D, components, aspect, wholeRange, mipRange));
	}
};

// layers >= 1, mips >= 1, samples = 1
class Image2DArray : public Image::Handle
{
public:
	template <typename ...Args>
	Image2DArray(Args &&...args) :
		Image::Handle(std::forward<Args>(args)...)
	{
	}

	svec2 extent(void) const
	{
		auto &e = image().getExtent();
		return svec2(e.x, e.y);
	}

	size_t size(void) const
	{
		return image().getArrayLayers();
	}

	auto view(const ComponentMapping &components, Image::Aspect aspect, const Range &arrayRange, const Range &mipRange)
	{
		return Image2DArray(image().createView(Image::Type::Image2DArray, components, aspect, arrayRange, mipRange));
	}

	auto viewElem(size_t index, const ComponentMapping &components, Image::Aspect aspect, const Range &mipRange)
	{
		return Image2D(image().createView(Image::Type::Image2D, components, aspect, Range(index, 1), mipRange));
	}
};

// layers >= 1, mips >= 1, samples > 1
class Image2DMSArray : public Image::Handle
{
public:
	template <typename ...Args>
	Image2DMSArray(Args &&...args) :
		Image::Handle(std::forward<Args>(args)...)
	{
	}

	svec2 extent(void) const
	{
		auto &e = image().getExtent();
		return svec2(e.x, e.y);
	}

	size_t size(void) const
	{
		return image().getArrayLayers();
	}

	auto view(const ComponentMapping &components, Image::Aspect aspect, const Range &arrayRange, const Range &mipRange)
	{
		return Image2DMSArray(image().createView(Image::Type::Image2DArray, components, aspect, arrayRange, mipRange));
	}

	auto viewElem(size_t index, const ComponentMapping &components, Image::Aspect aspect, const Range &mipRange)
	{
		return Image2DMS(image().createView(Image::Type::Image2D, components, aspect, Range(index, 1), mipRange));
	}
};

}

template <>
struct util::enable_bitmask<sb::Image::Usage>
{
	static inline constexpr bool value = true;
};

template <>
struct util::enable_bitmask<sb::Image::Aspect>
{
	static inline constexpr bool value = true;
};