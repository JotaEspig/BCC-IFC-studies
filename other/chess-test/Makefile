CC = g++
CC_FLAGS = 
SRC = $(find ./src -name "*.cpp")
TARGET = chess

build: dir
	$(CC) $(CC_FLAGS) $(SRC) -o $(TARGET)

run: build
	./bin/$(TARGET)
	$(MAKE) clean

.PHONY: dir
dir:
	if [ ! -d "./bin/" ]; then mkdir bin; fi

.PHONY: clean
clean:
	rm ./bin/*
