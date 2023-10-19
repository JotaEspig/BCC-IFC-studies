CC = gcc
CC_FLAGS = -Wall -Wextra

TARGET = tests
OBJECTS = hashmap.o tests.o

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

hashmap.o: hashmap.c hashmap.h
	$(CC) -c hashmap.c $(CC_FLAGS)

tests.o: tests.c
	$(CC) -c tests.c $(CC_FLAGS)

.PHONY: clean
clean:
	@rm *.o 2>/dev/null
