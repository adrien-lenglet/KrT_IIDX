
.DEFAULT_GOAL := all

BIN_FOLDER = ../../..

TARGET = glfw3.dll
TARGET_BIN = $(addprefix $(BIN_FOLDER)/, $(TARGET))

$(TARGET_BIN):
	cp $(TARGET) $(TARGET_BIN)

all: $(TARGET_BIN)

clean:
	rm -f $(TARGET_BIN)

.PHONY: all clean
