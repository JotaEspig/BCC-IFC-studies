.code16

.text

.globl _start




_start:
    # Leitura da memória
    movb (variavel), %ah

    # Escrita na memória
    movb $0x13, (variavel)

    # Soma de um array
    mov $0, %cl
    mov $0, %ax
    lea array_para_somar, %di
loop_soma:
    cmp $4, %cl # 4 é o tamanho do array
    je loop_soma_fim
    inc %cl
    addb (%di), %al
    inc %di
    jmp loop_soma
loop_soma_fim:
    
    hlt


. = _start + 300

variavel: .byte 0x00
array_para_somar: .byte 0x1, 0x2, 0x3, 0x4



. = _start + 510

.byte 0x55
.byte 0xaa
