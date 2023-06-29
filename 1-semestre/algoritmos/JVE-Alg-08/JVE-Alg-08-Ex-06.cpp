/*
MDC - Máximo Divisor Comum. Euclides foi um matemático grego que viveu há
aproximadamente 2.300 anos. Seu algoritmo para calcular o MDC - máximo divisor comum de
dois inteiros positivos, a e b, é eficiente e recursivo. Está descrito abaixo:
Escreva um programa que implemente o algoritmo recursivo de Euclides e o use para
determinar o máximo divisor comum de dois inteiros inseridos pelo usuário.
*/

#include <iostream>

int mdc(int a, int b);

int main(int argc, char *argv[])
{
    int num;
    std::cin >> num;
    int num2;
    std::cin >> num2;
    int x = mdc(num, num2);
    std::cout << x << std::endl;
    return 0;
}

int mdc(int a, int b)
{
    if (b == 0)
        return a;

    int c = a % b;
    return mdc(b, c);
}
