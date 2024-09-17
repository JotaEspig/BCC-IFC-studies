CC=gcc
CC_FLAGS=-lm -g3 -fsanitize=address,undefined
BUILD_DIR=build
TARGET=$(BUILD_DIR)/trietree
SOURCE=trietree.c main.c
OBJECTS=$(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCE))

.PHONY: $(BUILD_DIR) clean

all: $(BUILD_DIR) $(OBJECTS)
	$(CC) $(CC_FLAGS) -o $(TARGET) $(OBJECTS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
