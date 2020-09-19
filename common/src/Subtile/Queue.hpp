#pragma once

#include <vector>
#include <tuple>
#include "util/enum_class_bitmask.hpp"
#include "util/traits.hpp"
#include "Shader.hpp"
#include "Framebuffer.hpp"
#include "Swapchain.hpp"
#include "Semaphore.hpp"
#include "Fence.hpp"
#include "Buffer.hpp"
#include "PipelineStage.hpp"
#include "Access.hpp"
#include "DependencyFlag.hpp"

namespace Subtile {

class CommandBuffer
{
public:
	enum class Level {
		Neither = 0,
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
	virtual void beginRender(Usage flags, Framebuffer &fb, size_t subpass) = 0;
	virtual void beginRender(Usage flags, RenderPass &rp, size_t subpass) = 0;
	virtual void end(void) = 0;

	virtual void executeCommands(size_t count, CommandBuffer **cmds) = 0;
	virtual void bindPipeline(sb::Shader &shader) = 0;
	virtual void bindDescriptorSets(sb::Shader &shader, size_t first_set, size_t count, sb::Shader::DescriptorSet **sets) = 0;

	virtual void beginRenderPass(bool isInline, Framebuffer &fb, const srect2 &renderArea, size_t clearValueCount, ClearValue *clearValues) = 0;
	virtual void nextSubpass(bool isInline) = 0;
	virtual void endRenderPass(void) = 0;

	template <typename CommandsType>
	void beginRenderPassCmds(Framebuffer &fb, const srect2 &renderArea, size_t clearValueCount, sb::ClearValue *clearValues, CommandsType &&commands);
	template <typename CommandsType>
	void nextSubpassCmds(CommandsType &&commands);

	virtual void copy(const Buffer::Region &src, const Buffer::Region &dst) = 0;

	virtual void memoryBarrier(PipelineStage srcStageMask, PipelineStage dstStageMask, DependencyFlag flags, Access srcAccessMask, Access dstAccessMask) = 0;
	virtual void imageMemoryBarrier(PipelineStage srcStageMask, PipelineStage dstStageMask, DependencyFlag flags, Access srcAccessMask, Access dstAccessMask, Image::Layout oldLayout, Image::Layout newLayout, Image &image) = 0;

	virtual void setViewport(const rect2 &area, float minDepth, float maxDepth) = 0;
	virtual void setScissor(const srect2 &scissor) = 0;

	virtual void blit(sb::Image &srcImage, sb::Image::Layout srcLayout, const srect3 &srcRegion, sb::Image &dstImage, sb::Image::Layout dstLayout, const srect3 &dstRegion, Filter filter) = 0;
	virtual void copyBufferToImage(const Buffer::Region &srcBuffer, sb::Image &dstImage, sb::Image::Layout dstImageLayout, const srect3 &dstRegion) = 0;

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

	template <typename>
	struct SubmitWaitSemaphorePredicate
	{
		static inline constexpr auto value = false;
	};

	struct SubmitWaitSemaphoreConverter
	{
		template <typename PairType>	// [std::pair<Semaphore::Handle*, PipelineStage] assumed
		static auto convert(PairType &&pair)
		{
			return std::pair<Semaphore*, PipelineStage>(&static_cast<Semaphore&>(*pair.first), pair.second);
		}
	};

	template <typename>
	struct SubmitSemaphorePredicate
	{
		static inline constexpr auto value = false;
	};

	struct SubmitSemaphoreConverter
	{
		static auto convert(Semaphore::Handle &handle)
		{
			return &static_cast<Semaphore&>(handle);
		}
	};

public:
	virtual ~Queue(void) = default;

	virtual std::unique_ptr<CommandPool> commandPool(bool isReset) = 0;
	struct SubmitInfo
	{
		size_t waitSemaphoreCount;
		std::pair<Semaphore*, PipelineStage> *waitSemaphores;
		size_t commandBufferCount;
		CommandBuffer **commandBuffers;
		size_t signalSemaphoreCount;
		Semaphore **signalSemaphores;
	};
	virtual void submit(size_t submitCount, SubmitInfo *submits, sb::Fence *fence) = 0;
	virtual void present(size_t waitSemaphoreCount, Semaphore **waitSemaphores, Swapchain::Image2D &image) = 0;
	virtual void waitIdle(void) = 0;

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

