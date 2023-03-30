/*
Centena, dezena, unidade. Dado um número de três algarismos N = CDU (onde C é o
algarismo das centenas, D é o algarismo das dezenas e U o algarismo das unidades) Faça um
programa Python que receba do usuário o número inteiro N, e imprima separadamente a
centena, a dezena e a unidade.
*/

#include <stdio.h>
#include <stdint.h>

int main() {
    uint16_t number;
    printf("Numero: ");
    scanf("%hd", &number);
    uint8_t hundreds = number / 100;
    uint8_t remaining = number % 100;
    uint8_t dozens = remaining / 10;
    remaining %= 10;
    uint8_t units = remaining;

    printf("%d -> C:%d D:%d U:%d\n",
           number, hundreds, dozens, units);
    return 0;
}
