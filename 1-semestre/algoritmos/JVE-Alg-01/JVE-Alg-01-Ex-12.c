/*
Área e volume. Escreva um programa Python que começa lendo o valor de um raio r,
fornecido pelo usuário. O programa deve continuar calculando e exibindo a área de um círculo
de raio r, e o volume de uma esfera de raio r. Utilize a constante pi do módulo math nos seus
cálculos.
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
    printf("Raio da esfera (em cm): ");
    double radius = atof(read_input(20));
    double area = PI * pow(radius, 2);
    double volume = (4 * PI * pow(radius, 3)) / 3;
    printf("Raio: %lf\nVolume: %lf\n", area, volume);
    return 0;
}
