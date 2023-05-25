/*
Tarifa do táxi. Em uma determinada cidade, as tarifas de táxi consistem em um valor inicial de
R$ 4,00 mais R$ 0,25 a cada 140 metros percorridos. Escreva uma função que recebe como
seu único parâmetro a distância percorrida em quilômetros, e retorna como seu único
resultado o valor total da corrida. Escreva um programa principal que demonstre o
funcionamento de sua função.
*/

#include <stdio.h>

double taxi(double distance_km)
{
    return 0.25 * (int)(distance_km * 1000 / 140) + 4.0;
}

int main(void)
{
    double distance;
    printf("Distancia em km: ");
    scanf("%lf", &distance);
    double value = taxi(distance);
    printf("Valor: %.2lf\n", value);

    return 0;
}
