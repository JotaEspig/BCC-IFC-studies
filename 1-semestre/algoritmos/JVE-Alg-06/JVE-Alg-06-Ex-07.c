/*
Números perfeitos. Um número inteiro positivo n é chamado de número perfeito se a soma
de todos os divisores de n é igual a n. Por exemplo, 28 é um número perfeito porque seus
divisores são 1, 2, 4, 7 e 14; e 1+2+4+7+14=28. Escreva uma função para verificar se um
número é perfeito. A função deve receber somente um número inteiro positivo e retornar True
se ele for perfeito ou False caso contrário. Escreva uma função main para identificar e imprimir
todos os números perfeitos de 1 a 10.000. Obs.: você pode usar o código do exercício anterior
para lhe ajudar nesta tarefa.
*/

#include <stdio.h>

#include "list.h"

num_list_t *divisors(int num);
int is_perfect(int num);

int main(void)
{
    for (int i = 1; i <= 10000; i++)
    {
        if (is_perfect(i))
            printf("%d\n", i);
    }

    return 0;
}

int is_perfect(int num)
{
    num_list_t *nl = divisors(num);
    int sum = 0;
    for (int i = 0; i < nl->size - 1; i++)
        sum += nl->values[i];

    return sum == num;
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
