.code16

.text
.globl _start
_start:
    # 1
    mov $10, %bx
    mov $20, %ax
    add %bx, %ax

    # 2
    mov $10, %ax
    mov $20, %bl
    mul %bl

    # 3
    mov $10, %ax
    mov $3, %bl
    div %bl

    # 4
    xor %ax, %ax
    and %ax, %ax
    or %ax, %ax
    not %ax

    jmp loop_final


loop_final:
    hlt
    jmp loop_final


. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
