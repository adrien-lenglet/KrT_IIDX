CXX = clang++
CXXFLAGS = -std=c++17 -g

SRC_FOLDER = src
SRC = $(wildcard $(SRC_FOLDER)/*.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = res_detector

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ)

.PHONY: clean