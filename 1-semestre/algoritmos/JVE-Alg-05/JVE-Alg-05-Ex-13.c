/*
13. Dias em um mês. Escreva uma função que determina quantos dias há em um determinado
mês. Sua função deve receber dois parâmetros: o mês como um número inteiro entre 1 e 12 e
o ano como um número inteiro de quatro dígitos. Certifique-se de que sua função retorne o
número correto de dias em fevereiro para os anos bissextos. Inclua um programa principal que
lê um mês e ano do usuário e exibe o número de dias naquele mês. O exercício 12 da lista 3
pode ajudá-lo a resolver esse problema.
*/

#include <stdio.h>

int get_number_of_days_in_month(int month, int year) {
    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        days_in_month[1] = 29;

    return days_in_month[month - 1];
}

int main() {
    int month, year;

    printf("Mes (1-12): ");
    scanf("%d", &month);

    printf("Ano (4 digitos): ");
    scanf("%d", &year);

    int num_days = get_number_of_days_in_month(month, year);

    printf("%d dias.\n", num_days);

    return 0;
}
