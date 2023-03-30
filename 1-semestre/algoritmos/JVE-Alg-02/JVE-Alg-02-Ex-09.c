/*
Data invertida. Admitindo que uma data é lida pelo algoritmo em uma variável inteira, e não
em uma variável do tipo data, crie um programa Python que leia uma data no formato
DDMMAA e imprima essa data no formato AAMMDD, onde:
• a letra D corresponde a dois algarismos representando o dia;
• a letra M corresponde a dois algarismos representando o mês;
• a letra A corresponde aos dois últimos algarismos representando o ano.
Por exemplo: a data 110618 (11 de junho de 2018), deve ser impressa como 180611
*/

#include <stdio.h>
#include <stdint.h>

int main() {
    uint32_t data;
    printf("Digite a data no formato DDMMAA: ");
    scanf("%d", &data);

    uint8_t year = data / 10000;
    uint32_t remaining_data = data % 10000;
    uint8_t month = remaining_data / 100;
    remaining_data %= 100;
    uint8_t day = remaining_data;
    uint32_t new_data = day * 10000 + month * 100 + year; 

    printf("%d -> %d\n", data, new_data);
    return 0;
}
