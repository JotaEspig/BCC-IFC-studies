.code16

.text
.globl _start
_start:
    xor %ax, %ax
    # 1
    movb $0x05, %al
    call fat

    call sort

    jmp loop_final


loop_final:
    hlt
    jmp loop_final

fat:
    mov %ax, %cx
fat_loop:
    dec %cx
    mul %cx
    cmp $0x01, %cx
    jne fat_loop
    ret

    # 2 (Bubble sort)
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

    mov (%bp, %si, 1), %al
    mov (%bp, %di, 1), %ah
    cmp %al, %ah
    jge sort_loop_2
    mov %ah, (%bp, %si, 1)
    mov %al, (%bp, %di, 1)

    jmp sort_loop_2


sort_final:
    ret


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
