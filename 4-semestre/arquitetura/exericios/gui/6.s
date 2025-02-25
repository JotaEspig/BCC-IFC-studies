.code16

.text
.globl _start


_start:
    # Copia strings
    mov $string_1, %si
    mov $string_copia, %di
copiar_loop:
    movb (%si), %al
    movb %al, (%di)
    inc %si
    inc %di
    cmpb $0x00, %al
    jne copiar_loop

    # Compara as strings
    xor %ax, %ax
    lea string_1, %si
    lea string_2, %di
comparar_loop:
    movb (%si), %al
    movb (%di), %ah
    cmpb $0x00, %al # se for o fim da string, termina
    je comparar_fim
    cmpb $0x00, %ah # se for o fim da string, termina
    je comparar_fim
    inc %si
    inc %di
    cmpb %ah, %al
    je comparar_loop
    # se for diferente e se ambos não forem 0, significa que são diferentes
    mov $2, %ax # 2 para dizer q são diferentes
    comparar_fim:

    # Concatena strings
    mov $string_1, %si
    mov $string_copia, %di
concatena_loop:
    movb (%si), %al
    movb %al, (%di)
    inc %si
    inc %di
    cmpb $0x00, %al
    jne concatena_loop

    # Retorna para o caracter que indica o fim da string
    dec %di
    # Copia string_2 agora
    mov $string_2, %si
concatena2_loop:
    movb (%si), %al
    movb %al, (%di)
    inc %si
    inc %di
    cmpb $0x00, %al
    jne concatena2_loop

    hlt



. = _start + 300
string_1:
    .asciz "Guilherme o melhor"
string_2:
    .asciz "Eu sou o melhor"
string_copia:
    .byte 0x00


. = _start + 510

.byte 0x55
.byte 0xaa
