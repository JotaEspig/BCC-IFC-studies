section .data
    msg db "Hello World", 0xA
    msg_len equ $-msg

section .text
    global _start

_start:
    mov edx, msg_len
    mov ecx, msg
    mov ebx, 0x1
    mov eax, 4
    int 0x80

    mov ebx, 0
    mov eax, 1
    int 0x80
