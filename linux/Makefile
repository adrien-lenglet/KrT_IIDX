
.DEFAULT_GOAL := all

DEFINE =
WARNINGS =
EXTRA =
INCLUDE = -I../common/src -I../common/libs/include
CXXFLAGS = -m64 -std=c++17 $(EXTRA) $(WARNINGS) $(DEFINE) $(INCLUDE)

SRC_FOLDER = ../common/src
LIB_SRC_FOLDER = ../common/libs/src

SRC = $(wildcard $(SRC_FOLDER)/*.cpp) $(wildcard $(SRC_FOLDER)/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*/*.cpp)
OBJ = $(SRC:.cpp=.o)

LIB_SRC = $(wildcard $(LIB_SRC_FOLDER)/*.cpp)
LIB_OBJ = $(LIB_SRC:.cpp=.o)

TARGET = ../KrT_IIDX
LIBS_SO = $(wildcard libs/bin/*.so)
LDLIB = $(LIBS_SO) -lvulkan

DARG = all

libs:
	$(MAKE) -C libs $(DARG)

libs_clean: DARG = clean
libs_clean: libs
	rm -f $(LIB_OBJ)

shaders:
	$(MAKE) -C ../common/shaders $(DARG)

shaders_clean: DARG = clean
shaders_clean: shaders

$(OBJ): WARNINGS = -Wall -Wextra
$(LIB_OBJ): WARNINGS =

$(TARGET): libs shaders $(OBJ) $(LIB_OBJ) $(SHADER_BIN)
	g++ $(OBJ) $(LIB_OBJ) -Wl,-rpath,linux/libs/bin -o $(TARGET) $(LDLIB)

all: $(TARGET)

debug: EXTRA += -g
debug: DEFINE += -DDEBUG
debug: all

release: EXTRA += -O3
release: all

clean: shaders_clean
	rm -f $(TARGET) $(OBJ)

clean_all: libs_clean shaders_clean clean

.PHONY: all debug release clean libs libs_clean shaders shaders_clean clean_all
