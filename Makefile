COMMON = ./common
OPT = -j12

all: release

define make_platforms
	for plat in windows linux; do \
		$(MAKE) -C $$plat $(1) $(OPT); \
	done
endef

common_macro_resources:
	$(MAKE) -C $(COMMON) macro $(OPT)
	$(MAKE) -C $(COMMON) resources $(OPT)

debug: common_macro_resources
	$(MAKE) -C $(COMMON) debug $(OPT)

release: common_macro_resources
	$(MAKE) -C $(COMMON) release $(OPT)

debug_windows: debug
	$(MAKE) -C windows debug $(OPT)
release_windows: release
	$(MAKE) -C windows release $(OPT)
clean_windows: clean

debug_linux: debug
	$(MAKE) -C linux debug $(OPT)
release_linux: release
	$(MAKE) -C linux release $(OPT)
clean_linux: clean

clean: clean_builds
	$(MAKE) -C $(COMMON) clean $(OPT)

clean_builds:
	$(call make_platforms, clean)

clean_builds_libs:
	$(call make_platforms, libs_clean)

clean_all: clean_builds clean_builds_libs
	$(MAKE) -C $(COMMON) clean_all $(OPT)

wipe_all_bin: clean_builds clean_builds_libs
	$(MAKE) -C $(COMMON) wipe_all_bin $(OPT)

wipe_all_build: clean_builds clean_builds_libs
	$(MAKE) -C $(COMMON) wipe_all_build $(OPT)