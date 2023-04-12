filename=boot.asm

if [ $# -eq 1 ]; then
	filename=$1
fi

echo -e "\033[0;36massemblying\033[0m"
nasm -f bin $filename -o out.bin
qemu-system-x86_64 out.bin
echo -e "\033[1;31mremoving out.bin\033[0m"
rm out.bin
