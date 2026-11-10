/* semantico.h — análise semântica: resolve fontes, colunas e propriedades */
#ifndef SEMANTICO_H
#define SEMANTICO_H

#include "ast.h"
#include "dados.h"

/* Propriedades de um gráfico/indicador já validadas e resolvidas. */
typedef struct Config {
    Fonte *fonte;
    char *x;              /* nome da coluna do eixo X / categorias */
    int col_x;
    Serie *y;             /* séries do gráfico */
    int ny;
    Serie *valor;         /* indicador */
    Expr *filtro;
    Serie *ordem;
    int desc;
    int limite;           /* -1 = sem limite */
    char *titulo_x, *titulo_y, *prefixo, *sufixo;
    int largura, altura;
    int decimais;         /* -1 = automático */
    int empilhado;
    ListaStr *cores;
    int agregado;         /* as séries usam funções de agregação */
} Config;

/* Valida o dashboard inteiro; `dir_base` é o diretório do arquivo .dash,
   usado para resolver caminhos relativos das fontes. Os erros são
   contabilizados na variável global `erros`. */
void analisa(Dashboard *d, const char *dir_base);

/* Avalia uma expressão sobre uma linha da tabela. */
Valor avalia(const Expr *e, const Valor *linha);
int verdadeiro(Valor v);

void erro_em(int linha, const char *fmt, ...);
void aviso_em(int linha, const char *fmt, ...);

#endif
