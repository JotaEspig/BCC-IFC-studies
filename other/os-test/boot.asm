[org 0x7c00]

_start:
	jmp input

print:
	mov ah, 0x0e ; sets ah to 0x0e for bios print
	mov bx, msg  ; sets bytes to be printed
print_loop:
    mov al, [bx] ; set character to be printed
	cmp al, 0x0  ; if is null byte exit
	je exit
    int 0x10
	inc bx
	jmp print_loop

input:
	mov bx, msg
input_loop:
	mov ah, 0x0 ; sets ah to 0x0 for bios reading key
	int 0x16
	cmp al, '-' ; if its ! goes to print
	je print

	mov [bx], al
	inc bx
	jmp input_loop

exit:
	jmp $

msg: times 10 db 0

times 510 - ($-$$) db 0
db 0x55, 0xaa
