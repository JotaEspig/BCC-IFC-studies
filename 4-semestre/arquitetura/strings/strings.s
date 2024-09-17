.code16

.text
.globl _start
_start:
    movb $0x0e, %ah
    movb $'j' , %al
    int  $0x10
    call new_line

    push $str
    call print_str
    add $2, %sp
    call new_line

    push $str2
    call print_str
    add $2, %sp
    call new_line

    jmp loop_final


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


print_str:
    pusha
    mov %sp, %bp
    mov 18(%bp), %si
    movb $0x0e, %ah
print_char_loop:
    cmpb $0, (%si)
    je print_char_end
    movb (%si), %al
    int $0x10
    inc %si
    jmp print_char_loop
print_char_end:
    popa
    ret


loop_final:
    hlt
    jmp loop_final


# Simulating a data segment
. = _start + 400
str:
    .asciz "Hello, World!" # Or .string "Hello, World!"
    .byte 0x03 # This doesnt "break" the string because asciz adds a null byte at the end
str2:
    .ascii "Without Zero at end"
    .byte 0x03 # This DOES "break" the string because ascii DO NOT add a null byte at the end

. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
