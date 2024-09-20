.code16

.text
.globl _start
_start:

    mov $80, %cx
    movb $'x' , %al
oops:
    movb $0x0e, %ah
    int  $0x10
    dec  %cx
    jnz  oops


mov $22, %ch
big:
    movb $'x', %al
    movb $0x0e, %ah
    int $0x10
    movb $78, %cl
    movb $' ' , %al

big_m:
    movb $0x0e, %ah
    int  $0x10
    decb  %cl
    jnz big_m 

    movb $'x', %al
    movb $0x0e, %ah
    int $0x10

    decb %ch
    jnz big

    mov $80, %cx
    movb $'x' , %al
oops2:
    movb $0x0e, %ah
    int  $0x10
    dec  %cx
    jnz  oops2

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


loop_final:
    hlt
    jmp loop_final


. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
