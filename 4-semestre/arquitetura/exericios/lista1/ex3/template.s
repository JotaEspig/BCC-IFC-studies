.code16

.text
.globl _start
_start:
    # 1 (Loop de 0 a 10)
    movb $0, %cl
loop:
    inc %cl
    cmp $10, %cl
    jne loop

    # 2 (Verifica se é impar)
    xor %ax, %ax
    mov $0x01, %ax
    call is_odd

    # 3 (Utilização de instruções de jump)
    cmp $0x01, %ax
    jl loop_final
    movb $0x0e, %ah
    movb $'1', %al
    int $0x10
    # instruçoes de loop também são utilizadas em todo o código (jgt, jne, jmp)


loop_final:
    hlt
    jmp loop_final


# Ax = 0x01 se é impar e 0x00 se é par
is_odd:
    and $0x01, %ax
    ret


. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
