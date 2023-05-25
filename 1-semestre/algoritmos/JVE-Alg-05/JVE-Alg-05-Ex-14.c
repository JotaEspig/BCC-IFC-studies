/*
Datas mágicas. Uma “data mágica” é uma data na qual a multiplicação do dia pelo mês é
igual aos dois últimos dígitos do ano. Por exemplo, 10 de junho de 1960 é uma data mágica
porque 10 vezes 6 é igual a 60, que são os dois últimos dígitos do ano. Escreva uma função
que determina se uma data é ou não mágica. A função deve receber 3 parâmetros inteiros
(dia, mês e ano), e retornar um valor lógico. Escreva um programa main que utilize sua função
para determinar e imprimir todas as datas mágicas do século XX. O exercício anterior pode ser
útil para resolver este problema.
*/

#include <stdio.h>

int is_magic_date(int day, int month, int year)
{
    int last_two_digits = year % 100;
    int product = day * month;
    
    return (product == last_two_digits);
}

void print_magic_dates_of_20th_century()
{
    int day, month, year;

    printf("Datas mágicas do século XX:\n");

    for (year = 1900; year <= 1999; year++)
        for (month = 1; month <= 12; month++)
            for (day = 1; day <= 31; day++)
                if (is_magic_date(day, month, year))
                    printf("%02d/%02d/%d\n", day, month, year);
}

int main()
{
    print_magic_dates_of_20th_century();

    return 0;
}
