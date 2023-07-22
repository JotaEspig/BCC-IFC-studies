/*
Anagramas. Duas palavras são anagramas se contiverem as mesmas letras, mas em ordens
diferentes. Por exemplo: “amor" e “roma" são anagramas porque cada uma delas contém um
"a", um "o", um "m" e um “r”. Crie uma função Python que recebe duas strings e retorna True
se elas forem anagramas, ou False caso contrário.
*/

#include <iostream>
#include <string>

bool anagram(std::string a, std::string b);

int main (int argc, char *argv[])
{
    std::cout << "amor e roma: " << (anagram("amor", "roma") ? "true" : "false")
              << std::endl;
    return 0;
}

bool anagram(std::string a, std::string b)
{
    if (a.size() != b.size())
        return false;

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
