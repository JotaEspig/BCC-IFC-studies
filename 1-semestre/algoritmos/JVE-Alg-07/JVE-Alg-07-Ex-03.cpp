/*
Busca reversa. Escreva uma função chamada buscaReversa, que encontra todas as chaves
de um dicionário que estão mapeadas para um determinado valor. A função deve receber
como parâmetros um dicionário e um valor para ser buscado no dicionário. A função deve
retornar uma lista (possivelmente vazia) com as chaves encontradas. Escreva uma função
main para demonstrar sua função. Note que a função deve funcionar independentemente de
ela retornar múltiplas chaves, uma única chave, ou nenhuma chave.
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>

struct Dict
{
    std::vector<std::string> keys;
    std::map<std::string, int> map;
};

std::vector<std::string> reverse_search(Dict dict, int num);

int main (int argc, char *argv[])
{
    Dict d;
    d.map = {
        {"teste", 1},
        {"amarelo", 10},
        {"preto", 3},
        {"c++", 10}
    };
    d.keys = {"teste", "amarelo", "preto", "c++"};

    auto found = reverse_search(d, 10);
    for (auto e : found)
        std::cout << e << " ";
    std::cout << std::endl;
    return 0;
}

std::vector<std::string> reverse_search(Dict dict, int num)
{
    std::vector<std::string> found;
    for (auto e : dict.keys)
        if (dict.map[e] == num)
            found.push_back(e);

    return found;
}
