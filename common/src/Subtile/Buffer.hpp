#pragma once

#include <memory>
#include "../Subtile.hpp"
#include "util/enum_class_bitmask.hpp"

namespace Subtile {

class Buffer
{
public:
	virtual ~Buffer(void) = default;

	virtual void write(size_t off, size_t size, const void *data) = 0;

	enum class Usage {
		TransferSrc = 0x00000001,
		TransferDst = 0x00000002,
		UniformTexelBuffer = 0x00000004,
		StorageTexelBuffer = 0x00000008,
		UniformBuffer = 0x00000010,
		StorageBuffer = 0x00000020,
		IndexBuffer = 0x00000040,
		VertexBuffer = 0x00000080,
		IndirectBuffer = 0x00000100
	};

	enum class Location {
		Device,
		Host
	};

	struct Region
	{
		Region(Buffer &buffer, size_t offset, size_t size) :
			buffer(buffer),
			offset(offset),
			size(size)
		{
		}

		Buffer &buffer;
		size_t offset;
		size_t size;
	};

	class Handle
	{
	public:
		Handle(std::unique_ptr<Buffer> &&buffer, size_t size) :
			m_buffer(std::move(buffer)),
			m_size(size)
		{
		}

		operator Buffer&(void)
		{
			return *m_buffer;
		}

		auto region(size_t offset, size_t size)
		{
			return Region(*m_buffer, offset, size);
		}

		auto size(void) const
		{
			return m_size;
		}

		operator Region(void)
		{
			return region(0, m_size);
		}

	private:
		std::unique_ptr<Buffer> m_buffer;
		size_t m_size;
	};

	class Mappable : public Handle
	{
	public:
		template <typename ...Args>
		Mappable(Args &&...args) :
			Handle(std::forward<Args>(args)...)
		{
		}

		void write(size_t off, size_t size, const void *data)
		{
			Buffer &buf = *this;
			buf.write(off, size, data);
		}
	};

	template <typename T>
	class Array : public Handle
	{
	public:
		using value_type = T;

		template <typename ...Args>
		Array(Args &&...args) :
			Handle(std::forward<Args>(args)...)
		{
		}

		auto size(void) const
		{
			return static_cast<Handle&>(*this).size() / sizeof(T);
		}
	};

	template <typename VertexType>
	using Vertex = Array<VertexType>;

	using Index16 = Array<uint16_t>;
	using Index32 = Array<uint32_t>;
};

}

template <>
struct util::enable_bitmask<sb::Buffer::Usage>
{
	static inline constexpr bool value = true;
};