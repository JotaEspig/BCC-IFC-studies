/*
Fibonacci com memorização de resultado. Escreva uma nova versão da sua função
recursiva do exercício 2 (Fibonacci) utilizando a técnica de memorização de resultado para
melhorar desempenho e consumo de memória.
*/

#include <iostream>
#include <unordered_map>

int fib(int num);

int main (int argc, char *argv[])
{
    std::cout << fib(15) << std::endl;
    return 0;
}

int fib_recursive(int num, std::unordered_map<int, int> &already)
{
    if (num == 1 || num == 2)
        return 1;

    auto it = already.find(num);
    if (it != already.end())
        return it->second;

    already[num] =
        fib_recursive(num - 1, already) + fib_recursive(num - 2, already);
    return already[num];
}

int fib(int num)
{
    std::unordered_map<int, int> already;
    return fib_recursive(num, already);
}
