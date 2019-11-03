
.DEFAULT_GOAL := all

BIN_FOLDER = bin

LIBS = glfw

DARG = all

$(BIN_FOLDER):
	mkdir $(BIN_FOLDER)

$(LIBS):
	@$(MAKE) -C $@ $(DARG)

libs: $(BIN_FOLDER) $(LIBS)

all: libs

clean: DARG = clean
clean: $(LIBS)
	rm -rf bin

.PHONY: all clean libs $(LIBS)
