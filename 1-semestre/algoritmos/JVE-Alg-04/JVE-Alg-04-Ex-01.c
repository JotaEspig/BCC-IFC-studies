/*
Média aritmética. Escreva um programa Python que calcula a média aritmética de um
conjunto de valores fornecidos pelo usuário. O usuário deve entrar com o valor 0 indicando
que não serão mais fornecidos novos valores. Seu programa deve exibir uma mensagem de
erro se o primeiro valor fornecido pelo usuário for 0.
*/

// compile with "list.c"

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main()
{
    num_list_t *nl = new_num_list();
    float input = 0;
    do
    {
        if (input != 0) num_list_append(nl, input);

        printf("Numero (0 para sair): ");
        scanf("%f", &input);
    } while(input != 0);

    double sum = 0;
    for (size_t i; i < nl->size; i++)
    {
        sum += nl->values[i];
    }
    double average = sum / nl->size;
    printf("media: %.1lf\n", average);

    return 0;
}
