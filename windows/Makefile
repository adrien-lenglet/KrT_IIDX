LINK_OPT =
CXX = clang++
CXXFLAGS = -std=c++17 $(CXXFLAGS_ADD)

OBJ = ../common/obj.a

TARGET = ../KrT_IIDX.exe
LIBS_DLL = $(wildcard ../*.dll)
LIB = $(LIBS_DLL) \
"$(shell cygpath --unix $(VULKAN_SDK))/Lib/vulkan-1.lib"

$(TARGET): vulkan_sdk_ensure libs $(OBJ)
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

vulkan_sdk_ensure: .FORCE
	ifndef VULKAN_SDK
		$(error VULKAN_SDK is not set. Make sure the LunarG Vulkan SDK is installed on your system and that this variable is properly set in your environment)
	endif

.FORCE:
