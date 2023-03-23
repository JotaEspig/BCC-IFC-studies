/*
Soma dos n primeiros números positivos. Escreva um programa Python que receba do
usuário um número inteiro positivo n e então exiba a soma de todos os números inteiros de 1 a
n. Tal soma pode ser computada usando a seguinte fórmula:
soma = ((n)*(n+1))/2
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Argumentos de linha de comando invalidos.\n"
               "use: ./<programa> <n>\n");
        exit(1);
    }

    int n = atoi(argv[1]);
    long unsigned int total = (n * (n + 1)) / 2;
    printf("%d -> %lu\n", n, total);
    return 0;
}
