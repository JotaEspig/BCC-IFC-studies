CC = g++
CC_FLAGS = -Wall
SRC := $(shell find ./src -name "*.cpp")
TARGET = chess

build: dir
	$(CC) $(CC_FLAGS) $(SRC) -o ./bin/$(TARGET)

run: build
	./bin/$(TARGET)
	$(MAKE) clean

debug: dir
	$(CC) $(CC_FLAGS) -g $(SRC) -o ./bin/$(TARGET)

.PHONY: dir
dir:
	if [ ! -d "./bin/" ]; then mkdir bin; fi

.PHONY: clean
clean:
	rm ./bin/*
