/*
Palíndromo. Faça uma função Python recursiva que recebe uma string e retorne um valor
lógico indicando se ela é ou não é um palíndromo. OBS: Um palíndromo é uma palavra ou
frase, que é igual quando lida da esquerda para a direita ou da direita para a esquerda
(Espaços em branco e sinais de pontuação devem ser descartados). Exemplo de palíndromo:
"saudavel leva duas”.
*/

#include <iostream>
#include <string>

bool palindromo(std::string str);

int main (int argc, char *argv[])
{
    bool x = palindromo("saudavel leva duas");
    std::cout << x << std::endl;
    return 0;
}

std::string replace_all(std::string str, std::string old_val, std::string new_val)
{
    size_t pos = 0;
    while ((pos = str.find(" ", pos)) != std::string::npos)
        str.replace(pos, 1, "");

    return str;
}

bool palindromo_rec(std::string::iterator first, std::string::iterator last)
{
    if (first > last)
        return true;
    return (*first == *last) && palindromo_rec(++first, --last);
}

bool palindromo(std::string str)
{
    str = replace_all(str, " ", "");
    return palindromo_rec(str.begin(), str.end() - 1);
}
