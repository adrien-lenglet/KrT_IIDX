CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I ../../src

SRC_FOLDER = src
SRC = $(wildcard $(SRC_FOLDER)/*.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = res_detector

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)

.PHONY: clean
