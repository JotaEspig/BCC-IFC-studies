/*
Cor da casa do tabuleiro. As posições das casas em tabuleiros de xadrez são identificadas
por uma letra e um número. A letra identifica a coluna e o número define a linha, conforme a
figura abaixo:
Escreva um programa Python que receba do usuário um posição. Use um comando if para
determinar se a coluna informada começa com quadrado preto ou branco. Então, use
aritmética de inteiros para determinar a cor do quadrado da linha correspondente. Por
exemplo, se o usuário entrou com o valor a1, então seu programa deve informar que o
quadrado é preto. Se o usuário entrou com o valor d5, então seu programa deve informar que
o quadrado é branco. Seu programa pode assumir que o usuário vai entrar valores válidos,
não sendo necessário verificar eventuais erros de input.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rank, file;
    puts("Digite o coluna (número): ");
    scanf("%d", &rank);
    puts("Digite a fileira: ");
    scanf("%d", &file);

    if (abs(rank - file) % 2 == 0)
    {
        puts("Casa preta");
    }
    if (abs(rank - file) % 2 != 0)
    {   
        puts("Casa branca");
    }
    return 0;
}
