/* ast.h — árvore sintática abstrata da linguagem de dashboards */
#ifndef AST_H
#define AST_H

/* ---------- valores em tempo de compilação ---------- */
typedef enum { V_NULO, V_NUM, V_STR } TipoValor;

typedef struct {
    TipoValor tipo;
    double num;
    const char *str;
} Valor;

/* ---------- expressões ---------- */
typedef enum { E_NUM, E_STR, E_COL, E_BIN, E_UN } TipoExpr;

typedef enum {
    OP_SOMA, OP_SUB, OP_MUL, OP_DIV,
    OP_IGUAL, OP_DIF, OP_MENOR, OP_MENORIG, OP_MAIOR, OP_MAIORIG,
    OP_E, OP_OU, OP_NAO, OP_NEG
} Operador;

typedef struct Expr {
    TipoExpr tipo;
    Operador op;          /* E_BIN, E_UN */
    double num;           /* E_NUM */
    char *str;            /* E_STR (literal) ou E_COL (nome da coluna) */
    int col;              /* E_COL: índice resolvido na análise semântica */
    struct Expr *esq, *dir;
    int linha;
} Expr;

/* ---------- séries (expressão com agregação opcional) ---------- */
typedef enum { AG_NENHUMA, AG_SOMA, AG_MEDIA, AG_MIN, AG_MAX, AG_CONTAGEM } Agregacao;

typedef struct Serie {
    Agregacao ag;
    Expr *expr;           /* NULL em contagem() */
    char *nome;           /* rótulo dado por `como "..."`, ou NULL */
    int linha;
    struct Serie *prox;
} Serie;

/* ---------- propriedades ---------- */
typedef enum {
    P_DADOS, P_X, P_Y, P_VALOR, P_FILTRO, P_ORDENAR, P_LIMITE,
    P_TITULO_X, P_TITULO_Y, P_PREFIXO, P_SUFIXO,
    P_LARGURA, P_ALTURA, P_DECIMAIS, P_EMPILHADO, P_CORES,
    P_TOTAL
} TipoProp;

typedef struct ListaStr {
    char *str;
    struct ListaStr *prox;
} ListaStr;

typedef struct Prop {
    TipoProp tipo;
    char *str;            /* dados, x, títulos, prefixo, sufixo */
    double num;           /* limite, largura, altura, decimais, empilhado */
    Expr *expr;           /* filtro */
    Serie *series;        /* y, valor, ordenar */
    int desc;             /* ordenar: 1 = decrescente */
    ListaStr *lista;      /* cores */
    int linha;
    struct Prop *prox;
} Prop;

/* ---------- elementos ---------- */
typedef enum { EL_GRAFICO, EL_INDICADOR, EL_TEXTO, EL_SECAO } TipoElem;

typedef enum {
    G_LINHA, G_BARRA, G_COLUNA, G_AREA, G_PIZZA, G_ROSCA, G_DISPERSAO
} TipoGrafico;

typedef struct Elem {
    TipoElem tipo;
    TipoGrafico grafico;
    char *titulo;         /* título (ou conteúdo, em EL_TEXTO) */
    Prop *props;
    struct Elem *filhos;  /* EL_SECAO */
    struct Config *cfg;   /* preenchido pela análise semântica */
    int linha;
    struct Elem *prox;
} Elem;

/* ---------- fontes de dados ---------- */
typedef enum { F_CSV, F_JSON } Formato;

struct Tabela;

typedef struct Fonte {
    char *nome;
    Formato formato;
    char *caminho;
    char *subcaminho;     /* JSON: caminho "a.b.c" até o array, ou NULL */
    int linha;
    int usada;
    int da_cli;           /* caminho veio da linha de comando (nome=arquivo) */
    struct Tabela *tabela;
    struct Fonte *prox;
} Fonte;

/* ---------- dashboard (raiz) ---------- */
typedef enum { TEMA_AUTO, TEMA_CLARO, TEMA_ESCURO } Tema;

typedef struct {
    char *titulo;
    Tema tema;
    int colunas;
    int tem_tema, tem_colunas;
    Fonte *fontes;
    Elem *elementos;
} Dashboard;

/* ---------- construtores ---------- */
Expr *expr_num(double n, int linha);
Expr *expr_str(char *s, int linha);
Expr *expr_col(char *nome, int linha);
Expr *expr_bin(Operador op, Expr *e, Expr *d, int linha);
Expr *expr_un(Operador op, Expr *e, int linha);

Serie *serie_nova(Agregacao ag, Expr *e, int linha);
Serie *serie_anexa(Serie *lista, Serie *s);

Prop *prop_nova(TipoProp tipo, int linha);
Prop *prop_anexa(Prop *lista, Prop *p);
ListaStr *lista_anexa(ListaStr *lista, char *s);

Elem *elem_novo(TipoElem tipo, char *titulo, int linha);
Elem *elem_anexa(Elem *lista, Elem *e);

Fonte *fonte_nova(char *nome, Formato f, char *caminho, char *sub, int linha);

const char *nome_prop(TipoProp p);
const char *nome_agregacao(Agregacao a);
char *expr_texto(const Expr *e);     /* expressão de volta para texto */
char *serie_texto(const Serie *s);

void *xmalloc(unsigned long n);
char *xstrdup(const char *s);

#endif
