.code16

.text
.globl _start
_start:
    movb $0, %cl
loop:
    inc %cl
    cmp $10, %cl
    jne loop


loop_final:
    hlt
    jmp loop_final


. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
