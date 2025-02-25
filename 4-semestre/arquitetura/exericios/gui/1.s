.code16





.text

.globl _start

_start:
    # Realizando soma
    mov $1, %ax
    mov $7, %bx
    add %bx, %ax

    # Realizando multiplicação
    mov $7, %ax
    mov $2, %bl
    mul %bl

    # Realizando divisão
    mov $20, %ax
    mov $2, %bl
    div %bl

    # Algumas operações lógicas
    or %ax, %ax
    and $0x01, %ax

    hlt


. = _start + 510

# Bytes para fazer Boot
.byte 0x55
.byte 0xaa
