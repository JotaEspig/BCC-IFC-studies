CC = gcc
CFLAGS = 
BUILD_DIR = build
SRC = ll.c untyped.c main.c
OBJNAMES = ll.o untyped.o main.o
OBJ = $(foreach item,$(OBJNAMES),./$(BUILD_DIR)/$(item))
TARGET = $(BUILD_DIR)/a.out

a.out: $(BUILD_DIR) $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(BUILD_DIR)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR):
	mkdir ./$(BUILD_DIR)

clean:
	rm -rf ./$(BUILD_DIR)
