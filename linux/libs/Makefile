
.DEFAULT_GOAL := all
DARG = all

BIN_FOLDER = bin
LIBS = glfw

$(BIN_FOLDER):
	mkdir $(BIN_FOLDER)

$(LIBS): .FORCE
	@$(MAKE) -C $@ $(DARG)

libs: $(BIN_FOLDER) $(LIBS)

all: libs

clean: DARG = clean
clean: $(LIBS)
	rm -rf bin

.FORCE:
