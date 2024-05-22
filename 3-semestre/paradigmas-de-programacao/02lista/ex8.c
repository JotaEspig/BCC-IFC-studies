/*
Utilizando recursividade, implemente um algoritmo que multiplique dois números.
*/

#include <stdio.h>

int mult(int num1, int num2) {
    if (num2 == 0)
        return 0;
    else
        return num1 + mult(num1, num2 - 1);
}

int main() {
    printf("multiplication 5 x 6: %d\n", mult(5, 6));
}
