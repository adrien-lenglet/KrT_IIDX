#pragma once

#include "util/enum_class_bitmask.hpp"
#include "../Subtile.hpp"

namespace Subtile {

enum class PipelineStage {
	None = 0,
	TopOfPipe = 0x00000001,
	DrawIndirect = 0x00000002,
	VertexInput = 0x00000004,
	VertexShader = 0x00000008,
	TesselationControlShader = 0x00000010,
	TesselationEvaluationShader = 0x00000020,
	GeometryShader = 0x00000040,
	FragmentShader = 0x00000080,
	EarlyFragmentTests = 0x00000100,
	LateFragmentTests = 0x00000200,
	ColorAttachmentOutput = 0x00000400,
	ComputeShader = 0x00000800,
	Transfer = 0x00001000,
	BottomOfPipe = 0x00002000,
	Host = 0x00004000,
	AllGraphics = 0x00008000,
	AllCommands = 0x00010000
};

}

template <>
struct util::enable_bitmask<sb::PipelineStage>
{
	static inline constexpr bool value = true;
};