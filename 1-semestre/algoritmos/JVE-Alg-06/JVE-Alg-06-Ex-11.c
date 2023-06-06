/*
Mega-sena. Para ganhar o prêmio da mega-sena, é necessário acertar todos os 6 números
em seu bilhete com os 6 números entre 1 e 60 sorteados pelo organizador da loteria. Escreva
um programa que gere uma seleção aleatória de 6 números para um bilhete de mega-sena.
Certifique-se de que não haja números repetidos entre os sorteados. Exiba os números em
ordem crescente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int numeros[6];
    int i, j;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Gera os números do bilhete
    for (i = 0; i < 6; i++) {
        int numero;
        do {
            numero = rand() % 60 + 1; // Gera um número aleatório entre 1 e 60
            // Verifica se o número já foi sorteado anteriormente
            for (j = 0; j < i; j++) {
                if (numeros[j] == numero) {
                    numero = 0; // Sinaliza que o número já foi sorteado
                    break;
                }
            }
        } while (numero == 0);
        numeros[i] = numero;
    }

    // Ordena os números em ordem crescente
    for (i = 0; i < 6 - 1; i++) {
        for (j = 0; j < 6 - i - 1; j++) {
            if (numeros[j] > numeros[j + 1]) {
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }

    // Exibe os números sorteados
    printf("Números sorteados (ordem crescente): ");
    for (i = 0; i < 6; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    return 0;
}
