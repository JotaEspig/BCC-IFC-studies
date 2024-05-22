/*
Implemente um algoritmo que receba um CPF na forma XXXXXXXXXXX. Verifique e
informe se a entrada é um CPF válido.
*/

#include <stdio.h>
#include <string.h>

int is_valid_cpf(char *cpf) {
    if (strlen(cpf) != 11) {
        return 0;
    }
    int valid = 0;
    for (int i = 0; i < 1; ++i) {
        if (cpf[i] != cpf[i + 1]) {
            valid = 1;
            break;
        }
    }
    if (!valid) {
        return 0;
    }

    int first_verification_num = cpf[9] - '0';
    int last_verification_num = cpf[10] - '0';

    int sum = 0;
    int peso = 1;
    for (int i = 0; i < 9; ++i) {
        int val = cpf[i] - '0';
        sum += val * peso;
        ++peso;
    }
    int aux = sum % 11;
    if (aux == 10) {
        aux = 0;
    }

    if (first_verification_num != aux) {
        return 0;
    }

    sum = 0;
    peso = 0;
    for (int i = 0; i < 10; ++i) {
        int val = cpf[i] - '0';
        sum += val * peso;
        ++peso;
    }
    aux = sum % 11;
    if (aux == 10) {
        aux = 0;
    }

    if (last_verification_num != aux) {
        return 0;
    }

    return 1;
}

int main() {
    printf("123.456.789-09: %d\n", is_valid_cpf("12345678909"));
    printf("123.456.789-90: %d\n", is_valid_cpf("12345678990"));
    // cpf gerado pelo site: https://www.4devs.com.br/gerador_de_cpf
    printf("614.115.480-86: %d\n", is_valid_cpf("61411548086"));
    printf("000.000.000-00: %d\n", is_valid_cpf("00000000000"));
    printf("111.111.111-11: %d\n", is_valid_cpf("11111111111"));
}
