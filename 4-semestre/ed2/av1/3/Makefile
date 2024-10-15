CC=gcc
CC_FLAGS = -g3 -Wall -Wextra -Werror -std=c99 -fsanitize=address,undefined
BUILD_DIR=build
TARGET=$(BUILD_DIR)/btree
SOURCE=btree.c main.c
OBJECTS=$(patsubst %.c,$(BUILD_DIR)/%.o,$(SOURCE))

.PHONY: $(BUILD_DIR) clean

all: $(BUILD_DIR) $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
