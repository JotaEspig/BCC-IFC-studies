.code16

.text
.globl _start


_start:
    # Limpa a tela e a pinta de azul
    movb $0x06, %ah # Função de scroll up
    xorb %al, %al
    xorw %cx, %cx
    movw $0x184f, %dx # Valores para limpar a tela
    movb $0x4f, %bh # Branco com vermelho
    int $0x10

    # Move o cursor para a posição
    movb $0x0000, %dx # Coordenadas na tela x = 0 e y = 0
    movb $2, %ah
    movb $0, %bh
    int $0x10

    # imprime x (Eder :))
    movb $0x0e, %ah
    movb $'x' , %al
    int  $0x10

    hlt




. = _start + 510

.byte 0x55
.byte 0xaa
