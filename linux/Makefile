
.DEFAULT_GOAL := all

DEFINE =
EXTRA =
INCLUDE = -I../common/src -I../common/libs/include
CXXFLAGS = -m64 -Wall -Wextra -std=c++17 $(EXTRA) $(DEFINE) $(INCLUDE)

SRC_FOLDER = ../common/src

SRC = $(wildcard $(SRC_FOLDER)/*.cpp) $(wildcard $(SRC_FOLDER)/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*/*.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = ../KrT_IIDX
LIBS_SO = $(wildcard libs/bin/*.so)
LDLIB = $(LIBS_SO) -lvulkan

DARG = all

libs:
	$(MAKE) -C libs $(DARG)

libs_clean: DARG = clean
libs_clean: libs

shaders:
	$(MAKE) -C ../common/shaders $(DARG)

shaders_clean: DARG = clean
shaders_clean: shaders

$(TARGET): libs shaders $(OBJ) $(SHADER_BIN)
	g++ $(OBJ) -Wl,-rpath,linux/libs/bin -o $(TARGET) $(LDLIB)

all: $(TARGET)

debug: EXTRA = -g
debug: DEFINE = -DDEBUG
debug: all

release: EXTRA = -O3
release: all

clean: shaders_clean
	rm -f $(TARGET) $(OBJ)

clean_all: libs_clean shaders_clean clean

.PHONY: all debug release clean libs libs_clean shaders shaders_clean clean_all
