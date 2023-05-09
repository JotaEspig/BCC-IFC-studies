/*
Tabela de conversão de temperaturas. Escreva um programa Python que mostre uma tabela
de conversão de temperaturas em graus Celsius e graus Fahrenheit. A tabela deve incluir em
suas linhas todas as temperaturas entre 0 e 100 graus Celsius que sejam múltiplas de 10
graus Celsius. Inclua os cabeçalhos apropriados e tabulações para suas colunas. Pesquise na
internet sobre a fórmula de conversão de temperaturas Celsius para Fahrenheit.
*/

#include <stdio.h>

#define celsius2fahrenheit(x) (x * 9/5) + 32

int main()
{
    for (int i = 0; i <= 100; i += 10)
        printf("C: %d\t->\tF: %d\n", i, celsius2fahrenheit(i));

    return 0;
}
