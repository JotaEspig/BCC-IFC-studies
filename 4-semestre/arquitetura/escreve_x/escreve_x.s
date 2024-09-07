# Diz ao montador que o código está em linguagem assembly de 16 bits
.code16 			    
# Diz ao montador que a partir daqui (.text), será o código que será executado
.text 				    
# Só escreve isso aqui antes de começar a escrever o código, n sei pq é necessário
.globl _start

# Isso se chama label
# A label _start define o ponto de entrada do programa :) Acredite
_start:				
    # movb significa move byte
    # move um byte para o registrador al, no caso, o caractere 'x'
    # o $ indica que é um valor literal (um valor, um número, um inteiro, hexadecimal, etc)
    # o ' indica que é um caractere (char em C)
    # o % indica que é um registrador
    # Coisas da sintaxe dessa paradinha
    movb $'x' , %al		# character to print
    # move um byte para o registrador ah, no caso, o valor 0x0e
    # o 0x indica que é um valor hexadecimal
    # estamos movendo o valor 0x0e para o registrador ah pois é o valor que indica
    # que queremos imprimir um caractere na tela (será usado na próxima instrução)
    movb $0x0e, %ah
    # int é uma instrução de interrupção, é uma instrução que faz o processador
    # parar o que está fazendo e executar uma função específica
    # interrupção 0x10 é a interrupção que imprime um caractere na tela
    # (Acredite e utilize para printar UM (apenas UM por vez) caractere na tela)
    int  $0x10		    # bios service (interrupt) 

    # loop final para o programa não terminar
loop_final:
    hlt
    jmp loop_final

# Move a posição atual do código para a posição (começo + 510)
. = _start + 510	    # mov to 510th byte from 0 pos

# Assinatura da BIOS, TOTALMENTE NECESSÁRIO, SIMPLESMENTE ACEITE :)
# MBR boot signature
.byte 0x55		        
.byte 0xaa		        
