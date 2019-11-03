
.DEFAULT_GOAL := all

SHADER_VERT_SRC = $(wildcard *.vert)
SHADER_VERT_BIN = $(SHADER_VERT_SRC:.vert=.spv)
SHADER_TESC_SRC = $(wildcard *.tesc)
SHADER_TESC_BIN = $(SHADER_TESC_SRC:.tesc=.spv)
SHADER_TESE_SRC = $(wildcard *.tese)
SHADER_TESE_BIN = $(SHADER_TESE_SRC:.tese=.spv)
SHADER_GEOM_SRC = $(wildcard *.geom)
SHADER_GEOM_BIN = $(SHADER_GEOM_SRC:.geom=.spv)
SHADER_FRAG_SRC = $(wildcard *.frag)
SHADER_FRAG_BIN = $(SHADER_FRAG_SRC:.frag=.spv)
SHADER_COMP_SRC = $(wildcard *.comp)
SHADER_COMP_BIN = $(SHADER_COMP_SRC:.comp=.spv)
SHADER_MESH_SRC = $(wildcard *.mesh)
SHADER_MESH_BIN = $(SHADER_MESH_SRC:.mesh=.spv)
SHADER_TASK_SRC = $(wildcard *.task)
SHADER_TASK_BIN = $(SHADER_TASK_SRC:.task=.spv)
SHADER_RGEN_SRC = $(wildcard *.rgen)
SHADER_RGEN_BIN = $(SHADER_RGEN_SRC:.rgen=.spv)
SHADER_RINT_SRC = $(wildcard *.rint)
SHADER_RINT_BIN = $(SHADER_RINT_SRC:.rint=.spv)
SHADER_RAHIT_SRC = $(wildcard *.rahit)
SHADER_RAHIT_BIN = $(SHADER_RAHIT_SRC:.rahit=.spv)
SHADER_RCHIT_SRC = $(wildcard *.rchit)
SHADER_RCHIT_BIN = $(SHADER_RCHIT_SRC:.rchit=.spv)
SHADER_RMISS_SRC = $(wildcard *.rmiss)
SHADER_RMISS_BIN = $(SHADER_RMISS_SRC:.rmiss=.spv)
SHADER_RCALL_SRC = $(wildcard *.rcall)
SHADER_RCALL_BIN = $(SHADER_RCALL_SRC:.rcall=.spv)
SHADER_GLSL_SRC = $(wildcard *.glsl)
SHADER_GLSL_BIN = $(SHADER_GLSL_SRC:.glsl=.spv)
SHADER_HLSL_SRC = $(wildcard *.hlsl)
SHADER_HLSL_BIN = $(SHADER_HLSL_SRC:.hlsl=.spv)

SHADER_SRC = $(SHADER_VERT_SRC) $(SHADER_TESC_SRC) $(SHADER_TESE_SRC) $(SHADER_GEOM_SRC) $(SHADER_FRAG_SRC) $(SHADER_COMP_SRC) $(SHADER_MESH_SRC) $(SHADER_TASK_SRC) $(SHADER_RGEN_SRC) $(SHADER_RINT_SRC) $(SHADER_RAHIT_SRC) $(SHADER_RCHIT_SRC) $(SHADER_RMISS_SRC) $(SHADER_RCALL_SRC) $(SHADER_GLSL_SRC) $(SHADER_HLSL_SRC)
SHADER_BIN = $(SHADER_VERT_BIN) $(SHADER_TESC_BIN) $(SHADER_TESE_BIN) $(SHADER_GEOM_BIN) $(SHADER_FRAG_BIN) $(SHADER_COMP_BIN) $(SHADER_MESH_BIN) $(SHADER_TASK_BIN) $(SHADER_RGEN_BIN) $(SHADER_RINT_BIN) $(SHADER_RAHIT_BIN) $(SHADER_RCHIT_BIN) $(SHADER_RMISS_BIN) $(SHADER_RCALL_BIN) $(SHADER_GLSL_BIN) $(SHADER_HLSL_BIN)

%.spv: %.vert
	glslangValidator -V $< -o $@
%.spv: %.tesc
	glslangValidator -V $< -o $@
%.spv: %.tese
	glslangValidator -V $< -o $@
%.spv: %.geom
	glslangValidator -V $< -o $@
%.spv: %.frag
	glslangValidator -V $< -o $@
%.spv: %.comp
	glslangValidator -V $< -o $@
%.spv: %.mesh
	glslangValidator -V $< -o $@
%.spv: %.task
	glslangValidator -V $< -o $@
%.spv: %.rgen
	glslangValidator -V $< -o $@
%.spv: %.rint
	glslangValidator -V $< -o $@
%.spv: %.rahit
	glslangValidator -V $< -o $@
%.spv: %.rchit
	glslangValidator -V $< -o $@
%.spv: %.rmiss
	glslangValidator -V $< -o $@
%.spv: %.rcall
	glslangValidator -V $< -o $@
%.spv: %.glsl
	glslangValidator -V $< -o $@
%.spv: %.hlsl
	glslangValidator -V $< -o $@

all: $(SHADER_BIN)

clean:
	rm -f $(SHADER_BIN)

.PHONY: all clean
