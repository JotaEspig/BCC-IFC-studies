# Author: João Vitor Espig
# Adaptado do Makefile do Éder
#
# Uso: coloque as seguintes linhas no terminal
#
# make
# bochs -q

.PHONY: clean image
SOURCE = escreve_x
BUILD_DIR=build
TARGET=floppy.img

all: image

$(BUILD_DIR):
	-mkdir -p $(BUILD_DIR) 2>/dev/null

# Gera um arquivo floppy.img (simula um CD ou um pendrive)
# com 2880 blocos de 512 bytes (1.44 MB)
$(TARGET): $(BUILD_DIR)
	# o comando dd é usado para copiar e converter arquivos
	# if= é usado para especificar o arquivo de entrada
	# of= é usado para especificar o arquivo de saída
	# bs= é usado para especificar o tamanho do bloco
	# count= é usado para especificar o número de blocos a serem copiados
	#
	# usando /dev/null como arquivo de entrada para criar um arquivo vazio
	# /dev/zero retorna apenas bytes nulos (0, zero)
	dd if=/dev/zero of=$@ bs=512 count=2880

# Compilando o arquivo .s para um arquivo objeto .o
# (Coisas de assembly)
$(BUILD_DIR)/$(SOURCE).o: $(SOURCE).s $(BUILD_DIR) 
	as $< -o $@

# Linkando o arquivo objeto .o para um arquivo binário .bin
# Usa 0x7c00 como endereço de carregamento (coisas para permitir o boot do sistema no bochs)
$(BUILD_DIR)/$(SOURCE).bin: $(BUILD_DIR)/$(SOURCE).o $(BUILD_DIR) 
	ld --Ttext 0x7c00 --oformat=binary $(BUILD_DIR)/$(SOURCE).o -o $(BUILD_DIR)/$(SOURCE).bin

# Copia o binário executavel para o arquivo floppy.img
# O argumento conv=notrunc é necessária, sem ele da cagada :)
image: $(BUILD_DIR)/$(SOURCE).bin $(TARGET)
	dd if=$(BUILD_DIR)/$(SOURCE).bin of=$(TARGET) bs=512 count=1 conv=notrunc

# limpa os arquivos temporários
clean:
	$(RM) -f $(TARGET)
	$(RM) -f $(BUILD_DIR)$(SOURCE).o
	$(RM) -f $(BUILD_DIR)$(SOURCE).bin
