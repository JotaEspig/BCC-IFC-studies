/*
Palíndromo. Uma string é considerada um palíndromo se, de trás para frente, ela for idêntica
à string original. Por exemplo: “arara”, “osso”, “radar”. Escreva um programa Python usando
laço de repetição para determinar se uma palavra fornecida pelo usuário é ou não é um
palíndromo. Seu programa deve exibir uma mensagem informando o resultado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *input = (char *)calloc(100, sizeof(char));
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = 0;
    if (*input == 0)
        return -1;

    int len = strlen(input);
    for (int i = 0; i < len / 2; i++)
    {
        if (input[i] != input[len - i - 1])
        {
            printf("Não palindromo\n");
            return 0;
        }
    }
    printf("Palindromo\n");
    return 0;
}