	template <typename>
	struct isCmdBufHandle
	{
		static inline constexpr auto value = false;
	};

	struct CmdBufHandleToCommandBufferPtr;

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

		operator Queue&(void)
		{
			return *m_queue;
		}

		template <bool isReset>
		auto pool(void)
		{
			return CmdPoolHandle<Flags, isReset>(m_queue->commandPool(isReset));
		}

		struct SubmitFill
		{
			SubmitInfo *submitInfo;
			std::pair<Semaphore*, PipelineStage> *waitSemaphores;
			CommandBuffer **commandBuffers;
			Semaphore **signalSemaphores;
		};

		template <typename WaitSemaphoresType, typename CommandBuffersType, typename SignalSemaphoresType, typename ...Args>
		void submit(WaitSemaphoresType &&waitSemaphores, CommandBuffersType &&commandBuffers, SignalSemaphoresType &&signalSemaphores, Args &&...args)
		{
			auto count = submitGetCount(std::forward<WaitSemaphoresType>(waitSemaphores), std::forward<CommandBuffersType>(commandBuffers), std::forward<SignalSemaphoresType>(signalSemaphores), std::forward<Args>(args)...);
			SubmitInfo submits_vla[count.submits];
			std::pair<Semaphore*, PipelineStage> waitSemaphores_vla[count.waitSemaphores];
			CommandBuffer *commandBuffers_vla[count.commandBuffers];
			Semaphore *signalSemaphores_vla[count.signalSemaphores];

			SubmitFill buf {submits_vla, waitSemaphores_vla, commandBuffers_vla, signalSemaphores_vla};
			submits_fill(buf, std::forward<WaitSemaphoresType>(waitSemaphores), std::forward<CommandBuffersType>(commandBuffers), std::forward<SignalSemaphoresType>(signalSemaphores), std::forward<Args>(args)...);

			m_queue->submit(count.submits, submits_vla, nullptr);
		}

		template <typename WaitSemaphoresType, typename CommandBuffersType, typename SignalSemaphoresType, typename ...Args>
		void submit(Fence::Handle &fence, WaitSemaphoresType &&waitSemaphores, CommandBuffersType &&commandBuffers, SignalSemaphoresType &&signalSemaphores, Args &&...args)
		{
			auto count = submitGetCount(std::forward<WaitSemaphoresType>(waitSemaphores), std::forward<CommandBuffersType>(commandBuffers), std::forward<SignalSemaphoresType>(signalSemaphores), std::forward<Args>(args)...);
			SubmitInfo submits_vla[count.submits];
			std::pair<Semaphore*, PipelineStage> waitSemaphores_vla[count.waitSemaphores];
			CommandBuffer *commandBuffers_vla[count.commandBuffers];
			Semaphore *signalSemaphores_vla[count.signalSemaphores];

			SubmitFill buf {submits_vla, waitSemaphores_vla, commandBuffers_vla, signalSemaphores_vla};
			submits_fill(buf, std::forward<WaitSemaphoresType>(waitSemaphores), std::forward<CommandBuffersType>(commandBuffers), std::forward<SignalSemaphoresType>(signalSemaphores), std::forward<Args>(args)...);

			Fence &f = fence;
			m_queue->submit(count.submits, submits_vla, &f);
		}

		template <typename WaitSemaphoresType>
		void present(WaitSemaphoresType &&waitSemaphores, Swapchain::Image2D &image)
		{
			size_t count = submit_semaphores_conv::count(std::forward<WaitSemaphoresType>(waitSemaphores));
			Semaphore *sems_vla[count];
			submit_semaphores_conv::fill_array(sems_vla, std::forward<WaitSemaphoresType>(waitSemaphores));
			m_queue->present(count, sems_vla, image);
		}

		void waitIdle(void)
		{
			return m_queue->waitIdle();
		}

		class Getter
		{
		public:
			Getter(void) = default;

			Queue& get(Handle &handle)
			{
				return *handle.m_queue;
			}
		};

	private:
		friend Getter;
		std::unique_ptr<Queue> m_queue;

