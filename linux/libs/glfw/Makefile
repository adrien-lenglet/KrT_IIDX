
.DEFAULT_GOAL := all

BIN_FOLDER = ../bin

TARGET = libglfw.so
TARGET_BIN = $(addprefix ../bin/, $(TARGET))

$(TARGET_BIN):
	cp /usr/lib/$(TARGET) $(TARGET_BIN)

all: $(TARGET_BIN)

clean:
	rm -f $(TARGET_BIN)

.PHONY: all clean
