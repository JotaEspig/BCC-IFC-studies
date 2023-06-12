/*
"Tokenização" de strings. A tokenização é o processo de conversão de uma string em uma
lista de substrings, conhecidas como tokens. Em muitas circunstâncias, uma lista de tokens é
muito mais fácil de trabalhar do que a string original porque a string original pode ter
espaçamento irregular. Em alguns casos, um trabalho substancial também é necessário para
determinar onde termina um token e onde começo o próximo.
Em uma expressão matemática, os tokens são itens como operadores, números e parênteses.
Alguns tokens, como *, /, ^, ( e ) são fáceis de identificar porque o token é um único caractere
e nunca faz parte de outro token. Os símbolos + e - são um pouco mais desafiadores de tratar
porque podem representar o operador de adição ou subtração ou podem ser parte de um
token de número.
Dica: Um sinal de + ou de - é um operador se o caractere (diferente de espaço em branco)
imediatamente anterior fizer parte de um número ou se o caractere (diferente de espaço em
branco) imediatamente antes for um parêntese fechado. Caso contrário, faz parte de um
número.

Escreva uma função que pegue uma string contendo uma expressão matemática como seu
único parâmetro e a divida em uma lista de tokens. Cada token deve ser um parêntese, um
operador ou um número com um sinal opcional de + ou - (para simplificar, trabalharemos
apenas com inteiros neste problema). Retorne a lista de tokens como o resultado da função.
Você pode presumir que a string passada para sua função sempre contém uma expressão
matemática válida consistindo de parênteses, operadores e inteiros. Entretanto, sua função
deve lidar com quantidades variáveis de espaços em branco entre esses elementos. Inclua um
programa principal que demonstra sua função de tokenização lendo uma expressão do
usuário e imprimindo a lista de tokens.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Verifica se um caractere é um operador
bool ehOperador(char caractere) {
    return caractere == '+' || caractere == '-' || caractere == '*' || caractere == '/' || caractere == '^';
}

// Verifica se um caractere é um parêntese
bool ehParentese(char caractere) {
    return caractere == '(' || caractere == ')';
}

// Realiza a tokenização da expressão matemática
char** tokenizacao(const char* expressao, int* quantidadeTokens) {
    int tamanho = strlen(expressao);
    char** tokens = (char**)malloc(sizeof(char*) * tamanho); // Vetor de ponteiros para armazenar os tokens
    int i = 0; // Índice para percorrer a expressão
    int j = 0; // Índice para percorrer cada token
    *quantidadeTokens = 0; // Variável para armazenar a quantidade de tokens encontrados

    // Percorre a expressão
    while (i < tamanho) {
        char caractere = expressao[i];

        // Ignora os espaços em branco
        if (caractere == ' ') {
            i++;
            continue;
        }

        // Verifica se o caractere é um operador
        if (ehOperador(caractere)) {
            tokens[*quantidadeTokens] = (char*)malloc(sizeof(char) * 2);
            tokens[*quantidadeTokens][0] = caractere;
            tokens[*quantidadeTokens][1] = '\0';
            (*quantidadeTokens)++;
            i++;
            continue;
        }

        // Verifica se o caractere é um parêntese
        if (ehParentese(caractere)) {
            tokens[*quantidadeTokens] = (char*)malloc(sizeof(char) * 2);
            tokens[*quantidadeTokens][0] = caractere;
            tokens[*quantidadeTokens][1] = '\0';
            (*quantidadeTokens)++;
            i++;
            continue;
        }

        // Verifica se o caractere é um sinal de número
        if (caractere == '+' || caractere == '-') {
            // Verifica se o caractere anterior é um número ou um parêntese fechado
            if (i == 0 || ehParentese(expressao[i - 1])) {
                tokens[*quantidadeTokens] = (char*)malloc(sizeof(char) * 2);
                tokens[*quantidadeTokens][0] = caractere;
                tokens[*quantidadeTokens][1] = '\0';
                (*quantidadeTokens)++;
                i++;
                continue;
            }
        }

        // Caso contrário, é um número
        j = 0;
        while (i < tamanho && !ehOperador(expressao[i]) && !ehParentese(expressao[i]) && expressao[i] != ' ') {
            tokens[*quantidadeTokens] = (char*)realloc(tokens[*quantidadeTokens], sizeof(char) * (j + 2));
            tokens[*quantidadeTokens][j] = expressao[i];
            i++;
            j++;
        }
        tokens[*quantidadeTokens][j] = '\0';
        (*quantidadeTokens)++;
    }

    return tokens;
}

int main() {
    char expressao[100];
    printf("Digite uma expressao matematica (sem espaços :/): ");
    scanf("%s", expressao);
    int size;
    char **tokens = tokenizacao(expressao, &size);
    for (int i = 0; i < size; i++)
        printf("%s\n", tokens[i]);

    return 0;
}