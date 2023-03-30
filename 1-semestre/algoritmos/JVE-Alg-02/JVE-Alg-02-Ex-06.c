/*
Soma dos dígitos de um inteiro. Desenvolva um programa que obtenha do usuário um
número inteiro de 4 dígitos e exiba a soma dos dígitos do número. Por exemplo, se o usuário
fornecer o número 3141, então seu programa deve exibir o número 9 (3 + 1 + 4 + 1).
*/

#include <stdio.h>
#include <stdint.h>

int main() {
    uint16_t number;
    printf("Numero: ");
    scanf("%hd", &number);
    uint8_t thousands = number / 1000;
    uint16_t remaining = number % 1000;
    uint8_t hundreds = remaining / 100;
    remaining %= 100;
    uint8_t dozens = remaining / 10;
    remaining %= 10;
    uint8_t units = remaining;
    uint8_t sum = thousands + hundreds + dozens + units;

    printf("%d -> %d (%d + %d + %d + %d)\n",
           number, sum, thousands, hundreds, dozens, units);
    return 0;
}
