/* dados.h — carga das fontes de dados (CSV e JSON) para tabelas em memória */
#ifndef DADOS_H
#define DADOS_H

#include "ast.h"

typedef struct Tabela {
    int ncol;
    char **colunas;      /* nomes das colunas */
    int nlin;
    Valor **linhas;      /* linhas[i][j] */
} Tabela;

/* Retornam NULL em caso de falha, com a mensagem em `erro` (tamanho `n`). */
Tabela *carrega_csv(const char *caminho, char *erro, int n);
Tabela *carrega_json(const char *caminho, const char *subcaminho, char *erro, int n);

int tabela_coluna(const Tabela *t, const char *nome);   /* índice ou -1 */

#endif
