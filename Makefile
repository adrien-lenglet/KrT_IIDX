COMMON = ./common
OPT = -j12

all: release

LINK_OPT =
CXX = clang++
CXXFLAGS_ADD =
CXXFLAGS = -std=c++17 $(CXXFLAGS_ADD)

OBJ = common/obj.a

TARGET = KrT_IIDX
LIB = LOL

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LINK_OPT) $(OBJ) $(LIB) -o $(TARGET)

define make_platforms
	for plat in windows linux; do \
		$(MAKE) -C $$plat $(1) $(OPT); \
	done
endef

define copy_bins
endef

resources:
	$(MAKE) -C $(COMMON) resources_detect $(OPT)
	$(MAKE) -C $(COMMON) resources $(OPT)

common_macro_resources:
	$(MAKE) -C $(COMMON) macro $(OPT)
	$(MAKE) -C $(COMMON) resources_detect $(OPT)
	$(MAKE) -C $(COMMON) resources $(OPT)

debug: CXXFLAGS_ADD = -g
debug: common_macro_resources
	$(MAKE) -C $(COMMON) debug $(OPT)

release: CXXFLAGS_ADD = -O3
release: LINK_OPT = -s
release: common_macro_resources
	$(MAKE) -C $(COMMON) release $(OPT)

windows: LIB = "$(shell cygpath --unix $(VULKAN_SDK))/Lib/vulkan-1.lib" -lglfw3
windows: $(TARGET)

debug_windows: debug windows 
release_windows: release windows

build:
	mkdir build

WIN_PUBLISH = build/windows

publish_windows: wipe_all_bin release_windows
	mkdir -p $(WIN_PUBLISH)
	$(call copy_bins, $(WIN_PUBLISH))

linux: LIB = -lglfw -lvulkan
linux: $(TARGET)

debug_linux: debug linux
release_linux: release linux

clean_target:
	rm -f $(TARGET)

clean: clean_target
	$(MAKE) -C $(COMMON) clean $(OPT)

clean_all: clean_target
	$(MAKE) -C $(COMMON) clean_all $(OPT)

wipe_all_bin: clean_target
	$(MAKE) -C $(COMMON) wipe_all_bin $(OPT)
	rm -rf build

wipe_all_build: clean_target
	$(MAKE) -C $(COMMON) wipe_all_build $(OPT)

.PHONY: windows linux debug release