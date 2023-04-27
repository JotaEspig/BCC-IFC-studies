CC=i386-elf-gcc
LD=i386-elf-ld
ASM=nasm
OBJ_DIR=obj
TARGET_DIR=bin
SRC_DIR=src

run: %.bin
	qemu-system-x86_64 -drive \
		format=raw,file="$(TARGET_DIR)/OS.bin",index=0,if=floppy, -m 128M
	$(MAKE) clean

%.o:
	$(CC) -c $(SRC_DIR)/kernel.c -o $(OBJ_DIR)/kernel.o -ffreestanding -m32 -g
	$(ASM) $(SRC_DIR)/kernel_entry.asm -f elf -o $(OBJ_DIR)/kernel_entry.o

%.bin: %.o
	$(LD) -o $(TARGET_DIR)/full_kernel.bin -Ttext 0x1000 \
		$(OBJ_DIR)/kernel_entry.o $(OBJ_DIR)/kernel.o --oformat binary
	$(ASM) $(SRC_DIR)/boot.asm -f bin -o $(TARGET_DIR)/boot.bin
	$(ASM) $(SRC_DIR)/zereos.asm -f bin -o $(TARGET_DIR)/zereos.bin
	cat $(TARGET_DIR)/boot.bin $(TARGET_DIR)/full_kernel.bin \
		$(TARGET_DIR)/zereos.bin > $(TARGET_DIR)/OS.bin
.PHONY:clean
dir:
	if [ ! -d obj ]; then mkdir obj; fi
	if [ ! -d bin ]; then mkdir bin; fi
.PHONY:clean
clean:
	rm $(TARGET_DIR)/*.bin
	rm $(OBJ_DIR)/*.o
