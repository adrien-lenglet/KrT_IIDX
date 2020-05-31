
.DEFAULT_GOAL := all
LINK_OPT =
OPT = -j12
CXX = clang++
CXXFLAGS = -std=c++17

ifndef VULKAN_SDK
$(error VULKAN_SDK is not set. Make sure the LunarG Vulkan SDK is installed on your system and that this variable is properly set in your environment)
endif

OBJ = ../common/obj.a

TARGET = ../KrT_IIDX.exe
LIBS_DLL = $(wildcard ../*.dll)
LIB = $(LIBS_DLL) \
"$(shell cygpath --unix $(VULKAN_SDK))/Lib/vulkan-1.lib"

DARG = all

libs:
	$(MAKE) -C libs

libs_clean:
	$(MAKE) -C libs clean

resource:
	$(MAKE) -C ../common resources

obj:
	$(MAKE) -C ../common resources
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

clean_all: libs_clean clean
	$(MAKE) -C ../common clean_libs

.PHONY: all debug release clean libs libs_clean clean_all
