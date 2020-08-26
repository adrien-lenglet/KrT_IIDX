#pragma once

#include <vector>
#include <string>

#include "Subtile/Instance.hpp"

namespace Krt {

class Config {
public:
	Config(const std::vector<std::string> &args);
	~Config(void);

	bool isProfile = false;
};

class Instance : public sb::Instance<Instance>
{
	static inline constexpr auto m_graphics_family = sb::Queue::Flag::Graphics | sb::Queue::Flag::Present;

public:
	Instance(bool isDebug, const std::vector<std::string> &args);
	~Instance(void);

	void run(void);

	sb::Queue::Handle<m_graphics_family> graphics;
	sb::Swapchain::Handle swapchain;

private:
	decltype(graphics.pool<true>()) m_transfer_pool;

public:
	decltype(m_transfer_pool.primary()) m_transfer_cmd_buf;
	sb::CommandBuffer &transfer_unsafe;
	sb::CommandBuffer::Record::Primary<sb::Queue::Flag::Graphics> transfer;

private:
	sb::Buffer::Mappable m_staging_buffer;
	size_t m_staging_off = 0;

public:
	void resetStagingOff(void)
	{
		m_staging_off = 0;
	}

	template <typename SrcType, typename Type>
	void copyBuffer(SrcType &&src, sb::Buffer::Array<Type> &dst)
	{
		auto src_size = src.size() * sizeof(decltype(*src.data()));
		m_staging_buffer.write(m_staging_off, src_size, src.data());
		transfer.copy(m_staging_buffer.region(m_staging_off, src_size), dst);
		m_staging_off += src_size;
	}

	template <typename DescSet>
	void uploadDescSet(DescSet &&set)
	{
		auto src = set.bufferData();
		auto src_size = src.size() * sizeof(decltype(*src.data()));
		m_staging_buffer.write(m_staging_off, src_size, src.data());
		transfer.copy(m_staging_buffer.region(m_staging_off, src_size), set.bufferRegion());
		m_staging_off += src_size;
	}
};

}