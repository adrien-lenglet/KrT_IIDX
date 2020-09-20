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

RES_DETECTOR = tools/res_detector/res_detector
$(RES_DETECTOR): .FORCE
	$(MAKE) -C $(dir $(RES_DETECTOR))

resources_detect: $(RES_DETECTOR) .FORCE
	$(RES_DETECTOR) ../res $(SRC_FOLDER)/Krt Krt

%.res_detector.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

USER_RESOURCES_SRC = $(SRC_FOLDER)/Krt/res.resdecl.cpp
USER_RESOURCES_HEADER = $(USER_RESOURCES_SRC:.cpp=.hpp)
RESOURCES_SRC = $(USER_RESOURCES_SRC) $(wildcard $(SRC_FOLDER)/Subtile/Resource/*.cpp) $(wildcard $(SRC_FOLDER)/Subtile/Shader.cpp) $(wildcard $(SRC_FOLDER)/Subtile/RenderPass.cpp) $(wildcard libs/src/tiny_obj_loader.cpp)
RESOURCES_OBJ = $(RESOURCES_SRC:.cpp=.res_detector.o)

RESOURCE_DUMMY_MAIN = .sb_dummy_main.cpp
RESOURCE_OUT = ./.sb_resource_make

resources: $(RESOURCES_OBJ)

RES_SHIP = res_ship

$(RES_SHIP): $(RESOURCES_OBJ)
	$(CXX) $(CXXFLAGS) res_ship.cpp $(RESOURCES_OBJ) -o $(RES_SHIP)

LIB_SRC = $(wildcard $(LIB_SRC_FOLDER)/*.cpp)
LIB_OBJ = $(LIB_SRC:.cpp=.o)

$(OBJ): WARNINGS = -Wall -Wextra
$(LIB_OBJ): WARNINGS =

debug: EXTRA += -g
debug: DEFINE += -DDEBUG
debug: all

release: EXTRA += -O3
release: all $(RES_SHIP)

$(TARGET): $(OBJ) $(LIB_OBJ)
	ar rcs $(TARGET) $(OBJ) $(LIB_OBJ)

clean:
	rm -f $(OBJ) $(TARGET)

clean_libs:
	rm -f $(LIB_OBJ)

clean_all: clean_libs clean
	rm -f $(RESOURCES_OBJ) $(RES_SHIP)

TOOLS_FOLDER = tools
TOOLS = $(TOOLS_FOLDER)/res_detector

clean_tools:
	for tool in $(TOOLS); do \
		$(MAKE) -C $$tool clean; \
	done

wipe_all_bin: clean_tools clean_all

wipe_resources:
	rm -f $(USER_RESOURCES_SRC) $(USER_RESOURCES_HEADER)

wipe_all_build: wipe_resources wipe_all_bin

.FORCE: