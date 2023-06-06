/*
Abaixo e acima da média. Escreva um programa que leia números do usuário até que uma
linha em branco seja inserida. Seu programa deve exibir a média de todos os valores inseridos
pelo usuário. Em seguida, o programa deve exibir todos os valores abaixo da média, seguidos
por todos os valores médios (se houver), seguidos por todos os valores acima da média. Uma
mensagem apropriada deve ser exibida antes de cada lista de valores.
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int numeros[100];
    int totalNumeros = 0;
    int soma = 0;
    int i;

    // Lê os números do usuário até uma linha em branco ser inserida
    printf("Insira os números (linha em branco para encerrar):\n");
    while (1) {
        char input[100];
        fgets(input, sizeof(input), stdin);
        if (input[0] == '\n') {
            break;
        }
        numeros[totalNumeros] = atoi(input);
        soma += numeros[totalNumeros];
        totalNumeros++;
    }

    if (totalNumeros == 0) {
        printf("Nenhum número inserido.\n");
        return 0;
    }

    // Calcula a média
    float media = (float)soma / totalNumeros;

    // Exibe os valores abaixo da média
    printf("Valores abaixo da média:\n");
    for (i = 0; i < totalNumeros; i++) {
        if (numeros[i] < media) {
            printf("%d ", numeros[i]);
        }
    }
    printf("\n");

    // Exibe os valores médios
    printf("Valores médios:\n");
    for (i = 0; i < totalNumeros; i++) {
        if (numeros[i] == media) {
            printf("%d ", numeros[i]);
        }
    }
    printf("\n");

    // Exibe os valores acima da média
    printf("Valores acima da média:\n");
    for (i = 0; i < totalNumeros; i++) {
        if (numeros[i] > media) {
            printf("%d ", numeros[i]);
        }
    }
    printf("\n");

    return 0;
}
