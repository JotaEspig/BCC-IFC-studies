[org 0x7c00]

KERNEL_LOCATION equ 0x1000

; Saves the disk that the boot.asm has been loaded
BOOT_DISK: db 0
mov [BOOT_DISK], dl

; Setting up Extra segment and Data segment to 0.
; Doing that basically disables segmentation for these two
xor ax, ax
mov es, ax
mov ds, ax

; Stack Init
mov bp, 0x8000
mov sp, bp

; Reading disk process
; Save kernel address
mov bx, KERNEL_LOCATION
mov dh, 20 ; this number is used for amount sectors to read

mov ah, 2  ; Must be 2
mov al, dh ; How many sectors to read
mov ch, 0  ; Cylinder number
mov dh, 0  ; head number
mov cl, 2  ; What sector to read
mov dl, [BOOT_DISK] ; disk number
int 0x13

mov ah, 0x0
mov al, 0x3
int 0x10 ; text mode (clears the screen)

; GDT to enter protected mode
CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start

cli ; stops BIOS interrupts
lgdt [GDT_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax ; enables protected mode
jmp CODE_SEG:start_protected_mode

; Read about GDT (Global Descriptor Table)
GDT_start:
    GDT_null:
        dd 0x0
        dd 0x0

    GDT_code:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0x0

    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0x0

GDT_end:

GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start


[bits 32]
start_protected_mode:
    ; set up segment registers
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; set up stack
    mov ebp, 0x90000 ; 32 bit stack base pointer
    mov esp, ebp

    jmp KERNEL_LOCATION


times 510-($-$$) db 0 ; fill up the sector
dw 0xaa55 ; Magic number (BIOS signature)
