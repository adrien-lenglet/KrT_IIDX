#pragma once

#include "../Subtile.hpp"

namespace Subtile {

enum class PipelineStage {
	TopOfPipe,
	DrawIndirect,
	VertexInput,
	VertexShader,
	TesselationControlShader,
	TesselationEvaluationShader,
	GeometryShader,
	FragmentShader,
	EarlyFragmentTests,
	LateFragmentTests,
	ColorAttachmentOutput,
	ComputeShader,
	Transfer,
	BottomOfPipe
};

}