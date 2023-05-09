/*
Raiz quadrada. Escreva um programa Python que implemente o método de Newton para
calcular e exibir o valor da raiz quadrada de um número. O método de Newton é descrito pelo
pseudo-código abaixo:
Leia o valor de x do usuário
Inicialize raiz = x/2
Enquanto raiz não é boa o suficiente, faça
Atualize raiz para receber a média entre raiz e x/raiz
Quando o algoritmo chega ao fim, raiz contém um valor aproximado da raiz quadrada de x. A
qualidade desta aproximação depende de como você define “boa o suficiente”. Podemos, por
exemplo, considerar a solução boa o suficiente quando o valor absoluto da diferença entre
raiz * raiz e x é menor que .
*/

#include <stdio.h>

#define myabs(x) x < 0 ? -x : x

long double mysqrt(long double number);

int main()
{
    long double number;
    printf("Digite o numero: ");
    scanf("%Lf", &number);
    long double x = mysqrt(number);
    if (x == -1)
    {
        printf("Numero inválido\n");
        return -1;
    }

    printf("%.10Lf\n", x);
    return 0;
}

long double mysqrt(long double number)
{
    if (number < 0)
        return -1;

    long double result = number / 2;
    long double prev_result;
    while (myabs(result * result - number) >= 0.00000000001)
    {
        result = (result + number/result) / 2;
        if (result == prev_result)
            return prev_result;

        prev_result = result;
    }
    
    return result;
}
