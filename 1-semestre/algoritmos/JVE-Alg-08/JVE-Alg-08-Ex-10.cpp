/*
Decodificação run-lenght. A codificação run-length é uma técnica simples de compressão de
dados que pode ser eficaz quando valores repetidos ocorrem em posições adjacentes dentro
de uma lista. Compressão é obtida substituindo grupos de valores repetidos por uma cópia do
valor, seguido pelo número de vezes que o valor deve ser repetido. Por exemplo, a lista ["A",
"A", "A", "A", "A", "A", "A", "A", "A", "A", "A", "A", "B", "B", "B", "B",
"A", "A", "A", "A", "A", "A", "B"] seria comprimida como ["A", 12, "B", 4, "A",
6, "B", 1]. A descompressão é realizada replicando cada valor da lista o número de vezes
indicado.
Escreva uma função recursiva que descompacte uma lista codificada run-lenght. Sua função
recursiva deve ter uma lista compactada em run-lenght como seu único parâmetro. Ela deve
retornar a lista descompactada como seu único resultado. Crie um programa principal que
exibe uma lista codificada em run-lenght e o resultado da decodificação.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <string>

typedef std::vector<std::pair<std::string, int>>::iterator vec_pair_iter;

std::string decompact(std::vector<std::pair<std::string, int>> list);

int main()
{
    std::vector<std::pair<std::string, int>> list;
    list.push_back({"A", 12});
    list.push_back({"B", 4});
    list.push_back({"A", 6});
    list.push_back({"B", 1});
    std::string str = decompact(list);
    std::cout << str << std::endl;
    return 0;
}

std::string decompact(vec_pair_iter begin, vec_pair_iter end)
{
    if (begin == end)
        return "";

    std::string str = "";
    for (size_t i = 0; i < begin->second; ++i)
        str += begin->first;

    return str + decompact(begin + 1, end);
}

std::string decompact(std::vector<std::pair<std::string, int>> list)
{
    return decompact(list.begin(), list.end());
}
