[org 0x7c00]
mov [bootDisk], dl

main:
	; setting up 
	xor ax, ax
	mov es, ax

	; stack init
	mov bp, 0x8000
	mov sp, bp

	mov ah, 2 ; Must be 
	mov al, 1 ; how many sector to read
	mov ch, 0 ; cylinder number
	mov cl, 2 ; sector number
	mov dh, 0 ; head number
	mov dl, [bootDisk]
	mov bx, 0x7e00 ; address
	int 0x13

	; print the next sector
	call print

	jmp $

print:
	mov bx, 0x7e00

	mov ah, 0x0e ; setup for printing
	print_loop:
		mov al, [bx]
		int 0x10

		inc bx
		mov dx, [bx]
		cmp dx, 0
		jne print_loop

	ret

bootDisk: db 0

times 510 - ($-$$) db 0
dw 0xaa55
; defining 490 bytes after boot sector (more seems to have undefinded behavior)
times 490 db 'A'
db 0 ; defining last byte to be 0
