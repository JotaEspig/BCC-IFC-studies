.code16

.text
.globl _start
_start:
    movb $0x0e, %ah
    movb $'j' , %al
    int  $0x10
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


loop_final:
    hlt
    jmp loop_final


. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
