[bits 16]
[org 0x7c00]

; GDT (Global Descriptor Table) !important
; Code segment
; 	- Base (32 bits)    = 0
;	- Limit (20 bits)   = 0xfffff (highest value possible)
; 	- Present			= 1 (it's used and valid)
;	- Privilege 		= 00 (highest)
; 	- type 				= 1 (it's code or data segment)
; 	- Type flags  = 1010
;		- Code       = 1
;		- Conforming = 0
; 		- Readable   = 1
;		- Acessed    = 0
; 	- Other flags = 1100
;		- Graunularity = 1 => limit *= 0x1000
;		- 32 bits = 1
;		Other 2 bits are set to 0
; Data segment
; 	- pres,priv,type = 1001
; 	- Type Flags = 0010
;		- Code      = 0
;		- Direction = 0
;		- Writable  = 1
;		- Accessed  = 0
;	- Other flags = 1100

GDT_Start:
	null_descriptor:
		dd 0
		dd 0
	code_descriptor:
		dw 0xffff 	  ; first 16 bits (of 20) of limit
		dw 0 		  ; first 24 bits (of 32) of base
		db 0 		  ; 16 + 8 = 24
		db 0b10011010 ; p,p,v and type flags
		db 0b11001111 ; other flags + last 4 bits of limit
		db 0		  ; last 8 bits of base
	data_descriptor:
		dw 0xffff     ; limit
		dw 0 	      ; base
		db 0      	  ; base
		db 0b10010010 ; p,p,v and type flags
		db 0b11001111 ; other flags + limit
		db 0		  ; base
GDT_End:

GDT_Descriptor:
	dw GDT_End - GDT_Start - 1 ; size
	dw GDT_Start			   ; start

CODE_SEG equ code_descriptor - GDT_Start ; offset to code seg
DATA_SEG equ data_descriptor - GDT_Start ; offset to data seg

cli
lgdt [GDT_Descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax ; enters 32 bit mode
jmp CODE_SEG:start_protected_mode

[bits 32]
start_protected_mode:
	; write in video memory 0xb8000
	; first byte: char
	; second byte: color
	mov al, 'A'
	mov ah, 0x0f ; color
	mov [0xb8000], ax
	jmp $

times 510-($-$$) db 0
dw 0xaa55
