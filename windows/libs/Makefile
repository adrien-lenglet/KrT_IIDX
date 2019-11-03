
.DEFAULT_GOAL := all

LIBS = glfw

DARG = all

$(LIBS):
	@$(MAKE) -C $@ $(DARG)

libs: $(LIBS)

all: libs

clean: DARG = clean
clean: $(LIBS)

.PHONY: all clean libs $(LIBS)
