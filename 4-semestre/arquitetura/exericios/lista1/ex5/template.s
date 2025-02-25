.code16

.text
.globl _start
_start:
    # 1 (Leitura de teclado e exibir na tela)
    movb $0x0, %ah
    xorb %al, %al
    int $0x16
    movb $0x0e, %ah
    int $0x10
    call new_line

    # 2 (Leitura de string do teclado e exibir na tela)
loop_2:
    movb $0x0, %ah
    xorb %al, %al
    int $0x16
    cmpb $0x1c, %ah
    je loop_2_fim
    movb $0x0e, %ah
    int $0x10
    jmp loop_2
loop_2_fim:
    call new_line

    # 3
    # Não funciona dentro do ambiente bochs pois a interrupção 0x21 é da API do DOS e não é implementada pela BIOS
    movb $1, %ah
    int $0x21

    movb $2, %ah
    int $0x21

    jmp loop_final


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
