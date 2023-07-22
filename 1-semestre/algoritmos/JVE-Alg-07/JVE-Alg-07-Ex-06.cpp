/*
Anagramas novamente. A noção de anagramas pode ser estendida para múltiplas palavras.
Por exemplo: "William Shakespeare” e “I am a weakish speller” são anagramas se ignorarmos
se as letras são maiúsculas e também os espaços. Crie uma nova versão da sua função do
exercício anterior para verificar se duas frases são anagramas. Sua função deve
desconsiderar se as letras são maiúsculas ou minúsculas, ignorar espaços e sinais de
pontuação.
*/

#include <iostream>
#include <string>
#include <algorithm>

bool anagram(std::string a, std::string b);

int main (int argc, char *argv[])
{
    std::cout << (anagram("William Shakespeare", "I am a weakish speller") ? "true" : "false")
              << std::endl;
    return 0;
}

bool anagram(std::string a, std::string b)
{
    for (auto it = a.begin(); it != a.end(); ++it)
        *it = std::toupper(*it);
    for (auto it = b.begin(); it != b.end(); ++it)
        *it = std::toupper(*it);

    for (auto ch1 : a)
    {
        bool found = false;
        for (auto ch2 : b)
        {
            if (ch1 == ch2)
            {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }

    return true;
}
