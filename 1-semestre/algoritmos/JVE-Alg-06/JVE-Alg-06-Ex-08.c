/*
Somente palavras. Neste exercício você deve criar uma função em Python que recebe um
texto em uma string e retorna uma lista somente com as palavras, sem espaços ou símbolos
de pontuação. Por exemplo, se a string for: “Beleza! Este é um ótimo exemplo, você
não acha?”, sua função deveria retornar a seguinte lista: [ “Beleza", “Este", “é",
“um", “ótimo", "exemplo", “você", “não", “acha”]. Escreva uma função main
que demonstre o funcionamento da sua solução.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** separarPalavras(const char* texto, int* numPalavras) {
    char** palavras = NULL;
    int tamanhoTexto = strlen(texto);
    int tamanhoPalavra = 0;
    int palavraAtual = 0;
    int i, j;

    // Percorre o texto para contar o número de palavras
    for (i = 0; i < tamanhoTexto; i++) {
        if (isalpha(texto[i])) {
            if (tamanhoPalavra == 0) {
                (*numPalavras)++;
            }
            tamanhoPalavra++;
        } else {
            tamanhoPalavra = 0;
        }
    }

    // Aloca memória para o array de palavras
    palavras = (char**)malloc((*numPalavras) * sizeof(char*));
    if (palavras == NULL) {
        printf("Erro de memória.\n");
        exit(1);
    }

    // Percorre o texto novamente para copiar as palavras para o array
    tamanhoPalavra = 0;
    for (i = 0; i < tamanhoTexto; i++) {
        if (isalpha(texto[i])) {
            if (tamanhoPalavra == 0) {
                // Aloca memória para a palavra atual
                palavras[palavraAtual] = (char*)malloc(tamanhoTexto * sizeof(char));
                if (palavras[palavraAtual] == NULL) {
                    printf("Erro de memória.\n");
                    exit(1);
                }
            }
            palavras[palavraAtual][tamanhoPalavra] = tolower(texto[i]);
            tamanhoPalavra++;
        } else if (tamanhoPalavra > 0) {
            palavras[palavraAtual][tamanhoPalavra] = '\0';
            palavraAtual++;
            tamanhoPalavra = 0;
        }
    }

    return palavras;
}

int main() {
    const char* texto = "Beleza! Este e um otimo exemplo, voce nao acha?";
    int numPalavras = 0;
    char** palavras = separarPalavras(texto, &numPalavras);
    int i;

    printf("Palavras encontradas:\n");
    for (i = 0; i < numPalavras; i++) {
        printf("%s\n", palavras[i]);
    }

    // Libera a memória alocada
    for (i = 0; i < numPalavras; i++) {
        free(palavras[i]);
    }
    free(palavras);

    return 0;
}
