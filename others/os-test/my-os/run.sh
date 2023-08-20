# deprecated file. Use: make

echo "=== DEPRECATED ==="
echo -e "USE: make\n\n"

i386-elf-gcc -ffreestanding -m32 -g -c "src/kernel.c" -o "obj/kernel.o"
nasm "src/kernel_entry.asm" -f elf -o "obj/kernel_entry.o"
i386-elf-ld -o "bin/full_kernel.bin" -Ttext 0x1000 "obj/kernel_entry.o" "obj/kernel.o" --oformat binary
nasm "src/boot.asm" -f bin -o "bin/boot.bin"
nasm "src/zereos.asm" -f bin -o "bin/zereos.bin"
cat "bin/boot.bin" "bin/full_kernel.bin" "bin/zereos.bin" > "bin/OS.bin"

qemu-system-x86_64 -drive format=raw,file="bin/OS.bin",index=0,if=floppy, -m 128M
