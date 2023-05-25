/*
A string representa um inteiro? Neste exercício, você deve escrever uma função chamada
isInteger que determina se os caracteres em uma string representam ou não um inteiro válido,
retornando um valor lógico como resultado. Ao determinar se uma string representa um inteiro,
você deve ignorar qualquer espaço em branco à esquerda ou à direita. Uma vez que este
espaço em branco é ignorado, uma string representa um inteiro se seu comprimento for pelo
menos 1 e contiver apenas dígitos, ou se seu primeiro caractere for + ou - e o primeiro
caractere é seguido por um ou mais caracteres, todos os quais são dígitos. Escreva um
programa principal que leia uma string do usuário e informe se ela representa ou não um
número inteiro.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int is_integer(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
        if (str[i] < '0' || str[i] > '9')
            return 0;
    return 1;
}

int main(void)
{
    char buff[1000];
    fgets(buff, 1000, stdin);
    buff[strcspn(buff, "\n")] = 0;
    is_integer(buff) ? printf("inteiro\n") : printf("não inteiro\n");;

    return 0;
}
