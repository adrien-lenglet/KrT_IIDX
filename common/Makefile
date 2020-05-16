DEFINE =
WARNINGS =
EXTRA =
INCLUDE = -I src -I libs/include
CXX = clang++
CXXFLAGS = -std=c++17 $(EXTRA) $(WARNINGS) $(DEFINE) $(INCLUDE)

SRC_FOLDER = src
LIB_SRC_FOLDER = libs/src

SRC = $(wildcard $(SRC_FOLDER)/*.cpp) $(wildcard $(SRC_FOLDER)/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*/*/*.cpp) $(wildcard $(SRC_FOLDER)/*/*/*/*/*/*/*.cpp)
OBJ = $(SRC:.cpp=.o)

LIB_SRC = $(wildcard $(LIB_SRC_FOLDER)/*.cpp)
LIB_OBJ = $(LIB_SRC:.cpp=.o)

$(OBJ): WARNINGS = -Wall -Wextra
$(LIB_OBJ): WARNINGS =

debug: EXTRA += -g
debug: DEFINE += -DDEBUG
debug: all

release: EXTRA += -O3
release: all

all: $(OBJ) $(LIB_OBJ)

clean:
	rm -f $(OBJ)

clean_libs:
	rm -f $(LIB_OBJ)