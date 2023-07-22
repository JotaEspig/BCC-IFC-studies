/*
Sequencia de Fibonacci. A série de Fibonacci é uma sequencia de Fn números inteiros no
qual um termo é definido pela soma dos dois termos anteriores. Os primeiros termos Fi da
sequencia são 0, 1, 1, 2, 3, 5, 8, 13, etc. Portanto, o enésimo termo da sequencia é definido
por , sendo e . Escreva uma função Python recursiva que
recebe como parâmetro um valor inteiro n, e retorna o enésimo termo da sequencia de
Fibonacci.
*/

#include <iostream>

int fib(int num);

int main (int argc, char *argv[])
{
    int x = fib(10);
    std::cout << x << std::endl;
    return 0;
}

int fib(int num)
{
    if (num == 1 || num == 2)
        return 1;
    return fib(num - 1) + fib(num - 2);
}
