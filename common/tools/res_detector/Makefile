COMMON_SRC_FOLDER = ../../src
RESOURCES_SRC = $(wildcard $(COMMON_SRC_FOLDER)/Subtile/Resource/*.cpp)

CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I $(COMMON_SRC_FOLDER)

SRC_FOLDER = src
SRC = $(wildcard $(SRC_FOLDER)/*.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = res_detector

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(COMMON_SRC_FOLDER)/Subtile/Shader.cpp $(RESOURCES_SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: clean
