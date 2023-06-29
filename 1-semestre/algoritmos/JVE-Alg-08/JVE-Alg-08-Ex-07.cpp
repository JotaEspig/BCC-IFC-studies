/*
Conversão decimal → binário iterativa. Escreva uma função que converte um número
decimal (base 10) em binário (base 2). A função deve receber como parâmetro o número
inteiro decimal (q) e, em seguida, deve realizar a conversão usando o algoritmo de divisão
mostrado abaixo. Quando o algoritmo for concluído, o resultado contém a representação
binária do número, que deve ser retornada pela função como uma string.
*/

#include <iostream>
#include <string>

std::string dec_bin(int q);

int main()
{
    std::cout << dec_bin(5) << std::endl;
    return 0;
}

std::string dec_bin(int q)
{
    std::string result;
    while (q != 0)
    {
        int r = q % 2;
        result = std::to_string(r) + result;
        q = q / 2;
    }

    return result;
}
