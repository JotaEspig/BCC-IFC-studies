/*
Ordenação de 3 inteiros. Crie um programa que obtém 3 números inteiros do usuário e os
exibe de forma ordenada do menor para o maior. Use as funções min e max para encontrar o
menor valor e o maior valor. Dica: o valor do meio pode ser obtido pela soma dos três valores,
subtraída do maior e do menor.
*/

#include <stdio.h>

int main() {
    int int1, int2, int3,
        *max, *min, *mid;
    printf("Primeiro: ");
    scanf("%d", &int1);
    printf("Segundo: ");
    scanf("%d", &int2);
    printf("Terceiro: ");
    scanf("%d", &int3);

    // O código utiliza ponteiros para que seja possível a indentificação
    // de quais números já foram utilizados nas variáveis max e min para que
    // assim não ocorra repetição de um dos números na variável mid
    max = &int1;
    min = &int1;
    if (*max < int2)
        max = &int2;
    if (*max < int3)
        max = &int3;

    if (*min > int2)
        min = &int2;
    if (*min > int3)
        min = &int3;

    // Verifica se o endereço de cada número já foi utilizado, se não
    // ele usa o número como mid
    if (!(min == &int1 || max == &int1))
        mid = &int1;
    if (!(min == &int2 || max == &int2))
        mid = &int2;
    if (!(min == &int3 || max == &int3))
        mid = &int3;
    

    printf("Min: %d, Mid: %d, Max: %d\n", *min, *mid, *max);
    return 0;
}
