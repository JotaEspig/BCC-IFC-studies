/*
Negativos, zeros e positivos. Escreva um programa Python que leia números inteiros até
que uma linha em branco seja fornecida pelo usuário (se ele digitar somente enter). Depois
que todos os inteiros tiverem sido lidos, seu programa deve mostrar todos os números
negativos, seguidos por todos os zeros e depois todos os números positivos. Dentro de cada
grupo os números devem ser exibidos na ordem em que foram fornecidos pelo usuário. Por
exemplo, se o usuário forneceu os valores 3, -4, 1, 0, -1, 0 e -2, então seu programa deve
exibir os valores -4, -1, -2, 0, 0, 3 e 1, cada um em uma linha.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

int my_pow(int base, int expoent);
num_list_t *organize(num_list_t *nl);

int main(void)
{
    srand(time(NULL));

    num_list_t *nl = new_num_list();
    int size = rand() % 50;
    for (int i = 0; i < size; i++)
        num_list_append(nl, my_pow(-1, rand() % 2) * rand() % 50);

    for (int j = 0; j < nl->size; j++)
        printf("%.0lf ", nl->values[j]);
    printf("\n");

    num_list_t *new_nl = organize(nl);
    for (int j = 0; j < new_nl->size; j++)
        printf("%.0lf ", new_nl->values[j]);
    printf("\n");


    return 0;
}

num_list_t *organize(num_list_t *nl)
{
    num_list_t *negative = new_num_list();
    num_list_t *zereos = new_num_list();
    num_list_t *positive = new_num_list();
    num_list_t *result = new_num_list();

    for (size_t i = 0; i < nl->size; i++)
    {
        if (nl->values[i] < 0)
            num_list_append(negative, nl->values[i]);
        else if (nl->values[i] == 0)
            num_list_append(zereos, nl->values[i]);
        else
            num_list_append(positive, nl->values[i]);
    }

    for (size_t i = 0; i < negative->size; i++)
        num_list_append(result, negative->values[i]);
    for (size_t i = 0; i < zereos->size; i++)
        num_list_append(result, zereos->values[i]);
    for (size_t i = 0; i < positive->size; i++)
        num_list_append(result, positive->values[i]);

    free(negative);
    free(zereos);
    free(positive);
    return result;
}

int my_pow(int base, int expoent)
{
    if (expoent == 0)
        return 1;

    int result = 1;
    for (int i = 0; i < expoent; i++)
        result *= base;

    return result;
}
