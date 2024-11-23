.code16

.text
.globl _start
_start:
    # 1
    movw (v1), %ax

    # 2
    movb $0x43, (v1)
    movb $0x21, (v1 + 1)

    # 3
    movb $0, %cl
    movw $0, %ax
    movw $arr, %si
loop:
    cmp $4, %cl
    je loop_final
    addb (%si), %al
    inc %cl
    inc %si
    jmp loop
    

    jmp loop_final


loop_final:
    hlt
    jmp loop_final


. = _start + 400
v1: .word 0x1234
arr: .byte 0x4, 0x2, 0x3, 0x4

. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
