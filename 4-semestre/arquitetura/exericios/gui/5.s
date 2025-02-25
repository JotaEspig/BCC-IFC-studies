.code16

.text
.globl _start

_start:
    # Leitura de teclado. Exibe na tela o valor lido
    xor %ax, %ax # Limpa ax, necessário para o int 0x16
    int $0x16 # valor salvo fica em al
    movb $0x0e, %ah
    int $0x10

    # Loop que le string (varios caracteres) até que o enter seja pressionado
loop_string:
    xor %ax, %ax
    int $0x16
    cmpb $0x1c, %ah # 0x1c é o valor do enter
    je loop_string_fim
    mov $0x0e, %ah
    int $0x10

    jmp loop_string

loop_string_fim:
    movb $0x0a, %al # \n
    movb $0x0e, %ah
    int $0x10
    movb $0x0d, %al # \r
    int $0x10

    hlt



. = _start + 510


.byte 0x55
.byte 0xaa