		struct SubmitCount
		{
			size_t submits;
			size_t waitSemaphores;
			size_t commandBuffers;
			size_t signalSemaphores;
		};

		using submit_wait_semaphores_conv = util::elems_to_count_ptr<SubmitWaitSemaphorePredicate, SubmitWaitSemaphoreConverter>;
		using submit_command_buffers_conv = util::elems_to_count_ptr<isCmdBufHandle, CmdBufHandleToCommandBufferPtr>;
		using submit_semaphores_conv = util::elems_to_count_ptr<SubmitSemaphorePredicate, SubmitSemaphoreConverter>;

		void submitGetCountIter(SubmitCount&)
		{
		}

		template <typename WaitSemaphoresType, typename CommandBuffersType, typename SignalSemaphoresType, typename ...Args>
		void submitGetCountIter(SubmitCount &res, WaitSemaphoresType &&waitSemaphores, CommandBuffersType &&commandBuffers, SignalSemaphoresType &&signalSemaphores, Args &&...args)
		{
			res.submits++;
			res.waitSemaphores += submit_wait_semaphores_conv::count(std::forward<WaitSemaphoresType>(waitSemaphores));
			res.commandBuffers += submit_command_buffers_conv::count(std::forward<CommandBuffersType>(commandBuffers));
			res.signalSemaphores += submit_semaphores_conv::count(std::forward<SignalSemaphoresType>(signalSemaphores));
			submitGetCountIter(res, std::forward<Args>(args)...);
		}

		template <typename ...Args>
		auto submitGetCount(Args &&...args)
		{
			SubmitCount res {0, 0, 0, 0};

			submitGetCountIter(res, std::forward<Args>(args)...);
			return res;
		}

		void submits_fill(SubmitFill&)
		{
		}

		template <typename WaitSemaphoresType, typename CommandBuffersType, typename SignalSemaphoresType, typename ...Args>
		void submits_fill(SubmitFill &fill, WaitSemaphoresType &&waitSemaphores, CommandBuffersType &&commandBuffers, SignalSemaphoresType &&signalSemaphores, Args &&...args)
		{
			fill.submitInfo->waitSemaphoreCount = submit_wait_semaphores_conv::count(std::forward<WaitSemaphoresType>(waitSemaphores));
			fill.submitInfo->commandBufferCount = submit_command_buffers_conv::count(std::forward<CommandBuffersType>(commandBuffers));
			fill.submitInfo->signalSemaphoreCount = submit_semaphores_conv::count(std::forward<SignalSemaphoresType>(signalSemaphores));

			fill.submitInfo->waitSemaphores = fill.waitSemaphores;
			fill.submitInfo->commandBuffers = fill.commandBuffers;
			fill.submitInfo->signalSemaphores = fill.signalSemaphores;

			submit_wait_semaphores_conv::fill_array(fill.submitInfo->waitSemaphores, std::forward<WaitSemaphoresType>(waitSemaphores));
			submit_command_buffers_conv::fill_array(fill.submitInfo->commandBuffers, std::forward<CommandBuffersType>(commandBuffers));
			submit_semaphores_conv::fill_array(fill.submitInfo->signalSemaphores, std::forward<SignalSemaphoresType>(signalSemaphores));

			fill.waitSemaphores = &fill.waitSemaphores[fill.submitInfo->waitSemaphoreCount];
			fill.commandBuffers = &fill.commandBuffers[fill.submitInfo->commandBufferCount];
			fill.signalSemaphores = &fill.signalSemaphores[fill.submitInfo->signalSemaphoreCount];
			fill.submitInfo = &fill.submitInfo[1];
			submits_fill(fill, std::forward<Args>(args)...);
		}
	};
};

template <>
struct Queue::SubmitWaitSemaphorePredicate<std::pair<Semaphore::Handle*, PipelineStage>>
{
	static inline constexpr auto value = true;
};

template <>
struct Queue::SubmitSemaphorePredicate<Semaphore::Handle>
{
	static inline constexpr auto value = true;
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
	static inline constexpr auto GCT = Queue::Flag::Graphics | Queue::Flag::Compute | Queue::Flag::Transfer;

	template <typename Up>
	class PrimaryBothGCT;

	template <typename Up>
	class PrimarySecondaryBothGC;

