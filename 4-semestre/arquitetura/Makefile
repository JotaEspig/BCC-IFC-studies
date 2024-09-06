# Author: Éder Augusto Penharbel
# date: February, 2022
# version: September 6, 2024

.PHONY: clean image
SOURCE = writex

all: image

# generate floppy.img file (a floppy disk)
# the file will be filled with zeros and have a floppy disk size
# it uses dd to create a file with zeros
floppy.img:
	dd if=/dev/zero of=$@ bs=512 count=2880

# compiling the source code with instructions mnemonics using GNU Assembly
$(SOURCE).o: $(SOURCE).s
	as $< -o $@

# linking to a plain 16 bits binary with addresses related to 0x7c00
$(SOURCE).bin: $(SOURCE).o
	ld --Ttext 0x7c00 --oformat=binary $(SOURCE).o -o $(SOURCE).bin

# copying the binary executable image to the first position of floppy.img file
image: $(SOURCE).bin floppy.img
	dd if=$(SOURCE).bin of=floppy.img bs=512 count=1 conv=notrunc

# delete all files generated 
clean:
	$(RM) -f floppy.img
	$(RM) -f $(SOURCE).o
	$(RM) -f $(SOURCE).bin
