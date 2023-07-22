/*
Diferença simétrica. Escreva uma função Python que recebe dois conjuntos de números
inteiros M e N e retorna uma lista com sua diferença simétrica em ordem ascendente. O termo
diferença simétrica denota os valores que existem nos conjuntos M ou N, mas não existem em
ambos os conjuntos simultaneamente. Por exemplo, para os conjuntos M = {2, 4, 5, 9} e N =
{2, 4, 11, 12}, a resposta deveria ser [5, 9, 11, 12].
*/

#include <iostream>
#include <vector>

bool is_in(std::vector<int> list, int value);
std::vector<int> diff(std::vector<int> a, std::vector<int> b);

int main()
{
    std::vector<int> a = {2, 4, 5, 9};
    std::vector<int> b = {2, 4, 11, 12};
    std::vector<int> _diff = diff(a, b);
    for (auto e : _diff)
        std::cout << e << " ";
    std::cout << std::endl;
    return 0;
}

bool is_in(std::vector<int> list, int value)
{
    for (auto e : list)
        if (e == value)
            return true;

    return false;
}

std::vector<int> diff(std::vector<int> a, std::vector<int> b)
{
    std::vector<int> _diff;
    for (auto e : a)
        if (!is_in(b, e))
            _diff.push_back(e);

    for (auto e : b)
        if (!is_in(a, e))
            _diff.push_back(e);

    return _diff;
}
