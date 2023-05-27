/*
Ordem Crescente. Escreva um programa Python que leia números inteiros (do usuário) e os
armazena em uma lista. Seu programa deve continuar lendo inteiros até que o usuário entre
com o valor 0 (zero). Então, o programa deve exibir em ordem crescente todos os números
digitados pelo usuário sem incluir o valor 0, com um valor em cada linha impressa. Obs.: você
pode implementar o algoritmo de ordenação BubbleSort ou usar o método sort ou a função
sorted para ordenar a lista.
*/

#include <stdio.h>

#include "list.h"

void sort(num_list_t *nl);

int main(void)
{
    int num = 1;
    num_list_t *nl = new_num_list();
    while (num != 0)
    {
        printf("Digite um numero: ");
        scanf("%d", &num);
        if (num != 0) num_list_append(nl, (double)num);
    }

    printf("unordered\n");
    for (int i = 0; i < nl->size; i++)
        printf("%.0lf ", nl->values[i]);
    printf("\n");

    sort(nl);

    printf("Ordered:\n");
    for (int i = 0; i < nl->size; i++)
        printf("%.0lf ", nl->values[i]);
    printf("\n");

    return 0;
}

void sort(num_list_t *nl)
{
    size_t min_index = 0;
    for (size_t i = 0; i < nl->size; i++)
    {
        for (size_t j = i; j < nl->size; j++)
            if (nl->values[j] < nl->values[min_index])
                min_index = j;

        double aux = nl->values[i];
        nl->values[i] = nl->values[min_index];
        nl->values[min_index] = aux;
        min_index = i + 1;
    }
}
