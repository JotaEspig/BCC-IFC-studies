C=gcc
CFLAGS=-Wall -Wextra -Wpedantic -std=c99 -g -fsanitize=address,undefined
EXE_NAME=bin_tre
SRC=main.c \
	bin_tre.c

BUILD_DIR=build

OBJECTS=$(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))

all: $(OBJECTS)
	$(C) $(CFLAGS) -o $(BUILD_DIR)/$(EXE_NAME) $(OBJECTS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(C) $(CFLAGS) -c $< -o $@

clean: $(BUILD_DIR)
	-rm bin_tre $(BUILD_DIR)/*.o
