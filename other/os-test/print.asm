[bits 16]
[org 0x7c00]

jmp main

print:
        mov cx, 0  ; initialize the counter
        mov bx, 10 ; saves the base

        convert_loop:
        inc cl
        mov dx, 0 ; reset the remainder of the divison
        div bx    ; divides by bx (10)
        push dx   ; save the rest
        cmp al, 0
        jne convert_loop

        print_loop:
        pop dx        ; get the number
        mov al, dl
        add al, '0'   ; get number value in ascii character
        mov ah, 0x0e
        int 0x10

        dec cl
        jnz print_loop

        ret

main:
        ; Stack init
        mov bp, 0x8000
        mov sp, bp

        mov ax, [number]
        call print
        jmp $

number: db 123

times 510 - ($-$$) db 0
db 0x55, 0xaa
