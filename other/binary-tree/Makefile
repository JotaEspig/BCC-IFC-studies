CC=gcc
CC_FLAGS=

SRC=$(wildcard ./btree/*.c)
TARGET_NAME=binary-tree
TARGET_FOLDER=./bin/

all: dir
	$(CC) main.c $(SRC) $(CC_FLAGS) -o $(TARGET_FOLDER)$(TARGET_NAME)

dir:
	if [ ! -d "./bin" ]; then mkdir bin; fi

run: all
	@ $(TARGET_FOLDER)$(TARGET_NAME) $(IP)
