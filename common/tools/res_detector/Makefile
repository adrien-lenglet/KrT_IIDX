COMMON_SRC_FOLDER = ../../src
RESOURCES_SRC = $(wildcard $(COMMON_SRC_FOLDER)/Subtile/Resource/*.cpp)

CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I $(COMMON_SRC_FOLDER)

SRC_FOLDER = src
SRC = $(wildcard $(SRC_FOLDER)/*.cpp)
OBJ = $(SRC:.cpp=.o)

TARGET = res_detector
all: $(TARGET)

%.res_detector.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

ENGINE_SRC = $(COMMON_SRC_FOLDER)/Subtile/Shader.cpp $(RESOURCES_SRC) 
ENGINE_OBJ = $(ENGINE_SRC:.cpp=.res_detector.o)
ENGINE_DEPS = engine_deps.o

$(ENGINE_DEPS): $(ENGINE_SRC)
	$(MAKE) $(ENGINE_OBJ)
	ar rcs $(ENGINE_DEPS) $(ENGINE_OBJ)
	rm -f $(ENGINE_OBJ)

$(TARGET): $(ENGINE_DEPS) $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(ENGINE_DEPS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJ) $(ENGINE_DEPS)

.PHONY: clean
