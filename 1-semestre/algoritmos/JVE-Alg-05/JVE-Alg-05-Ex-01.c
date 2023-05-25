/*
Hipotenusa. Escreva uma função que recebe como parâmetros os comprimentos dos dois
lados menores de um triângulo retângulo. A função deve retornar como resultado o
comprimento da hipotenusa, calculado com o Teorema de Pitágoras. Inclua um programa
principal (função main) que solicite ao usuário os comprimentos dos lados, utilize sua função
para calcular a hipotenusa e imprima o resultado.
*/

#include <stdio.h>
#include <math.h>
// gcc -lm ...

double hypotenuse(double a, double b)
{
    double c = sqrt(pow(a, 2) + pow(b, 2));
    return c;
}

int main(void)
{
    double a, b;
    printf("Lado 1: ");
    scanf("%lf", &a);
    printf("Lado 2: ");
    scanf("%lf", &b);

    double c = hypotenuse(a, b);
    printf("Hipotenusa: %lf\n", c);

    return 0;
}
