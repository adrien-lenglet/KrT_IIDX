#pragma once

#include <vector>
#include <tuple>
#include "util/enum_class_bitmask.hpp"
#include "util/traits.hpp"
#include "Shader.hpp"

namespace Subtile {

class CommandBuffer
{
public:
	enum class Level {
		Primary = 0x00000001,
		Secondary = 0x00000002
	};

	enum class Usage {
		Empty = 0,
		OneTimeSubmit = 0x00000001,
		Simultaneous = 0x00000004
	};

	enum class RenderPassScope {
		Inside = 0x00000001,
		Outside = 0x00000002,
		Both = Inside | Outside
	};

	virtual ~CommandBuffer(void) = default;

	virtual void reset(bool releaseResources) = 0;
	virtual void begin(Usage flags) = 0;
	virtual void end(void) = 0;

	virtual void executeCommands(size_t count, CommandBuffer **cmds) = 0;
	virtual void bindPipeline(sb::Shader &shader) = 0;
	virtual void bindDescriptorSets(sb::Shader &shader, size_t first_set, size_t count, sb::Shader::DescriptorSet **sets) = 0;

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

	class Cmds;
	class Record;
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

	struct CmdBufHandleTraits;

	struct empty_graphics { template <typename ...Args> empty_graphics(Args &&...) {} };
	struct empty_compute { template <typename ...Args> empty_compute(Args &&...) {} };
	struct empty_transfer { template <typename ...Args> empty_transfer(Args &&...) {} };
	struct empty_present { template <typename ...Args> empty_present(Args &&...) {} };
	struct empty_graphics_compute_transfer { template <typename ...Args> empty_graphics_compute_transfer(Args &&...) {} };
	struct empty_reset { template <typename ...Args> empty_reset(Args &&...) {} };

public:
	virtual ~Queue(void) = default;

	virtual std::unique_ptr<CommandPool> commandPool(bool isReset) = 0;

	enum class Flag {
		Empty = 0,
		Graphics = 0x00000001,
		Compute = 0x00000002,
		Transfer = 0x00000004,
		Present = 0x00000040
	};

	using Set = std::vector<std::pair<Queue::Flag, std::vector<float>>>;

	template <CommandBuffer::Level L, Flag Q, bool isReset>
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
			return CmdBufHandle<CommandBuffer::Level::Primary, Flags, isReset>(m_pool->commandBuffer(CommandBuffer::Level::Primary));
		}