	template <typename Up>
	class PrimaryOutsideG;

	template <typename Up>
	class PrimarySecondaryOutsideGCT;

	template <typename Up>
	class PrimarySecondaryBothGCT;

	template <typename Up>
	class PrimarySecondaryInsideG;

	template <typename Up>
	class PrimarySecondaryBothG;

	template <typename Up>
	class PrimarySecondaryOutsideG;

public:
	template <Level L, RenderPassScope S, Queue::Flag Q>
	class For;
};

class CommandBuffer::Record
{
public:
	using RenderPass = CommandBuffer::Cmds::For<Level::Neither, RenderPassScope::Inside, Queue::Flag::Graphics>;
	using RenderPassPrimary = Cmds::For<Level::Primary, RenderPassScope::Inside, Queue::Flag::Graphics>;
	using RenderPassSecondary = Cmds::For<Level::Secondary, RenderPassScope::Inside, Queue::Flag::Graphics>;

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

	struct empty {};
	template <Level L, RenderPassScope S, Queue::Flag Q>
	using query = std::conditional_t<!!(L & Level::Primary) && !!(S & RenderPassScope::Both) && !!(Q & GCT), PrimaryBothGCT, empty>;

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

	static inline constexpr auto GC = Queue::Flag::Graphics | Queue::Flag::Compute;

public:
	PrimarySecondaryBothGC(void) = default;

	struct empty {};
	template <Level L, RenderPassScope S, Queue::Flag Q>
	using query = std::conditional_t<!!(S & RenderPassScope::Both) && !!(Q & GC), PrimarySecondaryBothGC, empty>;

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

template <typename Up>
class CommandBuffer::Cmds::PrimaryOutsideG
{
	CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

	static inline constexpr auto G = Queue::Flag::Graphics;

public:
	PrimaryOutsideG(void) = default;

	struct empty {};
	template <Level L, RenderPassScope S, Queue::Flag Q>
	using query = std::conditional_t<!!(L & Level::Primary) && !!(S & RenderPassScope::Outside) && !!(Q & G), PrimaryOutsideG, empty>;

	template <typename RenderPassType, typename ...Args>
	void render(Framebuffer::Handle<RenderPassType> &fb, const srect2 &renderArea, Args &&...args)
	{
		fb.render(cmd(), renderArea, std::forward<Args>(args)...);
	}
};

template <typename Up>
class CommandBuffer::Cmds::PrimarySecondaryOutsideGCT
{
	CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

public:
	PrimarySecondaryOutsideGCT(void) = default;

	struct empty {};
	template <Level L, RenderPassScope S, Queue::Flag Q>
	using query = std::conditional_t<!!(S & RenderPassScope::Outside) && !!(Q & GCT), PrimarySecondaryOutsideGCT, empty>;

	void copy(const Buffer::Region &src, const Buffer::Region &dst)
	{
		if (src.size != dst.size)
			throw std::runtime_error("Writing regions don't match");
		cmd().copy(src, dst);
	}

	void copyBufferToImage(const Buffer::Region &srcBuffer, sb::Image &dstImage, sb::Image::Layout dstImageLayout, const srect3 &dstRegion)
	{
		cmd().copyBufferToImage(srcBuffer, dstImage, dstImageLayout, dstRegion);
	}
};

template <typename Up>
class CommandBuffer::Cmds::PrimarySecondaryBothGCT
{
	CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

public:
	PrimarySecondaryBothGCT(void) = default;

	struct empty {};
	template <Level L, RenderPassScope S, Queue::Flag Q>
	using query = std::conditional_t<!!(S & RenderPassScope::Both) && !!(Q & GCT), PrimarySecondaryBothGCT, empty>;

	void memoryBarrier(PipelineStage srcStageMask, PipelineStage dstStageMask, DependencyFlag flags, Access srcAccessMask, Access dstAccessMask)
	{
		cmd().memoryBarrier(srcStageMask, dstStageMask, flags, srcAccessMask, dstAccessMask);
	}

