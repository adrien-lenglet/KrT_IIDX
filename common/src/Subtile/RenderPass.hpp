#pragma once

#include <set>
#include "util.hpp"
#include "util/traits.hpp"
#include "../Subtile.hpp"
#include "Cache.hpp"
#include "Image.hpp"
#include "Framebuffer.hpp"
#include "PipelineStage.hpp"
#include "Access.hpp"
#include "DependencyFlag.hpp"

#include "Resource/File.hpp"
#include "Resource/Target.hpp"

namespace Subtile {

namespace Resource {
class RenderPass;
}

class RenderPass
{
public:
	class Compiler;

	using Cache = sb::Cache<util::ref_wrapper<Resource::RenderPass>, std::unique_ptr<RenderPass>>;

	template <typename T>
	class RefGetter
	{
	public:
		RefGetter(T &holder) :
			m_holder(holder)
		{
		}

		auto& get(void)
		{
			return m_holder.m_ref;
		}

	private:
		T &m_holder;
	};

	class CacheRefHolder
	{
	public:
		template <typename ...Args>
		CacheRefHolder(Args &&...args) :
			m_ref(std::forward<Args>(args)...)
		{
		}

		template <typename>
		friend class RefGetter;

	protected:
		Cache::Ref m_ref;
	};


	template <typename ResType>
	class Loaded :
		public CacheRefHolder,
		public util::remove_cvr_t<ResType>::template Runtime<Loaded<ResType>>
	{
		using Res = util::remove_cvr_t<ResType>;

	public:
		Loaded(Cache::Ref &&shader_ref) :
			CacheRefHolder(std::move(shader_ref))
		{
		}
		Loaded(Loaded<Res> &&other) :
			CacheRefHolder(std::move(RefGetter<CacheRefHolder>(other).get()))
		{
		}

		operator RenderPass&(void)
		{
			return **m_ref;
		}
	};

	struct Layout
	{
		struct Attachment
		{
			Format format;
			Image::LoadOp loadOp;
			Image::StoreOp storeOp;
			Image::Layout inLayout;
			Image::Layout outLayout;
		};

		using AttachmentIndex = size_t;

		struct AttachmentReference
		{
			AttachmentIndex ndx;
			Image::Layout layout;
		};

		struct ColorAttachmentReference : public AttachmentReference
		{
			std::optional<AttachmentReference> resolve;
		};

		struct Subpass
		{
			std::vector<AttachmentReference> inputAttachments;
			std::vector<ColorAttachmentReference> colorAttachments;
			std::optional<AttachmentReference> depthStencilAttachment;
			std::vector<AttachmentIndex> preserveAttachments;
		};

		using SubpassIndex = size_t;

		struct Dependency
		{
			SubpassIndex srcSubpass;
			SubpassIndex dstSubpass;
			PipelineStage srcStageMask;
			PipelineStage dstStageMask;
			Access srcAccessMask;
			Access dstAccessMask;
			DependencyFlag flags;
		};

		std::vector<Attachment> attachments;
		std::vector<Subpass> subpasses;
		std::vector<Dependency> dependencies;
	};

	virtual ~RenderPass(void) = default;

	virtual std::unique_ptr<Framebuffer> createFramebuffer(const svec2 &extent, size_t layers, size_t count, sb::Image **images) = 0;
};

}

namespace Subtile {
namespace Resource {

class RenderPass : public File
{
public:
	RenderPass(void);
	~RenderPass(void) override;

	virtual sb::RenderPass::Layout layout(void) const = 0;
};

}
}