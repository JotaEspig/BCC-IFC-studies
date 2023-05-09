/*
Aproximação do valor de . O valor aproximado de pode ser calculado pela série infinita
apresentada abaixo:

Escreva um programa Python que exiba 15 aproximações de . A primeira aproximação deve
ter apenas o primeiro termo da série (ou seja, o valor resultante vai ser somente 3). Cada nova
aproximação de mostrada pelo seu programa deve incluir mais um termo da série, sendo
cada vez uma aproximação mais precisa do que a anterior.
*/

#include <stdio.h>

double pi(int approximation);

int main(void)
{

    for (int i = 1; i <= 15; i++)
        printf("%d - %lf\n", i, pi(i));

    return 0;
}

double pi(int approximation)
{
    int counter = 0;
    double pi_val = 3;
    for (int i = 0; i < approximation * 2; i += 2)
    {
        counter++;
        if (i == 0)
            continue;
        if (counter % 2 == 0)
            pi_val += 4.0 / (i * (i + 1) * (i + 2));
        else
            pi_val -= 4.0 / (i * (i + 1) * (i + 2));
    }

    return pi_val;
}
