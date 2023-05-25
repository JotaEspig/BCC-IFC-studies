/*
Conversão arbitrária de base numérica. Escreva um programa que permita ao usuário
converter um número de uma base para base 10 e vice-versa. Seu programa deve suportar
bases entre 2 (binário) e 16 (hexadecimal) para o número de entrada e o número de resultado.
Divida seu programa em várias funções, incluindo uma função que converte de uma base
arbitrária em uma base 10, uma função que converte de uma base 10 em uma base arbitrária.
A primeira função deve receber como parâmetros uma string com o número a ser convertido
para base 10, e o valor da base deste número (portanto, de 2 a 16) e deve retornar como
resultado o número convertido na base 10. A segunda função deve receber como parâmetros
um numero na base 10 e a base para qual queremos converter o número. Como resultado, a
função deve retornar uma string com o número convertido. Além disso, faça um programa
principal que lê as bases e o número de entrada do usuário. Você pode encontrar parte da
solução deste problema no exercício anterior e nos exercícios 14 e 15 da lista 4.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// gcc -lm ...

int to_base_10(char *num, int base);
char *base_10_to(int num, int base);

int main(void)
{
    int input_base, output_base;
    char number[50];

    printf("Digite a base de entrada: ");
    scanf("%d", &input_base);

    printf("Digite a base de saida: ");
    scanf("%d", &output_base);

    printf("Digite o número na base %d: ", input_base);
    scanf("%s", number);

    int decimal = to_base_10(number, input_base);
    printf("Decimal: %d\n", decimal);

    char* result = base_10_to(decimal, output_base);
    printf("Numero na base %d: %s\n", output_base, result);

    return 0;
}

int to_base_10(char *num, int base)
{
    size_t len = strlen(num);
    int result = 0;
    for (size_t i = 0; i < len; i++)
        result += atoi((char [2]){num[i], 0}) * pow(base, len - i - 1);
    return result;
}

char *base_10_to(int num, int base)
{
    // I don't want to reallocate memory for the string, so that's it
    char *in_base = (char *)calloc(1000, sizeof(char));

    int quotient, remainder;
    quotient = num;
    int counter = 0;
    while (quotient != 0)
    {
        remainder = quotient % base; 
        quotient = quotient / base;
        in_base[counter] = '0' + remainder;
        counter++;
    }

    char *reversed = (char *)calloc(strlen(in_base) + 1, sizeof(char));
    for (int i = 0; i < strlen(in_base); i++)
        reversed[i] = in_base[strlen(in_base) - i - 1];

    free(in_base);
    return reversed;
}
