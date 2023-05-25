/*
Mediana de três valores. Escreva uma função que recebe três números como parâmetros e
retorna o valor da mediana desses parâmetros como seu resultado. Inclua um programa
principal que lê três valores do usuário e exibe a mediana destes valores.
*/

#include <stdio.h>

int median(int arr[3])
{
    int copy[3];
    for (size_t i = 0; i < 3; i++)
        copy[i] = arr[i];

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3 - i - 1; j++)
        {
            if (copy[j] > copy[j + 1])
            {
                int aux = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = aux;
            }
        }
    }

    return copy[1];
}

int main(void)
{
    int arr[3] = {3, 2, 4};
    int x = median(arr);
    printf("%d\n", x);

    return 0;
}
