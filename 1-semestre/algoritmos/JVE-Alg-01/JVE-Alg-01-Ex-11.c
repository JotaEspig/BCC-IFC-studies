/*
Distância entre dois pontos na terra. A terra é curva (a não ser para os terraplanistas! � ) e
a distância entre graus de longitude (leste-oeste) varia conforme a latitude (norte-sul). Com
isso, encontrar a distância entre dois pontos na superfície da terra é mais complicado do
simplesmente usar o Teorema de Pitágoras no plano. Seja (t1, g1) e (t2, g2) as latitudes e
longitudes de dois pontos na superfície da terra. A distância em quilômetros entre estes dois
pontos ao longo da superfície da terra é dada por:

distancia = 6371.01 * arccos (sen(t1) * sen(t2) + cos(t1) * cos(t2) * cos(g1 - g2))

Crie um programa Python que receba a latitude e a longitude de dois pontos na Terra em
graus, calcule e exiba a distância entre eles em quilômetros ao longo da superfície.
*/

// Compile with: gcc JVE-Alg-1-Ex-11.c -o main -lm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EARTH_RADIUS 6371.01
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
    printf("Latitude ponto 1: ");
    double latitude_point1  = atof(read_input(20)) * (PI / 180);
    printf("Longitude ponto 1: ");
    double longitude_point1 = atof(read_input(20)) * (PI / 180);
    printf("Latitude ponto 2: ");
    double latitude_point2  = atof(read_input(20)) * (PI / 180);
    printf("Longitude ponto 2: ");
    double longitude_point2 = atof(read_input(20)) * (PI / 180);

    double distancia =
        EARTH_RADIUS * acos(sin(latitude_point1) * sin(latitude_point2) +
                            cos(latitude_point1) * cos(latitude_point2) *
                            cos(longitude_point1 - longitude_point2));

    printf("Distancia: %lfkm\n", distancia);
    return 0;
}
