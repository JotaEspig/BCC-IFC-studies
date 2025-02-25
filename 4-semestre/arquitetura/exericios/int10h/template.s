.code16

.text
.globl _start
_start:
    # Limpa a tela e a pinta de azul
    call clear_screen

    # Move o cursor para a posição no registrador DX
    movb $0x00, %dh # Coordenada X
    movb $0x00, %dl # Coordenada Y
    movb $2, %ah
    movb $0, %bh
    int $0x10

    # Imprime na tela a letra j do meu nome :)
    movb $0x0e, %ah
    movb $'j' , %al
    int  $0x10
    call new_line

    jmp loop_final


clear_screen:
    pusha
    movb $0x06, %ah # Scroll up window
    xorb %al, %al # Clear the screen
    xorw %cx, %cx # Upper left corner
    movw $0x184f, %dx # Lower right corner
    movb $0x1f, %bh # White on Blue
    int $0x10
    popa
    ret


new_line:
    pusha
    # new line
    movb $0x0a, %al
    movb $0x0e, %ah
    int $0x10
    # move cursor to the beginning of the line
    movb $0x0d, %al
    int $0x10
    popa
    ret


loop_final:
    hlt
    jmp loop_final


. = _start + 510

# MBR boot signature
.byte 0x55
.byte 0xaa
