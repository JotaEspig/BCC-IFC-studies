/*
Ordem decrescente. Escreva um programa Python que leia números inteiros (do usuário) e
os armazena em uma lista. Seu programa deve continuar lendo inteiros até que o usuário
entre com o valor 0 (zero). Então, o programa deve exibir em ordem decrescente todos os
números digitados pelo usuário sem incluir o valor 0, com um valor em cada linha impressa.
*/

#include <stdio.h>

#include "list.h"

void sort(num_list_t *nl, int (*func)(double, double));
int reverse_func(double a, double b)
{
    return a > b;
}

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

    sort(nl, &reverse_func);

    printf("Ordered:\n");
    for (int i = 0; i < nl->size; i++)
        printf("%.0lf ", nl->values[i]);
    printf("\n");

    return 0;
}

/*
* Selection sort
*/
void sort(num_list_t *nl, int (*func)(double a, double b))
{
    size_t min_index = 0;
    for (size_t i = 0; i < nl->size; i++)
    {
        for (size_t j = i; j < nl->size; j++)
            if (func(nl->values[j], nl->values[min_index]))
                min_index = j;

        double aux = nl->values[i];
        nl->values[i] = nl->values[min_index];
        nl->values[min_index] = aux;
        min_index = i + 1;
    }
}
