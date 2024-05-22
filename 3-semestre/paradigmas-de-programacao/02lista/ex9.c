/*
Utilizando recursividade, implemente um algoritmo que receba um número inteiro e
diga quantos dígitos ele tem.
*/

#include <stdio.h>

int digits(int num) {
    if (num <= 0)
        return 0;
    else
        return 1 + digits(num / 10);
}

int main() {
    printf("number of digits in number 42069: %d\n", digits(42069));
    return 0;
}
