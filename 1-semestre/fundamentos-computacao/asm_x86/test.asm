section .data
    msg db "Hello World", 0xA
    msg_len equ $-msg

section .bss
    sub_val resb 4

section .text
    global _start

_start:
    mov edx, msg_len
    mov ecx, msg
    mov ebx, 0x1
    mov eax, 0x4
    int 0x80

    mov eax, 0xA
    mov ebx, 0x6
    not ebx
    inc ebx
    add eax, ebx
    mov [sub_val], eax 

    mov edx, 0x2
    mov ecx, [sub_val]
    mov ebx, 0x1
    mov eax, 0x4
    int 0x80      ; for some reason it doesnt show in the terminal the value 6

    mov ebx, 0x0
    mov eax, 0x1
    int 0x80
