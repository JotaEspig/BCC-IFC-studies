/*
Centena, dezena, unidade (novamente). Dado um número de três algarismos N = CDU
(onde C é o algarismo das centenas, D é o algarismo das dezenas e U o algarismo das
unidades), considere o número M constituído pelos algarismos de N em ordem inversa, isto é,
M=UDC. Faça um programa Python para gerar e imprimir M a partir de N (p.ex.:N=123
->M=321).
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

    uint16_t number_m = units * 100 + dozens * 10 + hundreds;

    printf("N:%d -> C:%d D:%d U:%d -> M: %d\n",
           number, hundreds, dozens, units, number_m);
    return 0;
}
