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

%.hduped: %.hdup
	ruby $(ROOT)/tools/ppduper.rb $< $@ -I 0 -N 256

MACRO = $(wildcard $(SRC_FOLDER)/Subtile/Macro/*.hdup)
MACRO_DUPPED = $(MACRO:.hdup=.hduped)

MACRO_SEQ_FOR_EACH = $(foreach var,64 128 256 512 1024 2048 4096 8192,$(SRC_FOLDER)/Subtile/Macro/seq_for_each/it_$(var).hduped)

$(MACRO_SEQ_FOR_EACH): $(SRC_FOLDER)/Subtile/Macro/seq_for_each/seq_for_each.hdup
	ruby $(ROOT)/tools/ppduper.rb $< $@ -I 1

macro: $(MACRO_DUPPED) $(MACRO_SEQ_FOR_EACH)

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

$(TARGET): macro $(OBJ) $(LIB_OBJ)
	ar rcs $(TARGET) $(OBJ) $(LIB_OBJ)

clean:
	rm -f $(OBJ)

clean_libs:
	rm -f $(LIB_OBJ)

.FORCE: