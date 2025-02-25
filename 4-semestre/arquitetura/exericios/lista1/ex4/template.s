.code16

.text
.globl _start
_start:
    xor %ax, %ax
    # 1 (Fatorial)
    movb $0x05, %al
    call fat

    # 2 (algoritmo de sorgin O(n²): Bubble sort)
    call sort

    # 3 (Uso da stack como forma de passar argumentos)
    mov $0x120c, %dx
    push $'A'
    push %dx
    # número de argumentos
    push $2
    call print_char_at
    add $6, %sp # Remove os argumentos da pilha

    jmp loop_final


fat:
    mov %ax, %cx
fat_loop:
    dec %cx
    mul %cx
    cmp $0x01, %cx
    jne fat_loop
    ret

    # Bubble sort (exercicio 2)
sort:
    xor %cx, %cx
    decb %cl
    mov %cl, %ch
sort_loop_1:
    incb %ch
    cmpb (arr_size), %ch
    je sort_final
sort_loop_2:
    incb %cl
    mov (arr_size), %bl
    dec %bl
    cmpb %bl, %cl
    je sort_loop_1

    lea arr, %bp
    xor %dx, %dx
    mov %cl, %dl
    mov %dx, %si
    inc %dx
    mov %dx, %di

    mov (%bp, %si), %al
    mov (%bp, %di), %ah
    cmp %al, %ah
    jge sort_loop_2
    mov %ah, (%bp, %si)
    mov %al, (%bp, %di)

    jmp sort_loop_2


sort_final:
    ret


print_char_at:
    pusha
    # Gets the arguments from the stack
    movw %sp, %bp
    movw 18(%bp), %ax
    cmp $2, %ax
    jne _print_char_at_error
    # Go to coordinates
    movw 20(%bp), %dx
    movb $2, %ah
    movb $0, %bh
    int $0x10

    # Print the character
    movw 22(%bp), %ax
    movb $0x0e, %ah
    int $0x10
    popa
    movw $0, 18(%bp) # Return code (0 = success)
    ret

_print_char_at_error:
    movw $1, 18(%bp) # Return code (1 = error in the number of arguments)
    popa
    ret


loop_final:
    hlt
    jmp loop_final


. = _start + 400
arr_size:
    .byte 0x05
arr:
    .byte 0x04
    .byte 0x03
    .byte 0x08
    .byte 0x01
    .byte 0x02


. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
