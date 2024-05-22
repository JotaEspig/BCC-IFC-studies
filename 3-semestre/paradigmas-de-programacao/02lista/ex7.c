/*
Um número é dito perfeito se a soma dos seus divisores é igual a ele mesmo (ex:
6). Implemente um programa que receba um número e diga se ele é perfeito.
*/

#include <stdio.h>
int is_perfect(int num) {
    int sum = 1;
    for (int i = 2; i < num / 2 + 1; ++i) {
        if (num % i == 0) {
            sum += i;
        }
    }

    return num == sum;
}

int main() {
    for (int i = 0; i < 29; ++i)
        printf("%d - %d\n", i, is_perfect(i));
    return 0;
}
