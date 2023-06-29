/*
Total de valores numéricos. Escreva um programa que leia os valores numéricos do usuário
até que uma linha em branco seja inserida. Exiba a soma total de valores inseridos pelo
usuário (ou 0,0 se o primeiro valor inserido for uma linha em branco). Conclua esta tarefa
usando recursão. Seu programa não pode usar nenhum laço de repetição.
*/

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

void get_values(std::vector<int> &values);

int main(int argc, char *argv[])
{
    std::vector<int> values;
    get_values(values);

    std::cout << std::accumulate(values.begin(), values.end(), 0) << std::endl;
    return 0;
}

void get_values(std::vector<int> &values)
{
    int num;
    std::string str;
    getline(std::cin, str);
    if (str == "")
        return;

    num = stoi(str);
    values.push_back(num);
    return get_values(values);
}
