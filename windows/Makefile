LINK_OPT =
CXX = clang++
CXXFLAGS = -std=c++17 $(CXXFLAGS_ADD)

OBJ = ../common/obj.a

TARGET = ../KrT_IIDX.exe
LIBS_DLL = $(wildcard ../*.dll)
LIB = $(LIBS_DLL) \
"$(shell cygpath --unix $(VULKAN_SDK))/Lib/vulkan-1.lib"

$(TARGET): libs $(OBJ)
	$(CXX) $(CXXFLAGS) $(LINK_OPT) $(OBJ) $(LIB) -o $(TARGET)

target_ensure: vulkan_sdk_ensure $(TARGET)

libs: .FORCE
	$(MAKE) -C libs
libs_clean:
	$(MAKE) -C libs clean

debug: CXXFLAGS_ADD = -g
debug: target_ensure

release: CXXFLAGS_ADD = -O3
release: LINK_OPT = -s
release: target_ensure

clean:
	rm -f $(TARGET)

ifndef VULKAN_SDK
vulkan_sdk_ensure: .FORCE
	$(error VULKAN_SDK is not set. Make sure the LunarG Vulkan SDK is installed on your system and that this variable is properly set in your environment)	
endif
ifdef VULKAN_SDK
vulkan_sdk_ensure: .FORCE
endif

.FORCE:
