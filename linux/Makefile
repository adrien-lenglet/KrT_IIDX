
.DEFAULT_GOAL := all
LINK_OPT =
OPT = -j12
CXX = clang++
CXXFLAGS = -std=c++17

SRC_FOLDER = ../common/src
LIB_SRC_FOLDER = ../common/libs/src

LIB_SRC = $(wildcard $(LIB_SRC_FOLDER)/*.cpp)
LIB_OBJ = $(LIB_SRC:.cpp=.o)

SRC = $(wildcard $(SRC_FOLDER)/*.cpp) $(wildcard $(SRC_FOLDER)/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*/*/*/*.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = ../KrT_IIDX
LIBS_SO = $(wildcard libs/bin/*.so)
LDLIB = $(LIBS_SO) -lvulkan

DARG = all

libs:
	$(MAKE) -C libs

libs_clean:
	$(MAKE) -C libs clean

shaders:
	$(MAKE) -C ../common/shaders $(OPT)

shaders_clean:
	$(MAKE) -C ../common/shaders clean

obj:
	$(MAKE) -C ../common resources
	$(MAKE) -C ../common $(DARG) $(OPT)

obj_clean:
	$(MAKE) -C ../common clean

$(TARGET): libs shaders obj $(SHADER_BIN)
	$(CXX) $(CXXFLAGS) $(LINK_OPT) $(OBJ) $(LIB_OBJ) -Wl,-rpath,linux/libs/bin -o $(TARGET) $(LDLIB)

all: $(TARGET)

debug: DARG = debug
debug: CXXFLAGS = -g
debug: all

release: DARG = release
release: LINK_OPT = -s
release: CXXFLAGS = -O3
release: all

clean: obj_clean
	rm -f $(TARGET)

clean_all: libs_clean shaders_clean clean
	$(MAKE) -C ../common clean_libs

.PHONY: all debug release clean libs libs_clean shaders shaders_clean clean_all
