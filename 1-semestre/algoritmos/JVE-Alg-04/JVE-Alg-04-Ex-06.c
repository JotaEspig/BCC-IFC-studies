/*
Bits de paridade. Um bit de paridade é um mecanismo para detecção de erros em dados
transmitidos por uma conexão não confiável, como linha telefônica por exemplo. A idéia básica
é que, a cada grupo de 8 bits, seja acrescentado um bit adicional de forma que erros em bits
individuais possam ser detectados.
Os bit de paridade podem ser computados para paridade par ou paridade ímpar. Se for usada
paridade par, então o bit de paridade a ser transmitido deve ser tal que o número total de bits
“1” transmitidos (8 bits de dados + 1 bit de paridade) é par. Se for utilizada paridade ímpar, o
número total de bits “1” transmitidos deve ser ímpar.
Escreva um programa Python que compute o bit de paridade para grupos de 8 bits fornecidos
pelo usuário utilizando paridade par. Seu programa deve ler strings contendo 8 bits (portanto
as strings vai ser sequencias de 8 caracteres 0 ou 1) até que o usuário entre com uma linha
em branco. Logo após o usuário fornecer cada string, seu programa deve exibir uma
mensagem informando se o bit de paridade deve ser 0 ou 1. O programa também deve exibir
uma mensagem de erro caso o usuário entre com algo que não seja a sequência de 8 bits
*/

#include <stdio.h>
#include <string.h>

int count_char(const char *str, const char ch);

int main(void)
{
    char input[10];
    printf("Digite o byte: ");
    fgets(input, 10, stdin);
    if (*input == '\n')
        return -1;

    input[strlen(input) - 1] = 0; // deletes '\n'
    if (strlen(input) != 8 ||
        count_char(input, '1') + count_char(input, '0') != 8)
    {
        return -1;
    }

    int bit = 0;
    if (count_char(input, '1') % 2 == 1)
        bit = 1;

    printf("Bit de paridade: %d\n", bit);

    return 0;
}

int count_char(const char *str, const char ch)
{
    int counter = 0;
    while (*str != 0)
    {
        if (*str == ch)
            counter++;

        str++;
    }

    return counter;
}
