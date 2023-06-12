/*
Infix para posfix. As expressões matemáticas são frequentemente escritas na forma de infixo,
onde os operadores aparecem entre os operandos sobre os quais atuam. Embora seja uma
forma comum, também é possível expressar expressões matemáticas na forma pós-fixada, em
que o operador aparece depois de ambos os operandos. Por exemplo, a expressão infixa
3 + 4 é escrita como 3 4 + na forma pós-fixada.
Use a solução do exercício anterior para tokenizar uma expressão matemática. Em seguida,
use o algoritmo acima para transformar a expressão da forma infixo para a forma pós-fixada.
Seu código que implementa o algoritmo acima deve residir em uma função que recebe uma
lista de tokens que representam uma expressão infixa como seu único parâmetro. Ele deve
retornar uma lista de tokens que representam a expressão pós-fixada equivalente como seu
único resultado. Inclua um programa principal que demonstra sua função infixo para pós-fixada
lendo uma expressão do usuário na forma infixo e exibindo-a na forma pós-fixada.
A finalidade da conversão da forma infixo para a forma pós-fixada ficará evidente quando você
fizer o próximo exercício. Os exercícios 9 da lista 5 e 14 da lista atual podem ser úteis para
concluir este problema.
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

int main() {
    char expressao[100];
    printf("Digite uma expressao matematica na forma infixa: ");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = '\0'; // Remove o caractere de nova linha

    int quantidadeTokens;
    char** tokens = tokenizacao(expressao, &quantidadeTokens);

    int quantidadePosfixo;
    char** posfixo = infixoParaPosfixo(tokens, quantidadeTokens, &quantidadePosfixo);

    printf("Expressao em forma posfixa: ");
    for (int i = 0; i < quantidadePosfixo; i++) {
        printf("%s ", posfixo[i]);
    }
    printf("\n");
    return 0;
}
