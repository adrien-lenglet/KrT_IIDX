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

private:
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
		CommandBuffer& cmd(void)
		{
			return CmdGetter<Up>().get(static_cast<Up&>(*this));
		}

	public:
		GraphicsComputeTransfer(void) = default;

		static inline constexpr bool graphics_compute_transfer = true;
	};

public:
	class Graphics : public GraphicsComputeTransfer<Graphics>
	{
	public:
		Graphics(CommandBuffer &cmd) :
			m_cmd(cmd)
		{
			static_cast<void>(m_cmd);
		}

		static inline constexpr bool graphics = true;

	private:
		template <typename>
		friend class CmdGetter;
		CommandBuffer &m_cmd;
	};

	class Compute : public GraphicsComputeTransfer<Compute>
	{
	public:
		Compute(CommandBuffer &cmd) :
			m_cmd(cmd)
		{
			static_cast<void>(m_cmd);
		}

		static inline constexpr bool compute = true;

	private:
		template <typename>
		friend class CmdGetter;
		CommandBuffer &m_cmd;
	};

	class Transfer : public GraphicsComputeTransfer<Transfer>
	{
	public:
		Transfer(CommandBuffer &cmd) :
			m_cmd(cmd)
		{
			static_cast<void>(m_cmd);
		}

		static inline constexpr bool transfer = true;

	private:
		template <typename>
		friend class CmdGetter;
		CommandBuffer &m_cmd;
	};

	class Present
	{
	public:
		Present(CommandBuffer &cmd) :
			m_cmd(cmd)
		{
			static_cast<void>(m_cmd);
		}

		static inline constexpr bool present = true;

	private:
		template <typename>
		friend class CmdGetter;
		CommandBuffer &m_cmd;
	};
};

class Queue
{
	class CommandBufferHolder
	{
	public:
		template <typename ...Args>
		CommandBufferHolder(Args &&...args) :
			m_cmd(std::forward<Args>(args)...)
		{
		}

	protected:
		std::unique_ptr<CommandBuffer> m_cmd;
	};

public:
	virtual ~Queue(void) = default;

	virtual std::unique_ptr<CommandBuffer> commandBuffer(CommandBuffer::Level level) = 0;

	enum class Flag {
		Graphics = 0x00000001,
		Compute = 0x00000002,
		Transfer = 0x00000004,
		Present = 0x10000000
	};

	using Set = std::vector<std::pair<Queue::Flag, std::vector<float>>>;

	template <Flag Flags>
	class CmdBufHandle;

	template <Flag Flags>
	class Handle
	{
	public:
		Handle(std::unique_ptr<Queue> &&queue) :
			m_queue(std::move(queue))
		{
		}

		auto primary(void)
		{
			return CmdBufHandle<Flags>(m_queue->commandBuffer(CommandBuffer::Level::Primary));
		}

		auto secondary(void)
		{
			return CmdBufHandle<Flags>(m_queue->commandBuffer(CommandBuffer::Level::Secondary));
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

template <Queue::Flag Flags>
class Queue::CmdBufHandle : private CommandBufferHolder,
	public util::conditional_un_t<!!(Flags & Flag::Graphics), CommandBuffer::Graphics>,
	public util::conditional_un_t<!!(Flags & Flag::Compute), CommandBuffer::Compute>,
	public util::conditional_un_t<!!(Flags & Flag::Transfer), CommandBuffer::Transfer>,
	public util::conditional_un_t<!!(Flags & Flag::Present), CommandBuffer::Present>
{
public:
	CmdBufHandle(std::unique_ptr<CommandBuffer> &&commandBuffer) :
		CommandBufferHolder(std::move(commandBuffer)),
		util::conditional_un_t<!!(Flags & Flag::Graphics), CommandBuffer::Graphics>(*m_cmd),
		util::conditional_un_t<!!(Flags & Flag::Compute), CommandBuffer::Compute>(*m_cmd),
		util::conditional_un_t<!!(Flags & Flag::Transfer), CommandBuffer::Transfer>(*m_cmd),
		util::conditional_un_t<!!(Flags & Flag::Present), CommandBuffer::Present>(*m_cmd)
	{
	}
};

}