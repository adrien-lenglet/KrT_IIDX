
.DEFAULT_GOAL := all
DARG = all

LIBS = glfw

$(LIBS): .FORCE
	$(MAKE) -C $@ $(DARG)

libs: $(LIBS)

all: libs

clean: DARG = clean
clean: $(LIBS)

.FORCE: