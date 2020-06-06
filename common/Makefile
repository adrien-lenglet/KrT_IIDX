DEFINE =
WARNINGS =
EXTRA =
INCLUDE = -I src -I libs/include
CXX = clang++
CXXFLAGS = -std=c++17 $(EXTRA) $(WARNINGS) $(DEFINE) $(INCLUDE)

SRC_FOLDER = src
LIB_SRC_FOLDER = libs/src

ROOT = ..

SRC = $(wildcard $(SRC_FOLDER)/*.cpp) $(wildcard $(SRC_FOLDER)/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*/*/*/*.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = obj.a

all: $(TARGET)

MACRO_FOLDER = $(SRC_FOLDER)/Subtile/Macro
macro:
	$(MAKE) -C $(MACRO_FOLDER)

RES_DETECTOR = $(ROOT)/tools/res_detector/res_detector
$(RES_DETECTOR): .FORCE
	$(MAKE) -C $(dir $(RES_DETECTOR))

resources_detect: $(RES_DETECTOR) .FORCE
	$(RES_DETECTOR) $(ROOT)/res $(SRC_FOLDER)/Krt Krt

USER_RESOURCES_SRC = $(SRC_FOLDER)/Krt/res.resdecl.cpp
USER_RESOURCES_HEADER = $(USER_RESOURCES_SRC:.cpp=.hpp)
USER_RESOURCES_OBJ = $(USER_RESOURCES_SRC:.cpp=.o)

RESOURCES_SRC = $(wildcard $(SRC_FOLDER)/Subtile/Resource/*.cpp)
RESOURCES_OBJ = $(RESOURCES_SRC:.cpp=.o)

RESOURCE_DUMMY_MAIN = .sb_dummy_main.cpp
RESOURCE_OUT = ./.sb_resource_make

resources: $(RESOURCES_OBJ) $(USER_RESOURCES_OBJ)
	echo "int main(void) { return 0; }" > $(RESOURCE_DUMMY_MAIN)
	$(CXX) $(CXXFLAGS) $(RESOURCE_DUMMY_MAIN) $(RESOURCES_OBJ) $(USER_RESOURCES_OBJ) -o $(RESOURCE_OUT)
	$(RESOURCE_OUT)
	rm $(RESOURCE_DUMMY_MAIN) $(RESOURCE_OUT)

LIB_SRC = $(wildcard $(LIB_SRC_FOLDER)/*.cpp)
LIB_OBJ = $(LIB_SRC:.cpp=.o)

$(OBJ): WARNINGS = -Wall -Wextra
$(LIB_OBJ): WARNINGS =

debug: EXTRA += -g
debug: DEFINE += -DDEBUG
debug: all

release: EXTRA += -O3
release: all

$(TARGET): $(OBJ) $(LIB_OBJ)
	ar rcs $(TARGET) $(OBJ) $(LIB_OBJ)

clean:
	rm -f $(OBJ)
	rm -f $(TARGET)

clean_libs:
	rm -f $(LIB_OBJ)

clean_macros:
	$(MAKE) -C $(MACRO_FOLDER) clean

clean_all: clean_libs clean

TOOLS_FOLDER = $(ROOT)/tools
TOOLS = $(TOOLS_FOLDER)/res_detector

clean_tools:
	for tool in $(TOOLS); do \
		$(MAKE) -C $$tool clean; \
	done

wipe_all_bin: clean_tools clean_all

wipe_resources:
	rm -f $(USER_RESOURCES_SRC) $(USER_RESOURCES_HEADER)

wipe_all_build: clean_macros wipe_resources wipe_all_bin

.FORCE: