CC=i386-elf-gcc
LD=i386-elf-ld
ASM=nasm

# TODO Improve a lot Makefile

run: build
	qemu-system-x86_64 -drive \
		format=raw,file="bin/OS.bin",index=0,if=floppy, -m 128M

objects:
	$(CC) -c src/boot/main.c src/functions/print.c -ffreestanding -m32 -g
	mv *.o obj/
	$(ASM) src/boot/kernel_entry.asm -f elf -o obj/kernel_entry.o

build: objects
	$(LD) -o bin/full_kernel.bin -Ttext 0x1000 \
		obj/kernel_entry.o obj/main.o obj/print.o --oformat binary
	$(ASM) src/boot/boot.asm -f bin -o bin/boot.bin
	$(ASM) src/boot/zereos.asm -f bin -o bin/zereos.bin
	cat bin/boot.bin bin/full_kernel.bin bin/zereos.bin > bin/OS.bin

.PHONY:dir
dir:
	if [ ! -d obj ]; then mkdir obj; fi
	if [ ! -d bin ]; then mkdir bin; fi

.PHONY:clean
clean:
	rm bin/*.bin
	rm obj/*.o