	void imageMemoryBarrier(PipelineStage srcStageMask, PipelineStage dstStageMask, DependencyFlag flags, Access srcAccessMask, Access dstAccessMask, Image::Layout oldLayout, Image::Layout newLayout, Image &image)
	{
		cmd().imageMemoryBarrier(srcStageMask, dstStageMask, flags, srcAccessMask, dstAccessMask, oldLayout, newLayout, image);
	}
};

template <typename Up>
class CommandBuffer::Cmds::PrimarySecondaryInsideG
{
	CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

public:
	PrimarySecondaryInsideG(void) = default;

	struct empty {};
	template <Level L, RenderPassScope S, Queue::Flag Q>
	using query = std::conditional_t<!!(S & RenderPassScope::Inside) && !!(Q & Queue::Flag::Graphics), PrimarySecondaryInsideG, empty>;

	template <typename ModelType>
	void draw(ModelType &&model)
	{
		sb::Model &m = model;
		m.draw(cmd());
	}
};

template <typename Up>
class CommandBuffer::Cmds::PrimarySecondaryBothG
{
	CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

public:
	PrimarySecondaryBothG(void) = default;

	struct empty {};
	template <Level L, RenderPassScope S, Queue::Flag Q>
	using query = std::conditional_t<!!(Q & Queue::Flag::Graphics), PrimarySecondaryBothG, empty>;

	void setViewport(const rect2 &area, float minDepth, float maxDepth)
	{
		cmd().setViewport(area, minDepth, maxDepth);
	}

	void setScissor(const srect2 &scissor)
	{
		cmd().setScissor(scissor);
	}
};

template <typename Up>
class CommandBuffer::Cmds::PrimarySecondaryOutsideG
{
	CommandBuffer& cmd(void) { return CmdGetter<Up>().get(static_cast<Up&>(*this)); }

public:
	PrimarySecondaryOutsideG(void) = default;

	struct empty {};
	template <Level L, RenderPassScope S, Queue::Flag Q>
	using query = std::conditional_t<!!(S & RenderPassScope::Outside) && !!(Q & Queue::Flag::Graphics), PrimarySecondaryOutsideG, empty>;

