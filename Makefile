COMMON = ./common
OPT = -j12

all: release

debug:
	$(MAKE) -C $(COMMON) macro $(OPT)
	$(MAKE) -C $(COMMON) resources $(OPT)
	$(MAKE) -C $(COMMON) debug $(OPT)

release:
	$(MAKE) -C $(COMMON) macro $(OPT)
	$(MAKE) -C $(COMMON) resources $(OPT)
	$(MAKE) -C $(COMMON) release $(OPT)

debug_windows: debug
	$(MAKE) -C windows debug $(OPT)
release_windows: release
	$(MAKE) -C windows release $(OPT)
clean_windows: clean

debug_linux: debug
	$(MAKE) -C linux debug $(OPT)
release_linux: release
	$(MAKE) -C linux debug $(OPT)
clean_linux: clean

clean: clean_builds
	$(MAKE) -C $(COMMON) clean $(OPT)

clean_builds:
	$(MAKE) -C windows clean $(OPT)
	$(MAKE) -C linux clean $(OPT)

clean_builds_libs:
	$(MAKE) -C windows libs_clean $(OPT)
	$(MAKE) -C linux libs_clean $(OPT)

clean_all: clean_builds clean_builds_libs
	$(MAKE) -C $(COMMON) clean_all $(OPT)

wipe_all_build: clean_builds
	$(MAKE) -C $(COMMON) wipe_all_build $(OPT)