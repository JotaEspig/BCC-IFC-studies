.code16

.text
.globl _start
_start:
    movb $0x0e, %ah
    movb $'j' , %al
    int  $0x10
    call new_line

    push $str
    call print_string
    call new_line

    call print_len
    call new_line

    call print_inverted_str
    call new_line
    # Clean up the stack
    addw $2, %sp

    jmp loop_final


print_string:
    pusha
    movw %sp, %bp
    movw 18(%bp), %si
    movb $0x0e, %ah
_print_char_loop:
    cmpb $0, (%si)
    je _print_char_end
    movb (%si), %al
    int $0x10
    incw %si
    jmp _print_char_loop

_print_char_end:
    popa
    ret


print_len:
    pusha
    movw %sp, %bp
    movw 18(%bp), %si
    movb $0x0e, %ah
    xorb %cl, %cl
_print_len_loop:
    cmpb $0, (%si)
    je _print_len_end
    incb %cl
    incw %si
    jmp _print_len_loop

_print_len_end:
    addb $'0', %cl
    movb %cl, %al
    int $0x10
    popa
    ret


print_inverted_str:
    pusha
    movw %sp, %bp
    movw 18(%bp), %si
    xorb %ah, %ah
    push $0
_print_inv_char_loop:
    cmpb $0, (%si)
    je _print_inv_char_loop2
    movb (%si), %al
    push %ax
    incw %si
    jmp _print_inv_char_loop

_print_inv_char_loop2:
    pop %ax
    cmpw $0, %ax
    je _print_inv_char_end
    movb $0x0e, %ah
    int $0x10
    jmp _print_inv_char_loop2

_print_inv_char_end:
    popa
    ret



new_line:
    pusha
    # new line
    movb $0x0a, %al
    movb $0x0e, %ah
    int $0x10
    # move cursor to the beginning of the line
    movb $0x0d, %al
    int $0x10
    popa
    ret


loop_final:
    hlt
    jmp loop_final


. = _start + 400
str:
    .asciz "Hello!"


. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
