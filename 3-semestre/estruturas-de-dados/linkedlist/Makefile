CC = gcc
CFLAGS =
BUILD_DIR = build
SRC = ll.c untyped.c utils.c main.c
OBJNAMES = $(patsubst %.c, %.o, $(SRC))
OBJ = $(foreach item,$(OBJNAMES),./$(BUILD_DIR)/$(item))
TARGET = $(BUILD_DIR)/a.out

$(TARGET): $(BUILD_DIR) $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

run: $(TARGET)
	./$(TARGET)

debugrun: debug run

debug: CFLAGS += -g3 -fsanitize=address,undefined
debug: $(TARGET)

$(BUILD_DIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR):
	mkdir ./$(BUILD_DIR)

clean:
	rm -rf ./$(BUILD_DIR)
