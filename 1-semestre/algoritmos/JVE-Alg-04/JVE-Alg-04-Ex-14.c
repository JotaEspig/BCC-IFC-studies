/*
Binário para decimal. Escreva um programa Python que converte um número binário (base 2) para
decimal (base 10). Seu programa deve iniciar lendo um número binário como uma string. Então, ele
deve computar o número decimal equivalente processando cada dígito do número binário. Finalmente
seu programa deve exibir uma mensagem informando o número decimal calculado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pow(int a, int b)
{
    int x = a;
    for (int i = 1; i < b; i++)
        x *= a;

    return x;
}

int main()
{
    char *input = (char *)calloc(100, sizeof(char));
    printf("Digite binario: ");
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = 0;
    int decimal = 0;
    for (int i = 0; i < strlen(input); i++)
        decimal += (input[i] - 48) * pow(2, strlen(input) - i - 1);

    printf("%d\n", decimal);
    return 0;
}