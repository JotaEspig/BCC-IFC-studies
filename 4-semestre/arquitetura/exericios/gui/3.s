.code16

.text
.globl _start


_start:
    # For loop de 1 a 10
    movb $0, %cl
for_loop:
    inc %cl
    cmp $10, %cl
    jne for_loop

    # Verifica se é impar usando a instrução AND, se AX for 1, significa que é impar
    xor %ax, %ax
    mov $0x07, %bx # o numero exemplo é 7
    and $0x01, %bx

    # Utilização de junções jump e também imprime 1 se for impar
    cmp $0x01, %bx
    jl fim_Programa
    movb $0x0e, %ah
    movb $'1', %al
    int $0x10


fim_Programa:
    hlt
. = _start + 510

.byte 0x55
.byte 0xaa
