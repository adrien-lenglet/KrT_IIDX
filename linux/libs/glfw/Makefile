
.DEFAULT_GOAL := all

BIN_FOLDER = ../bin

TARGET = libglfw.so
TARGET_BIN = $(addprefix ../bin/, $(TARGET))
TARGET_3 = libglfw.so.3
TARGET_3_BIN = $(addprefix ../bin/, $(TARGET_3))
TARGET_3_4 = libglfw.so.3.4
TARGET_3_4_BIN = $(addprefix ../bin/, $(TARGET_3_4))
TARGET_BIN_ALL = $(TARGET_BIN) $(TARGET_3_BIN) $(TARGET_3_4_BIN)

$(TARGET_BIN):
	cp $(TARGET) $(TARGET_BIN)

$(TARGET_3_BIN):
	cp $(TARGET_3) $(TARGET_3_BIN)

$(TARGET_3_4_BIN):
	cp $(TARGET_3_4) $(TARGET_3_4_BIN)

all: $(TARGET_BIN_ALL)

clean:
	rm -f $(TARGET_BIN_ALL)

.PHONY: all clean
