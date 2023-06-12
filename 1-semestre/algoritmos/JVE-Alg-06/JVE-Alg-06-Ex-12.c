/*
A lista está ordenada? Escreva uma função que determina se uma lista de valores está ou
não em ordem de classificação (crescente ou decrescente). A função deve receber a lista
como parâmetro e retornar True se a lista já estiver classificada. Caso contrário, ele deve
retornar False. Escreva um programa principal que leia uma lista de números do usuário e use
sua função para relatar se a lista é classificada.
*/

#include <stdio.h>
#include <stdbool.h>

bool estaOrdenada(const int* lista, int tamanho) {
    int i;

    // Verifica se a lista está em ordem crescente
    bool crescente = true;
    for (i = 0; i < tamanho - 1; i++) {
        if (lista[i] > lista[i + 1]) {
            crescente = false;
            break;
        }
    }
    if (crescente) {
        return true;
    }

    // Verifica se a lista está em ordem decrescente
    bool decrescente = true;
    for (i = 0; i < tamanho - 1; i++) {
        if (lista[i] < lista[i + 1]) {
            decrescente = false;
            break;
        }
    }
    if (decrescente) {
        return true;
    }

    return false;
}

int main() {
    int numeros[100];
    int tamanho = 0;
    int i;

    // Lê os números do usuário
    printf("Insira os números (digite 0 para encerrar):\n");
    while (1) {
        int numero;
        scanf("%d", &numero);
        if (numero == 0) {
            break;
        }
        numeros[tamanho] = numero;
        tamanho++;
    }

    // Verifica se a lista está classificada e exibe o resultado
    if (estaOrdenada(numeros, tamanho)) {
        printf("A lista está classificada.\n");
    } else {
        printf("A lista não está classificada.\n");
    }

    return 0;
}
