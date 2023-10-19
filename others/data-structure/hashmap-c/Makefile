CC = gcc
CC_FLAGS = -Wall -Wextra

TARGET = tests
OBJECTS = hashmap.o tests.o

debug: CC_FLAGS += -g -fsanitize=address
debug: $(TARGET)
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(CC_FLAGS)

hashmap.o: hashmap.c hashmap.h
	$(CC) -c hashmap.c $(CC_FLAGS)

tests.o: tests.c
	$(CC) -c tests.c $(CC_FLAGS)

.PHONY: clean
clean:
	@rm *.o 2>/dev/null
