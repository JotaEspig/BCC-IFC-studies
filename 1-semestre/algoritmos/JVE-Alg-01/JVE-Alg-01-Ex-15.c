/*
Área de um polígono regular. Um polígono é regular se seus lados são todos do mesmo
tamanho e os ângulos entre lados adjacentes são todos iguais. A área de um polígono regular
pode ser calculada pela fórmula abaixo onde l é o comprimento de um lado e n é o número de
lados:

area = (n * l^2) / (4 * tan(PI/n))

Escreva um programa Python que obtenha do usuário os valores de l e n, e então calcule e
exiba a área do polígono regular correspondente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159265358979323846

char *read_input(int strlength) {
    char *str = (char *) calloc(strlength, sizeof(char));
    if (fgets(str, strlength, stdin) == NULL)
        return NULL;

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';

    return str;
}

int main() {
    printf("Tamanho dos lados (em cm): ");
    double side = atof(read_input(20));
    printf("Quantidade de lados: ");
    double amount = atof(read_input(20));

    double area = (amount * pow(side, 2)) / (4 * tan(PI / amount));
    printf("Area: %.2lfcm\n", area);
    return 0;
}
