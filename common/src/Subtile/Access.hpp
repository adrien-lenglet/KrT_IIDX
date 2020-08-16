#pragma once

#include "../Subtile.hpp"

namespace Subtile {

enum class Access {
	IndirectCommandRead,
	IndexRead,
	VertexAttributeRead,
	UniformRead,
	InputAttachmentRead,
	ShaderRead,
	ShaderWrite,
	ColorAttachmentRead,
	ColorAttachmentWrite,
	DepthStencilAttachmentRead,
	DepthStencilAttachmentWrite,
	TransferRead,
	TransferWrite,
	HostRead,
	HostWrite,
	MemoryRead,
	MemoryWrite
};

}