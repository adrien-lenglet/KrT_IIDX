
.DEFAULT_GOAL := all
OPT = -j12
CXX = clang++
CXXFLAGS = -std=c++17

OBJ = ../common/obj.a

TARGET = ../KrT_IIDX
LIBS_SO = $(wildcard libs/bin/*.so)
LIB = $(LIBS_SO) -lvulkan -Wl,-rpath,linux/libs/bin

DARG = all

libs:
	$(MAKE) -C libs

libs_clean:
	$(MAKE) -C libs clean

obj:
	$(MAKE) -C ../common macro $(OPT)
	$(MAKE) -C ../common resources $(OPT)
	$(MAKE) -C ../common $(DARG) $(OPT)

obj_clean:
	$(MAKE) -C ../common clean

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LINK_OPT) $(OBJ) $(LIB) -o $(TARGET)

builder: libs obj $(TARGET)

all: builder

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
