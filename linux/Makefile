LINK_OPT =
CXX = clang++
CXXFLAGS = -std=c++17 $(CXXFLAGS_ADD)

OBJ = ../common/obj.a

TARGET = ../KrT_IIDX
LIBS_SO = $(wildcard libs/bin/*.so)
LIB = $(LIBS_SO) -lvulkan -Wl,-rpath,linux/libs/bin

$(TARGET): libs $(OBJ)
	$(CXX) $(CXXFLAGS) $(LINK_OPT) $(OBJ) $(LIB) -o $(TARGET)

libs: .FORCE
	$(MAKE) -C libs
libs_clean:
	$(MAKE) -C libs clean

debug: CXXFLAGS_ADD = -g
debug: $(TARGET)

release: CXXFLAGS_ADD = -O3
release: LINK_OPT = -s
release: $(TARGET)

clean:
	rm -f $(TARGET)

.FORCE: