%{
/* parser.y — analisador sintático (bison) da linguagem de dashboards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

int yylex(void);
void yyerror(const char *msg);

extern int erros;
extern const char *arquivo_fonte;

Dashboard *raiz = NULL;          /* resultado da análise sintática */
static Dashboard *dash;          /* dashboard em construção */

static void adiciona_fonte(Fonte *f);
static Prop *prop_str(TipoProp t, char *s, int linha);
static Prop *prop_num(TipoProp t, double n, int linha);
%}

%code requires {
#include "ast.h"
}

%locations
%define parse.error verbose

%union {
    double num;
    char *str;
    int inteiro;
    Expr *expr;
    Serie *serie;
    Prop *prop;
    Elem *elem;
    ListaStr *lista;
}

/* palavras reservadas "suaves": também podem ser usadas como nome de coluna */
%token <str> DASHBOARD "dashboard" FONTE "fonte" CSV "csv" JSON "json" TEMA "tema"
%token <str> CLARO "claro" ESCURO "escuro" AUTO "auto" COLUNAS "colunas"
%token <str> GRAFICO "grafico" INDICADOR "indicador" TEXTO "texto" SECAO "secao"
%token <str> LINHA "linha" BARRA "barra" COLUNA "coluna" AREA "area"
%token <str> PIZZA "pizza" ROSCA "rosca" DISPERSAO "dispersao"
%token <str> DADOS "dados" VALOR "valor" FILTRO "filtro" ORDENAR "ordenar" LIMITE "limite"
%token <str> TITULO_X "titulo_x" TITULO_Y "titulo_y" PREFIXO "prefixo" SUFIXO "sufixo"
%token <str> LARGURA "largura" ALTURA "altura" DECIMAIS "decimais"
%token <str> EMPILHADO "empilhado" CORES "cores"
/* palavras reservadas estritas */
%token X "x" Y "y"
%token SOMA "soma" MEDIA "media" MINIMO "minimo" MAXIMO "maximo" CONTAGEM "contagem"
%token COMO "como" ASC "asc" DESC "desc" SIM "sim"
%token E "e" OU "ou" NAO "nao"
%token IGUAL "==" DIFERENTE "!=" MENOR_IGUAL "<=" MAIOR_IGUAL ">="
%token <num> NUM "número"
%token <str> STRING "string" ID "identificador"

%type <inteiro> formato tipo_grafico tema agregacao direcao booleano prop_texto prop_numero
%type <str> coluna palavra
%type <expr> expr
%type <serie> serie serie_base lista_series
%type <prop> propriedades propriedade
%type <elem> elementos elemento
%type <lista> lista_cores

/* precedência: da menor para a maior */
%left OU
%left E
%right NAO
%nonassoc IGUAL DIFERENTE '<' '>' MENOR_IGUAL MAIOR_IGUAL
%left '+' '-'
%left '*' '/'
%right MENOS_UNARIO

%%

programa
    : DASHBOARD STRING              { dash = xmalloc(sizeof *dash);
                                      dash->titulo = $2;
                                      dash->colunas = 2;
                                      dash->tema = TEMA_AUTO; }
      '{' itens '}'                 { raiz = dash; }
    ;

itens
    : %empty
    | itens item
    ;

item
    : configuracao
    | fonte
    | elemento                      { dash->elementos = elem_anexa(dash->elementos, $1); }
    ;

configuracao
    : TEMA ':' tema ';'             { if (dash->tem_tema) {
                                          fprintf(stderr, "%s:%d: erro: 'tema' definido mais de uma vez\n",
                                                  arquivo_fonte, @1.first_line);
                                          erros++;
                                      }
                                      dash->tema = $3; dash->tem_tema = 1; }
    | COLUNAS ':' NUM ';'           { if (dash->tem_colunas) {
                                          fprintf(stderr, "%s:%d: erro: 'colunas' definido mais de uma vez\n",
                                                  arquivo_fonte, @1.first_line);
                                          erros++;
                                      }
                                      if ($3 < 1 || $3 > 6 || $3 != (int)$3) {
                                          fprintf(stderr, "%s:%d: erro: 'colunas' deve ser um inteiro entre 1 e 6\n",
                                                  arquivo_fonte, @3.first_line);
                                          erros++;
                                      } else {
                                          dash->colunas = (int)$3;
                                      }
                                      dash->tem_colunas = 1; }
    ;

tema
    : CLARO                         { $$ = TEMA_CLARO; }
    | ESCURO                        { $$ = TEMA_ESCURO; }
    | AUTO                          { $$ = TEMA_AUTO; }
    ;

fonte
    : FONTE ID '=' formato '(' STRING ')' ';'
                                    { adiciona_fonte(fonte_nova($2, $4, $6, NULL, @1.first_line)); }
    | FONTE ID '=' formato '(' STRING ',' STRING ')' ';'
                                    { adiciona_fonte(fonte_nova($2, $4, $6, $8, @1.first_line)); }
    ;

formato
    : CSV                           { $$ = F_CSV; }
    | JSON                          { $$ = F_JSON; }
    ;

elementos
    : %empty                        { $$ = NULL; }
    | elementos elemento            { $$ = elem_anexa($1, $2); }
    ;

elemento
    : GRAFICO tipo_grafico STRING '{' propriedades '}'
                                    { $$ = elem_novo(EL_GRAFICO, $3, @1.first_line);
                                      $$->grafico = $2;
                                      $$->props = $5; }
    | INDICADOR STRING '{' propriedades '}'
                                    { $$ = elem_novo(EL_INDICADOR, $2, @1.first_line);
                                      $$->props = $4; }
    | TEXTO STRING ';'              { $$ = elem_novo(EL_TEXTO, $2, @1.first_line); }
    | SECAO STRING '{' elementos '}'
                                    { $$ = elem_novo(EL_SECAO, $2, @1.first_line);
                                      $$->filhos = $4; }
    ;

tipo_grafico
    : LINHA                         { $$ = G_LINHA; }
    | BARRA                         { $$ = G_BARRA; }
    | COLUNA                        { $$ = G_COLUNA; }
    | AREA                          { $$ = G_AREA; }
    | PIZZA                         { $$ = G_PIZZA; }
    | ROSCA                         { $$ = G_ROSCA; }
    | DISPERSAO                     { $$ = G_DISPERSAO; }
    ;

propriedades
    : %empty                        { $$ = NULL; }
    | propriedades propriedade      { $$ = prop_anexa($1, $2); }
    ;

propriedade
    : DADOS ':' ID ';'              { $$ = prop_str(P_DADOS, $3, @1.first_line); }
    | X ':' coluna ';'              { $$ = prop_str(P_X, $3, @1.first_line); }
    | Y ':' lista_series ';'        { $$ = prop_nova(P_Y, @1.first_line); $$->series = $3; }
    | VALOR ':' serie ';'           { $$ = prop_nova(P_VALOR, @1.first_line); $$->series = $3; }
    | FILTRO ':' expr ';'           { $$ = prop_nova(P_FILTRO, @1.first_line); $$->expr = $3; }
    | ORDENAR ':' serie_base direcao ';'
                                    { $$ = prop_nova(P_ORDENAR, @1.first_line);
                                      $$->series = $3; $$->desc = $4; }
    | LIMITE ':' NUM ';'            { $$ = prop_num(P_LIMITE, $3, @1.first_line); }
    | prop_texto ':' STRING ';'     { $$ = prop_str($1, $3, @1.first_line); }
    | prop_numero ':' NUM ';'       { $$ = prop_num($1, $3, @1.first_line); }
    | EMPILHADO ':' booleano ';'    { $$ = prop_num(P_EMPILHADO, $3, @1.first_line); }
    | CORES ':' lista_cores ';'     { $$ = prop_nova(P_CORES, @1.first_line); $$->lista = $3; }
    | error ';'                     { $$ = NULL; yyerrok; }
    ;

prop_texto
    : TITULO_X                      { $$ = P_TITULO_X; }
    | TITULO_Y                      { $$ = P_TITULO_Y; }
    | PREFIXO                       { $$ = P_PREFIXO; }
    | SUFIXO                        { $$ = P_SUFIXO; }
    ;

prop_numero
    : LARGURA                       { $$ = P_LARGURA; }
    | ALTURA                        { $$ = P_ALTURA; }
    | DECIMAIS                      { $$ = P_DECIMAIS; }
    ;

booleano
    : SIM                           { $$ = 1; }
    | NAO                           { $$ = 0; }
    ;

lista_cores
    : STRING                        { $$ = lista_anexa(NULL, $1); }
    | lista_cores ',' STRING        { $$ = lista_anexa($1, $3); }
    ;

lista_series
    : serie                         { $$ = $1; }
    | lista_series ',' serie        { $$ = serie_anexa($1, $3); }
    ;

serie
    : serie_base                    { $$ = $1; }
    | serie_base COMO STRING        { $$ = $1; $$->nome = $3; }
    ;

serie_base
    : expr                          { $$ = serie_nova(AG_NENHUMA, $1, @1.first_line); }
    | agregacao '(' expr ')'        { $$ = serie_nova($1, $3, @1.first_line); }
    | CONTAGEM '(' expr ')'         { $$ = serie_nova(AG_CONTAGEM, $3, @1.first_line); }
    | CONTAGEM '(' ')'              { $$ = serie_nova(AG_CONTAGEM, NULL, @1.first_line); }
    ;

agregacao
    : SOMA                          { $$ = AG_SOMA; }
    | MEDIA                         { $$ = AG_MEDIA; }
    | MINIMO                        { $$ = AG_MIN; }
    | MAXIMO                        { $$ = AG_MAX; }
    ;

