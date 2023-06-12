/*
Lista de divisores. Um divisor de um numero inteiro n é um número inteiro positivo menor
que n, tal que divida n em partes inteiras (divisão exata, sem resto). Escreva uma função
Python que calcula todos os divisores de um número inteiro positivo. A função deve retornar
uma lista contendo todos os divisores. Escreva uma função main para demonstrar o
funcionamento da sua solução, a função main deve ler um número do usuário e imprimir todos
os seus divisores.
*/

#include <stdio.h>

#include "list.h"

num_list_t *divisors(int num);

int main(void)
{
    int num;
    scanf("%d", &num);

    num_list_t *nl = divisors(num);
    for (int i = 0; i < nl->size; i++)
        printf("%.0lf ", nl->values[i]);
    printf("\n");

    return 0;
}

num_list_t *divisors(int num)
{
    int num_original = num;
    num_list_t *nl = new_num_list();

    for (int i = 1; i <= num; i++)
    {
        if (num % i == 0)
            num_list_append(nl, i);
    }

    return nl;
}
