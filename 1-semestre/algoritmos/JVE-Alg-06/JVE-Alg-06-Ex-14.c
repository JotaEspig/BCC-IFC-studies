/*
Precedência de operadores. Escreva uma função chamada precedencia que retorna um
inteiro representando a precedência de um operador matemático. Uma string contendo o
operador será passada para a função como seu único parâmetro. Sua função deve retornar 1
para + e -, 2 para * e / e 3 para ^. Se a string passada para a função não for um desses
operadores, a função deve retornar -1. Inclua um programa principal que lê um operador do
usuário e exibe a precedência do operador ou uma mensagem de erro indicando que a
entrada não era um operador.
*/

#include <stdio.h>
#include <string.h>

int precedencia(const char* operador) {
    if (strcmp(operador, "+") == 0 || strcmp(operador, "-") == 0) {
        return 1;
    } else if (strcmp(operador, "*") == 0 || strcmp(operador, "/") == 0) {
        return 2;
    } else if (strcmp(operador, "^") == 0) {
        return 3;
    } else {
        return -1; // Operador desconhecido
    }
}

int main() {
    char operador[10];

    printf("Digite um operador matemático: ");
    scanf("%s", operador);

    int p = precedencia(operador);
    if (p == -1) {
        printf("Erro: '%s' não é um operador válido.\n", operador);
    } else {
        printf("Precedência de '%s': %d\n", operador, p);
    }

    return 0;
}
