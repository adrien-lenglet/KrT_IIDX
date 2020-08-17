#pragma once

#include "../Subtile.hpp"
#include "Format.hpp"

namespace Subtile {

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