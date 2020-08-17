#pragma once

#include <set>
#include "../Subtile.hpp"
#include "Image.hpp"
#include "PipelineStage.hpp"
#include "Access.hpp"
#include "DependencyFlag.hpp"

#include "Resource/File.hpp"
#include "Resource/Target.hpp"

namespace Subtile {

class RenderPass
{
public:
	class Compiler;

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
			std::set<PipelineStage> srcStageMask;
			std::set<PipelineStage> dstStageMask;
			std::set<Access> srcAccessMask;
			std::set<Access> dstAccessMask;
			std::set<DependencyFlag> flags;
		};

		std::vector<Attachment> attachments;
		std::vector<Subpass> subpasses;
		std::vector<Dependency> dependencies;
	};

	virtual ~RenderPass(void) = default;
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