		auto secondary(void)
		{
			return CmdBufHandle<CommandBuffer::Level::Secondary, Flags, isReset>(m_pool->commandBuffer(CommandBuffer::Level::Secondary));
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

template <>
struct util::enable_bitmask<sb::CommandBuffer::Level>
{
	static inline constexpr bool value = true;
};

template <>
struct util::enable_bitmask<sb::CommandBuffer::RenderPassScope>
{
	static inline constexpr bool value = true;
};

template <>
struct util::enable_bitmask<sb::CommandBuffer::Usage>
{
	static inline constexpr bool value = true;
};

namespace Subtile {

class CommandBuffer::Cmds
{
	static inline constexpr auto PrimarySecondary = Level::Primary | Level::Secondary;

	template <typename Up>
	class PrimaryBothGCT;

	template <typename Up>
	class PrimarySecondaryBothGC;

public:
	template <Level L, RenderPassScope S, Queue::Flag Q>
	class For;
};

class CommandBuffer::Record
{
public:
	class RenderPass
	{
	public:
		using Primary = Cmds::For<Level::Primary, RenderPassScope::Inside, Queue::Flag::Graphics>;
		using Secondary = Cmds::For<Level::Secondary, RenderPassScope::Inside, Queue::Flag::Graphics>;
	};

	template <Queue::Flag Flags>
	using Primary = Cmds::For<Level::Primary, RenderPassScope::Outside, Flags>;
	template <Queue::Flag Flags>
	using Secondary = Cmds::For<Level::Secondary, RenderPassScope::Outside, Flags>;
};

template <typename Up>
class CommandBuffer::Cmds::PrimaryBothGCT
{
	CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

public:
	PrimaryBothGCT(void) = default;

	struct GCT {
		static inline constexpr auto value = Queue::Flag::Graphics | Queue::Flag::Compute | Queue::Flag::Transfer;
	};

	struct empty {};
	template <Level L, RenderPassScope S, Queue::Flag Q>
	using query = std::conditional_t<!!(L & Level::Primary) && !!(S & RenderPassScope::Both) && !!(Q & GCT::value), PrimaryBothGCT, empty>;

	template <Queue::Flag Q, bool R>
	void execute(Queue::CmdBufHandle<Level::Secondary, Q, R> &sec_cmd)
	{
		auto commandBuffer = &CmdGetter<decltype(sec_cmd)>().get(sec_cmd);
		cmd().executeCommands(1, &commandBuffer);
	}
};

template <typename Up>
class CommandBuffer::Cmds::PrimarySecondaryBothGC
{
	CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

public:
	PrimarySecondaryBothGC(void) = default;

	struct GC {
		static inline constexpr auto value = Queue::Flag::Graphics | Queue::Flag::Compute;
	};

	struct empty {};
	template <Level L, RenderPassScope S, Queue::Flag Q>
	using query = std::conditional_t<!!(L & PrimarySecondary) && !!(S & RenderPassScope::Both) && !!(Q & GC::value), PrimarySecondaryBothGC, empty>;

	void bind(Shader &shader)
	{
		cmd().bindPipeline(shader);
	}

	void bind(Shader &shader, Shader::DescriptorSet &set, size_t index)
	{
		auto sp = &set;
		cmd().bindDescriptorSets(shader, index, 1, &sp);
	}
};

template <CommandBuffer::Level L, CommandBuffer::RenderPassScope S, Queue::Flag Q>
class CommandBuffer::Cmds::For :
	public PrimaryBothGCT<For<L, S, Q>>::template query<L, S, Q>,
	public PrimarySecondaryBothGC<For<L, S, Q>>::template query<L, S, Q>
{
public:
	For(CommandBuffer &cmd) :
		m_cmd(cmd)
	{
	}

private:
	template <typename>
	friend class CmdGetter;
	CommandBuffer &m_cmd;
};

struct Queue::CmdBufHandleTraits
{
	template <typename Up>
	class Reset
	{
		CommandBuffer& cmd(void) { return CommandBuffer::CmdGetter<Up>().get(static_cast<Up&>(*this)); }

	public:
		Reset(void) = default;

		void reset(bool releaseResources = false)
		{
			cmd().reset(releaseResources);
		}
	};

	template <typename Up, Flag Flags>
	class Primary
	{
		CommandBuffer& cmd(void) { return CommandBuffer::CmdGetter<Up>().get(static_cast<Up&>(*this)); }

	public:
		Primary(void) = default;

		using Record = CommandBuffer::Record::Primary<Flags>;

		template <typename Callable>
		void record(Callable &&callable)
		{
			Record recording(cmd());

			cmd().begin(CommandBuffer::Usage::Empty);
			callable(recording);
			cmd().end();
		}

		template <typename Callable>
		void record(CommandBuffer::Usage usage, Callable &&callable)
		{
			Record recording(cmd());

			cmd().begin(usage);
			callable(recording);
			cmd().end();
		}
	};

	template <typename Up, Flag Flags>
	class Secondary
	{
		CommandBuffer& cmd(void) { return CommandBuffer::CmdGetter<Up>().get(static_cast<Up&>(*this)); }

	public:
		Secondary(void) = default;

		using Record = CommandBuffer::Record::Secondary<Flags>;

		template <typename Callable>
		void record(Callable &&callable)
		{
			Record recording(cmd());

			cmd().begin(CommandBuffer::Usage::Empty);
			callable(recording);
			cmd().end();
		}

		template <typename Callable>
		void record(CommandBuffer::Usage usage, Callable &&callable)
		{
			Record recording(cmd());

			cmd().begin(usage);
			callable(recording);
			cmd().end();
		}
	};
};

template <CommandBuffer::Level L, Queue::Flag Q, bool isReset>
class Queue::CmdBufHandle :
	private CommandBufferHolder,
	public std::conditional_t<isReset, CmdBufHandleTraits::Reset<CmdBufHandle<L, Q, isReset>>, empty_reset>,
	public std::conditional_t<!!(L & CommandBuffer::Level::Primary), CmdBufHandleTraits::Primary<CmdBufHandle<L, Q, isReset>, Q>, CmdBufHandleTraits::Secondary<CmdBufHandle<L, Q, isReset>, Q>>
{
public:
	CmdBufHandle(std::unique_ptr<CommandBuffer> &&commandBuffer) :
		CommandBufferHolder(std::move(commandBuffer)),
		m_cmd(*m_unique_cmd)
	{
	}

private:
	template <typename>
	friend class CommandBuffer::CmdGetter;
	CommandBuffer &m_cmd;
};

}