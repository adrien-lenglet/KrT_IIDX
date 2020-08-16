#pragma once

#include "../Subtile.hpp"
#include "Format.hpp"

namespace Subtile {

class Image
{
public:
	enum class Layout {
		Undefined,
		General,

		ColorAttachmentOptimal,
		DepthStencilAttachmentOptimal,
		DepthStencilReadOnlyOptimal,
		ShaderReadOnlyOptimal,
		TransferSrcOptimal,
		TransferDstOptimal,

		Preinitialized,

		PresentSrc
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

	virtual ~Image(void) = default;
};

}