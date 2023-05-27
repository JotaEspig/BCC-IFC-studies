/*
Removendo extremos. Ao analisar os dados coletados como parte de um experimento
científico, pode ser desejável remover os valores mais extremos antes de realizar outros
cálculos. Escreva uma função que tenha uma lista de valores e um número inteiro não
negativo, n, como seus parâmetros. A função deve criar uma nova cópia da lista com os n
maiores elementos e os n menores elementos removidos. Em seguida, ele deve retornar a
nova cópia da lista como o único resultado da função. A ordem dos elementos na lista
retornada não precisa coincidir com a ordem dos elementos na lista original.
Escreva um programa principal que demonstre sua função. Sua função main deve ler uma lista
de números do usuário e remover os dois maiores e os dois menores valores dela. Exiba a
lista com os extremos removidos, seguido pela lista original. Seu programa deve gerar uma
mensagem de erro apropriada se o usuário inserir menos de 4 valores.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

num_list_t *copy_rm_extremes(num_list_t *nl, int n);
void sort(num_list_t *nl);

int main(void)
{
    num_list_t *nl = new_num_list();

    // Fill the list with random values
    srand(time(NULL));
    for (int i = 0; i < 20; i++)
        num_list_append(nl, rand() % 100);

    sort(nl);
    printf("Lista inicial: \n");
    for (int i = 0; i < nl->size; i++)
        printf("%.0lf ", nl->values[i]);
    printf("\n");

    nl = copy_rm_extremes(nl, 2);
    printf("Final: \n");
    for (int i = 0; i < nl->size; i++)
        printf("%.0lf ", nl->values[i]);
    printf("\n");

    return 0;
}

num_list_t *copy_rm_extremes(num_list_t *nl, int n)
{
    num_list_t *new_nl = new_num_list();
    for (size_t i = 0; i < nl->size; i++)
        num_list_append(new_nl, nl->values[i]);

    sort(new_nl);
    for (int i = 0; i < n; i++)
    {
        num_list_pop(new_nl, 0);
        num_list_pop(new_nl, new_nl->size - 1);
    }

    return new_nl;
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
