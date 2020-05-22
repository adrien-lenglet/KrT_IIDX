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

detect_res: .FORCE
	$(ROOT)/tools/res_detector/res_detector $(ROOT)/res $(SRC_FOLDER)/Krt Krt

RESOURCES_SRC = $(wildcard $(SRC_FOLDER)/Subtile/Resource/*.cpp)
RESOURCES_OBJ = $(RESOURCES_SRC:.cpp=.o) $(SRC_FOLDER)/Krt/res.o
RESOURCE_DUMMY_MAIN = .sb_dummy_main.cpp
RESOURCE_OUT = ./.sb_resource_make

resources: detect_res $(RESOURCES_OBJ)
	echo "int main(void) { return 0; }" > $(RESOURCE_DUMMY_MAIN)
	$(CXX) $(CXXFLAGS) $(RESOURCE_DUMMY_MAIN) $(RESOURCES_OBJ) -o $(RESOURCE_OUT)
	$(RESOURCE_OUT)
	rm $(RESOURCE_DUMMY_MAIN) $(RESOURCE_OUT)

$(SRC_FOLDER)/Krt/res.o: $(SRC_FOLDER)/Krt/res.cpp $(SRC_FOLDER)/Krt/res.hpp
	$(CXX) $(CXXFLAGS) -c $(SRC_FOLDER)/Krt/res.cpp -o $(SRC_FOLDER)/Krt/res.o

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

clean_libs:
	rm -f $(LIB_OBJ)

.FORCE: