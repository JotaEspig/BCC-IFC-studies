/*
Números primos. Um número inteiro positivo é primo se e somente se ele for divisível apenas
por 1 e por ele mesmo. Escreva uma função que recebe um valor inteiro positivo e retorna
True se ele for primo ou False se ele não for. Escreva um programa principal que leia um
número inteiro do usuário e exiba uma mensagem indicando se ele é ou não primo.
*/

#include <stdio.h>

int is_prime(int num)
{
    if (num == 1)
        return 0;

    for (int i = 2; i <= num / 2; i++)
        if (num % i == 0)
            return 0;
    return 1;
}

int main(void)
{
    int num;
    printf("Numero: ");
    scanf("%d", &num);

    is_prime(num) ? printf("Primo\n") : printf("Nao primo\n");

    return 0;
}
