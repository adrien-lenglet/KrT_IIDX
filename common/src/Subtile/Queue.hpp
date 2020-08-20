#pragma once

#include <vector>
#include <tuple>
#include "util/enum_class_bitmask.hpp"
#include "util/traits.hpp"

namespace Subtile {

class CommandBuffer
{
public:
	enum class Level {
		Primary,
		Secondary
	};

	virtual ~CommandBuffer(void) = default;

	virtual void reset(bool releaseResources) = 0;

	struct Capacity
	{
		template <typename Type>
		class CmdGetter
		{
		public:
			CmdGetter(void) = default;

			CommandBuffer& get(Type &value)
			{
				return value.m_cmd;
			}
		};

		template <typename Up>
		class GraphicsComputeTransfer
		{
			CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

		public:
			GraphicsComputeTransfer(void) = default;
		};

		template <typename Up>
		class Graphics
		{
			CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

		public:
			Graphics(void) = default;
		};

		template <typename Up>
		class Transfer
		{
			CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

		public:
			Transfer(void) = default;
		};

		template <typename Up>
		class Compute
		{
			CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

		public:
			Compute(void) = default;
		};

		template <typename Up>
		class Present
		{
			CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

		public:
			Present(void) = default;
		};

		template <typename Up>
		class Reset
		{
			CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

		public:
			Reset(void) = default;

			
			void reset(bool releaseResources = false)
			{
				cmd().reset(releaseResources);
			}
		};
	};

	class Graphics : public Capacity::Graphics<Graphics>, public Capacity::GraphicsComputeTransfer<Graphics>
	{
	public:
		struct empty { template <typename ...Args> empty(Args &&...) {} };

		Graphics(CommandBuffer &cmd) :
			m_cmd(cmd)
		{
			static_cast<void>(m_cmd);
		}

	private:
		template <typename>
		friend class Capacity::CmdGetter;
		CommandBuffer &m_cmd;
	};

	class Compute : public Capacity::Compute<Compute>, public Capacity::GraphicsComputeTransfer<Compute>
	{
	public:
		struct empty { template <typename ...Args> empty(Args &&...) {} };

		Compute(CommandBuffer &cmd) :
			m_cmd(cmd)
		{
			static_cast<void>(m_cmd);
		}

	private:
		template <typename>
		friend class CmdGetter;
		CommandBuffer &m_cmd;
	};

	class Transfer : public Capacity::Transfer<Transfer>, public Capacity::GraphicsComputeTransfer<Transfer>
	{
	public:
		struct empty { template <typename ...Args> empty(Args &&...) {} };

		Transfer(CommandBuffer &cmd) :
			m_cmd(cmd)
		{
			static_cast<void>(m_cmd);
		}

	private:
		template <typename>
		friend class CmdGetter;
		CommandBuffer &m_cmd;
	};

	class Present : public Capacity::Present<Present>
	{
	public:
		struct empty { template <typename ...Args> empty(Args &&...) {} };

		Present(CommandBuffer &cmd) :
			m_cmd(cmd)
		{
			static_cast<void>(m_cmd);
		}

	private:
		template <typename>
		friend class CmdGetter;
		CommandBuffer &m_cmd;
	};
};

class CommandPool
{
public:
	virtual ~CommandPool(void) = default;

	virtual std::unique_ptr<CommandBuffer> commandBuffer(CommandBuffer::Level level) = 0;
};

class Queue
{
	class CommandBufferHolder
	{
	public:
		template <typename ...Args>
		CommandBufferHolder(Args &&...args) :
			m_unique_cmd(std::forward<Args>(args)...)
		{
		}

	protected:
		std::unique_ptr<CommandBuffer> m_unique_cmd;
	};

	struct empty_graphics { template <typename ...Args> empty_graphics(Args &&...) {} };
	struct empty_compute { template <typename ...Args> empty_compute(Args &&...) {} };
	struct empty_transfer { template <typename ...Args> empty_transfer(Args &&...) {} };
	struct empty_present { template <typename ...Args> empty_present(Args &&...) {} };

public:
	virtual ~Queue(void) = default;

	virtual std::unique_ptr<CommandPool> commandPool(bool isReset) = 0;

