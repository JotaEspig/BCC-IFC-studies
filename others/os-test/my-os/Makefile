CC = i386-elf-gcc
CC_FLAGS = -ffreestanding -m32 -g -I./include/
LD = i386-elf-ld
LD_FLAGS = -Ttext 0x1000 --oformat binary
ASM = nasm

TARGET_DIR = bin
TARGET = $(TARGET_DIR)/OS.bin

OBJ_DIR = obj
OBJ = $(OBJ_DIR)/main.o $(OBJ_DIR)/print.o $(OBJ_DIR)/kernel_entry.o

BINARY_DIR = bin
# the order is important
BINARY = $(BINARY_DIR)/boot.bin $(BINARY_DIR)/full_kernel.bin $(BINARY_DIR)/zereos.bin

all: dir $(TARGET)

$(TARGET): $(BINARY)
	@cat $^ > $@

$(BINARY_DIR)/full_kernel.bin: $(OBJ)
	$(LD) -o $@ $(LD_FLAGS) $^

$(BINARY_DIR)/boot.bin: src/boot.asm
	$(ASM) $< -f bin -o $@

$(BINARY_DIR)/zereos.bin: src/zereos.asm
	$(ASM) $< -f bin -o $@

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJ_DIR)/kernel_entry.o: src/kernel_entry.asm
	$(ASM) $< -f elf -o $@

run: $(all)
	qemu-system-x86_64 -drive format=raw,file="$(TARGET)",index=0,if=floppy, -m 128M

.PHONY: clean
clean: dir
	-rm $(TARGET_DIR)/* 2> /dev/null
	-rm $(OBJ_DIR)/* 2> /dev/null
	-rm $(BINARY_DIR)/* 2> /dev/null

.PHONY: dir
dir:
	-mkdir $(TARGET_DIR) 2> /dev/null
	-mkdir $(OBJ_DIR) 2> /dev/null
	-mkdir $(BINARY_DIR) 2> /dev/null
