.code16

.text
.globl _start

_start:
    # implementa fatorial
    mov $0x0000, %ax # Limpa ax
    movb $0x05, %al # 5! = 120
    mov %ax, %cx
fatorial_loop:
    dec %cx
    mul %cx
    cmp $0x01, %cx
    jne fatorial_loop
    # Termina execução, ax tendo o resultado

    # ordena um array
    call ordena_array

    # Usando stack para passar argumentos
    push $'A'
    call imprimir_letra
    add $6, %sp # Remove os argumentos da pilha

    hlt

ordena_array:
    mov $0, %cx
    decb %cl
    mov %cl, %ch

# Primeiro for do bubble sort
ordena_array_loop_1:
    incb %ch
    cmpb (tamanhoDoArray), %ch
    je ordena_array_final

# Segundo for do bubble sort
ordena_array_loop_2:
    incb %cl
    mov (tamanhoDoArray), %bl
    dec %bl
    cmpb %bl, %cl
    je ordena_array_loop_1

    lea Array, %bp
    xor %dx, %dx
    mov %cl, %dl
    mov %dx, %si
    inc %dx
    mov %dx, %di

    mov (%bp, %di, 1), %ah
    mov (%bp, %si, 1), %al
    cmp %al, %ah
    jge ordena_array_loop_2
    mov %al, (%bp, %di, 1)
    mov %ah, (%bp, %si, 1)

    jmp ordena_array_loop_2


ordena_array_final:
    ret


imprimir_letra:
    movw 2(%bp), %ax # pega na stack a letra
    movb $0x0e, %ah
    int $0x10
    ret


. = _start + 300

tamanhoDoArray:
    .byte 0x05
Array:
    .byte 0x06
    .byte 0x05
    .byte 0x04
    .byte 0x0e
    .byte 0x03


. = _start + 510

.byte 0x55
.byte 0xaa