	enum class Flag {
		Graphics = 0x00000001,
		Compute = 0x00000002,
		Transfer = 0x00000004,
		Present = 0x00000040
	};

	using Set = std::vector<std::pair<Queue::Flag, std::vector<float>>>;

	template <Flag Flags, bool isReset>
	class CmdBufHandle;

	template <Flag Flags, bool isReset>
	class CmdPoolHandle
	{
	public:
		CmdPoolHandle(std::unique_ptr<CommandPool> &&pool) :
			m_pool(std::move(pool))
		{
		}

		auto primary(void)
		{
			return CmdBufHandle<Flags, isReset>(m_pool->commandBuffer(CommandBuffer::Level::Primary));
		}

		auto secondary(void)
		{
			return CmdBufHandle<Flags, isReset>(m_pool->commandBuffer(CommandBuffer::Level::Secondary));
		}

	private:
		std::unique_ptr<CommandPool> m_pool;
	};

	template <Flag Flags>
	class Handle
	{
	public:
		Handle(std::unique_ptr<Queue> &&queue) :
			m_queue(std::move(queue))
		{
		}

		operator Flag(void) const
		{
			return Flags;
		}

		template <bool isReset>
		auto pool(void)
		{
			return CmdPoolHandle<Flags, isReset>(m_queue->commandPool(isReset));
		}

	private:
		std::unique_ptr<Queue> m_queue;
	};
};

}

template <>
struct util::enable_bitmask<sb::Queue::Flag>
{
	static inline constexpr bool value = true;
};

namespace Subtile {

template <Queue::Flag Flags, bool isReset>
class Queue::CmdBufHandle :
	private CommandBufferHolder,
	public std::conditional_t<!!(Flags & Flag::Graphics), CommandBuffer::Capacity::Graphics<CmdBufHandle<Flags, isReset>>, empty_graphics>,
	public std::conditional_t<!!(Flags & Flag::Compute), CommandBuffer::Capacity::Compute<CmdBufHandle<Flags, isReset>>, empty_compute>,
	public std::conditional_t<!!(Flags & Flag::Transfer), CommandBuffer::Capacity::Transfer<CmdBufHandle<Flags, isReset>>, empty_transfer>,
	public std::conditional_t<!!(Flags & Flag::Present), CommandBuffer::Capacity::Present<CmdBufHandle<Flags, isReset>>, empty_present>,

	public std::conditional_t<!!(Flags & Flag::Graphics) || !!(Flags & Flag::Compute) || !!(Flags & Flag::Transfer), CommandBuffer::Capacity::GraphicsComputeTransfer<CmdBufHandle<Flags, isReset>>, empty_present>,

	public std::conditional_t<isReset, CommandBuffer::Capacity::Reset<CmdBufHandle<Flags, isReset>>, util::empty_struct>
{
	using Graphics = std::conditional_t<!!(Flags & Flag::Graphics), CommandBuffer::Graphics, CommandBuffer::Graphics::empty>;
	using Compute = std::conditional_t<!!(Flags & Flag::Compute), CommandBuffer::Compute, CommandBuffer::Compute::empty>;
	using Transfer = std::conditional_t<!!(Flags & Flag::Transfer), CommandBuffer::Transfer, CommandBuffer::Transfer::empty>;
	using Present = std::conditional_t<!!(Flags & Flag::Present), CommandBuffer::Present, CommandBuffer::Present::empty>;

public:
	CmdBufHandle(std::unique_ptr<CommandBuffer> &&commandBuffer) :
		CommandBufferHolder(std::move(commandBuffer)),
		m_cmd(*m_unique_cmd),
		m_graphics(m_cmd),
		m_compute(m_cmd),
		m_transfer(m_cmd),
		m_present(m_cmd)
	{
	}

	operator Graphics&(void)
	{
		return m_graphics;
	}
	operator Compute&(void)
	{
		return m_compute;
	}
	operator Transfer&(void)
	{
		return m_transfer;
	}
	operator Present&(void)
	{
		return m_present;
	}

private:
	template <typename>
	friend class CommandBuffer::Capacity::CmdGetter;
	CommandBuffer &m_cmd;

	Graphics m_graphics;
	Compute m_compute;
	Transfer m_transfer;
	Present m_present;
};

}