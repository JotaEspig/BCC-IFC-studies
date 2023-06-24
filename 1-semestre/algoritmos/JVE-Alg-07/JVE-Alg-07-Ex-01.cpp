/*
Caracteres únicos. Escreva uma função Python para verificar se uma string possui
caracteres únicos. Por exemplo, a string “azul" não repete letras, mas a string
“ferramenta"possui letras repetidas. A função deve receber uma string e retornar True no
primeiro caso (letras únicas) ou False caso contrário (letras repetidas). Você deve usar
conjuntos para implementar a função.
*/

#include <iostream>
#include <string>
#include <vector>

bool is_in(std::vector<char> list, char value);
bool check_word(std::string word);

int main()
{
    std::string word;
    std::cout << "Palavra: ";
    std::cin >> word;
    std::cout << (check_word(word) ? "unica" : "nao unica") << std::endl; 

    return 0;
}

bool is_in(std::vector<char> list, char value)
{
    for (auto e : list)
        if (e == value)
            return true;

    return false;
}

bool check_word(std::string word)
{
    std::vector<char> chars_used;
    for (auto e : word)
    {
        if (is_in(chars_used, e))
            return false;

        chars_used.push_back(e);
    }

    return true;
}
