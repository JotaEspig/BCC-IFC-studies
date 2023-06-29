/*
Fatorial. Implementa uma função recursiva para calcular o fatorial de um número inteiro
positivo. O fatorial é denotado pelo símbolo de exclamação “!” e é definido da seguinte forma:
1! = 1 e n! = n x (n-1)!, para n>1.
*/

#include <iostream>

int fatorial(int n);

int main (int argc, char *argv[])
{
    int num = 5;
    int x = fatorial(num);
    std::cout << x << std::endl;
    return 0;
}

int fatorial(int n)
{
    if (n <= 1)
        return 1;
    return n * fatorial(n - 1);
}
