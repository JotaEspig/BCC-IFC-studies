if [ ! $# -eq 1 ]; then
    echo -e "Invalid amount of arguments\nUse: ./run.sh <filename>"
    exit
fi

filename=$1
nasm -f elf64 $filename -o $filename.o
ld $filename.o -o $filename.out
./$filename.out
rm $filename.o $filename.out
