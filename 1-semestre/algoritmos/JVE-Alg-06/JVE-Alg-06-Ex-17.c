/*
Avaliação de expressão pós-fixada. Avaliar uma expressão pós-fixada é mais fácil do que
avaliar uma expressão infixa porque ela não contém nenhum colchete e não há regras de
precedência de operador a serem consideradas. Uma expressão pós-fixada pode ser avaliada
usando o seguinte algoritmo:

Escreva um programa que leia uma expressão matemática em forma de infixo do usuário, a
avalie e exiba seu valor. Usa suas soluções dos exercícios 15 e 16 junto com o algoritmo
mostrado acima para resolver este problema.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Verifica se um caractere é um operador
bool ehOperador(char caractere) {
    return caractere == '+' || caractere == '-' || caractere == '*' || caractere == '/' || caractere == '^';
}

// Realiza uma operação matemática com dois operandos e um operador
int realizarOperacao(int a, int b, char operador) {
    switch (operador) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return pow(a, b);
        default:
            return 0;
    }
}

// Verifica se um caractere é um parêntese
bool ehParentese(char caractere) {
    return caractere == '(' || caractere == ')';
}

// Verifica a precedência de um operador
int precedencia(char operador) {
    if (operador == '+' || operador == '-')
        return 1;
    else if (operador == '*' || operador == '/')
        return 2;
    else if (operador == '^')
        return 3;
    else
        return 0;
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

// Converte uma expressão infixa para uma expressão pós-fixada
char** infixoParaPosfixo(char** tokens, int quantidadeTokens, int* quantidadePosfixo) {
    char** posfixo = (char**)malloc(sizeof(char*) * quantidadeTokens);
    char** pilha = (char**)malloc(sizeof(char*) * quantidadeTokens);
    int topo = -1; // Índice do topo da pilha
    *quantidadePosfixo = 0; // Variável para armazenar a quantidade de tokens na expressão pós-fixada

    for (int i = 0; i < quantidadeTokens; i++) {
        char* token = tokens[i];

        // Se o token for um número, adiciona diretamente à expressão pós-fixada
        if (!ehOperador(token[0])) {
            posfixo[*quantidadePosfixo] = token;
            (*quantidadePosfixo)++;
        }
        // Se o token for um operador
        else {
            while (topo >= 0 && ehOperador(pilha[topo][0]) && precedencia(pilha[topo][0]) >= precedencia(token[0])) {
                posfixo[*quantidadePosfixo] = pilha[topo];
                (*quantidadePosfixo)++;
                topo--;
            }
            topo++;
            pilha[topo] = token;
        }
    }

    while (topo >= 0) {
        posfixo[*quantidadePosfixo] = pilha[topo];
        (*quantidadePosfixo)++;
        topo--;
    }

    free(pilha);
    return posfixo;
}

// Avalia uma expressão pós-fixada e retorna o seu valor
int avaliarPosfixo(char** posfixo, int quantidadeTokens) {
    int* pilha = (int*)malloc(sizeof(int) * quantidadeTokens);
    int topo = -1; // Índice do topo da pilha

    for (int i = 0; i < quantidadeTokens; i++) {
        char* token = posfixo[i];

        // Se o token for um número, adiciona à pilha
        if (!ehOperador(token[0])) {
            topo++;
            pilha[topo] = atoi(token);
        }
        // Se o token for um operador, realiza a operação com os operandos no topo da pilha
        else {
            int b = pilha[topo];
            topo--;
            int a = pilha[topo];
            topo--;
            int resultado = realizarOperacao(a, b, token[0]);
            topo++;
            pilha[topo] = resultado;
        }
    }

    int resultado = pilha[topo];
    free(pilha);
    return resultado;
}

int main() {
    char expressao[100];
    printf("Digite uma expressao matematica na forma infixa: ");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = '\0'; // Remove o caractere de nova linha

    int quantidadeTokens;
    char** tokens = tokenizacao(expressao, &quantidadeTokens);

    int quantidadePosfixo;
    char** posfixo = infixoParaPosfixo(tokens, quantidadeTokens, &quantidadePosfixo);

    int resultado = avaliarPosfixo(posfixo, quantidadePosfixo);

    printf("Resultado: %d\n", resultado);

    return 0;
}
