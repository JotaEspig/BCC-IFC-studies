.code16

.text
.globl _start
_start:
    # 1 (copia strings)
    mov $str1, %si
    mov $str_dest, %di
copy_loop:
    movb (%si), %al
    movb %al, (%di)
    inc %si
    inc %di
    cmpb $0x00, %al
    jne copy_loop

    # 2 compara strings (AX = 0 se iguais)
    xor %ax, %ax
    mov $str1, %si
    mov $str1, %di # a mesma string para retornar verdadeiro (valor 0 no AX)
cmp_loop:
    movb (%si), %al
    movb (%di), %ah
    cmpb $0x00, %al
    je cmp_fim
    cmpb $0x00, %ah
    je cmp_fim
    inc %si
    inc %di
    cmpb %ah, %al
    je cmp_loop
    mov $0x01, %ax
cmp_fim:

    # 3 (concatena strings)
    mov $str1, %si
    mov $str_dest, %di
concatena_loop:
    movb (%si), %al
    movb %al, (%di)
    inc %si
    inc %di
    cmpb $0x00, %al
    jne concatena_loop

    # volta para o último caractere
    dec %di
    # copia a segunda string para terminar a concatenação
    mov $str2, %si
concatena2_loop:
    movb (%si), %al
    movb %al, (%di)
    inc %si
    inc %di
    cmpb $0x00, %al
    jne concatena2_loop


loop_final:
    hlt
    jmp loop_final


. = _start + 400
str1:
    .asciz "Blable"
str2:
    .asciz "foobar"
str_dest:
    .byte 0x00

. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
