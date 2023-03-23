/*
Área de um triângulo. A área de um triângulo pode ser calculada pela fórmula abaixo, onde b
é o comprimento de sua base e h é o comprimento de sua altura.

area = (b * h) / 2

Escreva um programa Python que permita que o usuário forneça os dados de b e h de um
triângulo, e calcule e exiba o valor de sua área.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_input(int strlength) {
    char *str = (char *) calloc(strlength, sizeof(char));
    if (fgets(str, strlength, stdin) == NULL)
        return NULL;

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    return str;
}

int main() {
    printf("Base (em cm): ");
    double base = atof(read_input(20));
    printf("Altura (em cm): ");
    double height = atof(read_input(20));

    double area = (base * height) / 2;
    printf("Area: %.2lfcm\n", area);
    return 0;
}