direcao
    : %empty                        { $$ = 0; }
    | ASC                           { $$ = 0; }
    | DESC                          { $$ = 1; }
    ;

expr
    : expr OU expr                  { $$ = expr_bin(OP_OU, $1, $3, @2.first_line); }
    | expr E expr                   { $$ = expr_bin(OP_E, $1, $3, @2.first_line); }
    | NAO expr                      { $$ = expr_un(OP_NAO, $2, @1.first_line); }
    | expr IGUAL expr               { $$ = expr_bin(OP_IGUAL, $1, $3, @2.first_line); }
    | expr DIFERENTE expr           { $$ = expr_bin(OP_DIF, $1, $3, @2.first_line); }
    | expr '<' expr                 { $$ = expr_bin(OP_MENOR, $1, $3, @2.first_line); }
    | expr MENOR_IGUAL expr         { $$ = expr_bin(OP_MENORIG, $1, $3, @2.first_line); }
    | expr '>' expr                 { $$ = expr_bin(OP_MAIOR, $1, $3, @2.first_line); }
    | expr MAIOR_IGUAL expr         { $$ = expr_bin(OP_MAIORIG, $1, $3, @2.first_line); }
    | expr '+' expr                 { $$ = expr_bin(OP_SOMA, $1, $3, @2.first_line); }
    | expr '-' expr                 { $$ = expr_bin(OP_SUB, $1, $3, @2.first_line); }
    | expr '*' expr                 { $$ = expr_bin(OP_MUL, $1, $3, @2.first_line); }
    | expr '/' expr                 { $$ = expr_bin(OP_DIV, $1, $3, @2.first_line); }
    | '-' expr %prec MENOS_UNARIO   { $$ = expr_un(OP_NEG, $2, @1.first_line); }
    | '(' expr ')'                  { $$ = $2; }
    | NUM                           { $$ = expr_num($1, @1.first_line); }
    | STRING                        { $$ = expr_str($1, @1.first_line); }
    | coluna                        { $$ = expr_col($1, @1.first_line); }
    ;

coluna
    : ID                            { $$ = $1; }
    | X                             { $$ = xstrdup("x"); }
    | Y                             { $$ = xstrdup("y"); }
    | palavra                       { $$ = $1; }
    ;

/* palavras reservadas que também valem como nome de coluna */
palavra
    : DASHBOARD | FONTE | CSV | JSON | TEMA | CLARO | ESCURO | AUTO | COLUNAS
    | GRAFICO | INDICADOR | TEXTO | SECAO
    | LINHA | BARRA | COLUNA | AREA | PIZZA | ROSCA | DISPERSAO
    | DADOS | VALOR | FILTRO | ORDENAR | LIMITE
    | TITULO_X | TITULO_Y | PREFIXO | SUFIXO
    | LARGURA | ALTURA | DECIMAIS | EMPILHADO | CORES
    ;

%%

/* troca todas as ocorrências de `de` por `para` em `s` (buffer de tamanho n) */
static void substitui(char *s, size_t n, const char *de, const char *para)
{
    char tmp[512], *p;
    while ((p = strstr(s, de)) != NULL) {
        snprintf(tmp, sizeof tmp, "%.*s%s%s", (int)(p - s), s, para, p + strlen(de));
        snprintf(s, n, "%s", tmp);
    }
}

void yyerror(const char *msg)
{
    char m[512];
    /* as mensagens do bison vêm em inglês; traduz as partes fixas */
    snprintf(m, sizeof m, "%s", msg);
    substitui(m, sizeof m, "syntax error, ", "");
    substitui(m, sizeof m, "syntax error", "entrada inválida");
    substitui(m, sizeof m, "unexpected", "não esperava");
    substitui(m, sizeof m, "expecting", "esperava");
    substitui(m, sizeof m, " or ", " ou ");
    substitui(m, sizeof m, "end of file", "fim de arquivo");
    fprintf(stderr, "%s:%d:%d: erro sintático: %s\n",
            arquivo_fonte, yylloc.first_line, yylloc.first_column, m);
    erros++;
}

static void adiciona_fonte(Fonte *f)
{
    Fonte *p;
    for (p = dash->fontes; p; p = p->prox) {
        if (strcmp(p->nome, f->nome) == 0) {
            fprintf(stderr, "%s:%d: erro: fonte '%s' já declarada na linha %d\n",
                    arquivo_fonte, f->linha, f->nome, p->linha);
            erros++;
            return;
        }
        if (!p->prox) break;
    }
    if (p) p->prox = f; else dash->fontes = f;
}

static Prop *prop_str(TipoProp t, char *s, int linha)
{
    Prop *p = prop_nova(t, linha);
    p->str = s;
    return p;
}

static Prop *prop_num(TipoProp t, double n, int linha)
{
    Prop *p = prop_nova(t, linha);
    p->num = n;
    return p;
}
