# Author: Éder Augusto Penharbel
# Adaptado por João Vitor Espig
# date: February, 2022
# version: September 6, 2024

.PHONY: clean image
SOURCE = template
BUILD_DIR=build
TARGET=$(BUILD_DIR)/floppy.img

all: image

$(BUILD_DIR):
	-mkdir -p $@ 2>/dev/null

# generate floppy.img file (a floppy disk)
# the file will be filled with zeros and have a floppy disk size
# it uses dd to create a file with zeros
$(TARGET): $(BUILD_DIR)
	dd if=/dev/zero of=$@ bs=512 count=2880

# compiling the source code with instructions mnemonics using GNU Assembly
$(BUILD_DIR)/$(SOURCE).o: $(SOURCE).s $(BUILD_DIR) 
	as $< -o $@

# linking to a plain 16 bits binary with addresses related to 0x7c00
$(BUILD_DIR)/$(SOURCE).bin: $(BUILD_DIR)/$(SOURCE).o $(BUILD_DIR) 
	ld --Ttext 0x7c00 --oformat=binary $(BUILD_DIR)/$(SOURCE).o -o $(BUILD_DIR)/$(SOURCE).bin

# copying the binary executable image to the first position of floppy.img file
image: $(BUILD_DIR)/$(SOURCE).bin $(TARGET)
	dd if=$(BUILD_DIR)/$(SOURCE).bin of=$(TARGET) bs=512 count=1 conv=notrunc

# delete all files generated 
clean:
	$(RM) -f $(TARGET)
	$(RM) -f $(BUILD_DIR)/$(SOURCE).o
	$(RM) -f $(BUILD_DIR)/$(SOURCE).bin