	void blit(sb::Image &srcImage, sb::Image::Layout srcLayout, const srect3 &srcRegion, sb::Image &dstImage, sb::Image::Layout dstLayout, const srect3 &dstRegion, Filter filter)
	{
		return cmd().blit(srcImage, srcLayout, srcRegion, dstImage, dstLayout, dstRegion, filter);
	}
};

template <CommandBuffer::Level L, CommandBuffer::RenderPassScope S, Queue::Flag Q>
class CommandBuffer::Cmds::For :
	public PrimaryBothGCT<For<L, S, Q>>::template query<L, S, Q>,
	public PrimarySecondaryBothGC<For<L, S, Q>>::template query<L, S, Q>,
	public PrimaryOutsideG<For<L, S, Q>>::template query<L, S, Q>,
	public PrimarySecondaryOutsideGCT<For<L, S, Q>>::template query<L, S, Q>,
	public PrimarySecondaryBothGCT<For<L, S, Q>>::template query<L, S, Q>,
	public PrimarySecondaryInsideG<For<L, S, Q>>::template query<L, S, Q>,
	public PrimarySecondaryBothG<For<L, S, Q>>::template query<L, S, Q>,
	public PrimarySecondaryOutsideG<For<L, S, Q>>::template query<L, S, Q>
{
public:
	For(CommandBuffer &cmd) :
		m_cmd(cmd)
	{
	}

	template <CommandBuffer::Level cL, CommandBuffer::RenderPassScope cS, Queue::Flag cQ, class = std::enable_if_t<(cL & L) == cL && (cS & S) == cS && (cQ & Q) == cQ>>
	operator For<cL, cS, cQ>&(void)
	{
		return reinterpret_cast<For<cL, cS, cQ>&>(*this);
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
		using RecordRender = CommandBuffer::Record::RenderPassSecondary;

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

		template <typename Subpass, typename RenderPassType, typename Callable>
		void recordRender(Framebuffer::Handle<RenderPassType> &fb, Callable &&callable)
		{
			static_assert(std::is_same_v<typename Subpass::RenderPass, RenderPassType>, "Subpass doesn't match with framebuffer");

			Record recording(cmd());

			cmd().beginRender(CommandBuffer::Usage::Empty, fb, Subpass::index);
			callable(recording);
			cmd().end();
		}

		template <typename Subpass, typename RenderPassType, typename Callable>
		void recordRender(CommandBuffer::Usage usage, Framebuffer::Handle<RenderPassType> &fb, Callable &&callable)
		{
			static_assert(std::is_same_v<typename Subpass::RenderPass, RenderPassType>, "Subpass doesn't match with framebuffer");

			Record recording(cmd());

			cmd().beginRender(usage, fb, Subpass::index);
			callable(recording);
			cmd().end();
		}

		template <typename Subpass, typename RenderPassType, typename Callable>
		void recordRender(RenderPass::Loaded<RenderPassType> &rp, Callable &&callable)
		{
			static_assert(std::is_same_v<typename Subpass::RenderPass, RenderPassType>, "Subpass doesn't match with framebuffer");

			Record recording(cmd());

			cmd().beginRender(CommandBuffer::Usage::Empty, rp, Subpass::index);
			callable(recording);
			cmd().end();
		}

		template <typename Subpass, typename RenderPassType, typename Callable>
		void recordRender(CommandBuffer::Usage usage, RenderPass::Loaded<RenderPassType> &rp, Callable &&callable)
		{
			static_assert(std::is_same_v<typename Subpass::RenderPass, RenderPassType>, "Subpass doesn't match with framebuffer");

			Record recording(cmd());

			cmd().beginRender(usage, rp, Subpass::index);
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

	operator CommandBuffer&(void)
	{
		return m_cmd;
	}

private:
	template <typename>
	friend class CommandBuffer::CmdGetter;
	CommandBuffer &m_cmd;
};

template <CommandBuffer::Level L, Queue::Flag Q, bool isReset>
struct Queue::isCmdBufHandle<Queue::CmdBufHandle<L, Q, isReset>>
{
	static inline constexpr auto value = true;
};

struct Queue::CmdBufHandleToCommandBufferPtr
{
	template <CommandBuffer::Level L, Queue::Flag Q, bool isReset>
	static CommandBuffer* convert(CmdBufHandle<L, Q, isReset> &cmd)
	{
		return &CommandBuffer::CmdGetter<CmdBufHandle<L, Q, isReset>>().get(cmd);
	}
};

template <typename CommandsType>
void CommandBuffer::beginRenderPassCmds(Framebuffer &fb, const srect2 &renderArea, size_t clearValueCount, sb::ClearValue *clearValues, CommandsType &&commands)
{
	using Commands_t = util::remove_cvr_t<CommandsType>;

	if constexpr (std::is_invocable_v<Commands_t, CommandBuffer::Record::RenderPassPrimary&>) {
		beginRenderPass(true, fb, renderArea, clearValueCount, clearValues);
		CommandBuffer::Record::RenderPassPrimary cmd(*this);
		commands(cmd);
	} else {
		beginRenderPass(false, fb, renderArea, clearValueCount, clearValues);

		using conv = util::elems_to_count_ptr<Queue::isCmdBufHandle, Queue::CmdBufHandleToCommandBufferPtr>;
		size_t commands_count = conv::count(std::forward<CommandsType>(commands));
		CommandBuffer *commands_vla[commands_count];
		conv::fill_array(commands_vla, std::forward<CommandsType>(commands));

		executeCommands(commands_count, commands_vla);
	}
}

template <typename CommandsType>
void CommandBuffer::nextSubpassCmds(CommandsType &&commands)
{
	using Commands_t = util::remove_cvr_t<CommandsType>;

	if constexpr (std::is_invocable_v<Commands_t, CommandBuffer::Record::RenderPassPrimary&>) {
		nextSubpass(true);
		CommandBuffer::Record::RenderPassPrimary cmd(*this);
		commands(cmd);
	} else {
		nextSubpass(false);

		using conv = util::elems_to_count_ptr<Queue::isCmdBufHandle, Queue::CmdBufHandleToCommandBufferPtr>;
		size_t commands_count = conv::count(std::forward<CommandsType>(commands));
		CommandBuffer *commands_vla[commands_count];
		conv::fill_array(commands_vla, std::forward<CommandsType>(commands));

		executeCommands(commands_count, commands_vla);
	}
}

}