/*
Área de um triângulo (novamente). No exercício anterior você criou um programa para
calcular a área de um triângulo dados sua base e sua altura. Entretanto, também é possível
calcular a área de um triângulo se forem conhecidos os comprimentos de seus 3 lados. Seja
l1, l2 e l3 os comprimentos dos três lados.
Seja l = (l1 + l2 + l3) / 2
Então, a área do triângulo pode ser calculada com a seguinte fórmula:

area = sqrt(l * (l - l1) * (l - l2) * (l - l3))

Escreva um programa Python que leia os comprimentos de 3 lados de um triângulo, calcule e
exiba sua área.
*/

// Compile with: gcc JVE-Alg-1-Ex-10.c -o main -lm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char *read_input(int strlength) {
    char *str = (char *) calloc(strlength, sizeof(char));
    if (fgets(str, strlength, stdin) == NULL)
        return NULL;

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    return str;
}

int main() {
    printf("lado 1 (em cm): ");
    double side1 = atof(read_input(20));
    printf("lado 2 (em cm): ");
    double side2 = atof(read_input(20));
    printf("lado 3 (em cm): ");
    double side3 = atof(read_input(20));

    double l = (side1 + side2 + side3) / 2;
    double area = sqrt(l * (l - side1) * (l - side2) * (l - side3));
    printf("Area: %.2lfcm\n", area);
    return 0;
}
