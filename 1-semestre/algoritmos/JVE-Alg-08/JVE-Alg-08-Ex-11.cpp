/*
Codificação run-lenght. Escreva uma função recursiva que implemente a técnica de
compressão run-lenght descrita no exercício anterior. Sua função deve receber uma lista ou
uma string como seu único parâmetro. Ela deve retornar a lista compactada em run-lenght
como seu único resultado. Inclua um programa principal que leia uma string do usuário, a
compacte e exiba o resultado codificado em run-lenght.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <fstream>

typedef std::vector<std::pair<std::string, int>> vec_pair;
typedef std::vector<std::pair<std::string, int>>::iterator vec_pair_iter;

vec_pair compact(std::string str);

int main()
{
    std::string str, buffer;
    std::ifstream file("test.txt");
    while (std::getline(file, buffer))
    {
        str += buffer;
        str.push_back('\n');
    }

    vec_pair vec = compact(str);
    for (auto e : vec)
    {
         std::cout << e.first << " : " << e.second << std::endl;
    }

    return 0;
}

vec_pair compact(std::string::iterator begin, std::string::iterator end)
{
    vec_pair vec(0);
    if (begin == end)
        return vec;

    int count = 0;
    char original = *begin;
    while (*begin == original && begin != end)
    {
        ++count;
        ++begin;
    }

    vec.push_back({std::to_string(original), count});

    vec_pair from_recursion = compact(begin, end);
    for (auto e : from_recursion)
        vec.push_back(e);

    return vec;
}

vec_pair compact(std::string str)
{
    return compact(str.begin(), str.end());
}
