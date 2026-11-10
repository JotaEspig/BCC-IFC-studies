%{
/* lexer.l — analisador léxico (flex) da linguagem de dashboards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.tab.h"

extern int erros;
extern const char *arquivo_fonte;

static int coluna_atual = 1;

/* mantém yylloc atualizado (linha/coluna) para as mensagens de erro */
#define YY_USER_ACTION                                         \
    yylloc.first_line = yylloc.last_line = yylineno;           \
    yylloc.first_column = coluna_atual;                        \
    {                                                          \
        int i;                                                 \
        for (i = 0; i < yyleng; i++) {                         \
            if (yytext[i] == '\n') coluna_atual = 1;           \
            else if ((yytext[i] & 0xC0) != 0x80) coluna_atual++; \
        }                                                      \
    }                                                          \
    yylloc.last_column = coluna_atual - 1;

static char *texto_string(const char *s, int n);

/* palavras reservadas "suaves": guardam o próprio texto, pois a gramática
   também as aceita como nome de coluna (ex.: uma coluna chamada `valor`) */
#define PALAVRA(tok) do { yylval.str = xstrdup(yytext); return tok; } while (0)
%}

%option noyywrap nounput noinput yylineno

LETRA   [A-Za-z_\x80-\xff]
DIGITO  [0-9]

%x COMENTARIO

%%

[ \t\r\n]+              { /* espaços em branco */ }
"#"[^\n]*               { /* comentário de linha */ }
"//"[^\n]*              { /* comentário de linha */ }
"/*"                    { BEGIN(COMENTARIO); }
<COMENTARIO>"*/"        { BEGIN(INITIAL); }
<COMENTARIO>.|\n        { }
<COMENTARIO><<EOF>>     {
                          fprintf(stderr, "%s:%d: erro léxico: comentário não terminado\n",
                                  arquivo_fonte, yylineno);
                          erros++;
                          BEGIN(INITIAL);
                          return 0;
                        }

"dashboard"             { PALAVRA(DASHBOARD); }
"fonte"                 { PALAVRA(FONTE); }
"csv"                   { PALAVRA(CSV); }
"json"                  { PALAVRA(JSON); }
"tema"                  { PALAVRA(TEMA); }
"claro"                 { PALAVRA(CLARO); }
"escuro"                { PALAVRA(ESCURO); }
"auto"                  { PALAVRA(AUTO); }
"colunas"               { PALAVRA(COLUNAS); }

"grafico"|"gráfico"     { PALAVRA(GRAFICO); }
"indicador"             { PALAVRA(INDICADOR); }
"texto"                 { PALAVRA(TEXTO); }
"secao"|"seção"         { PALAVRA(SECAO); }

"linha"                 { PALAVRA(LINHA); }
"barra"                 { PALAVRA(BARRA); }
"coluna"                { PALAVRA(COLUNA); }
"area"|"área"           { PALAVRA(AREA); }
"pizza"                 { PALAVRA(PIZZA); }
"rosca"                 { PALAVRA(ROSCA); }
"dispersao"|"dispersão" { PALAVRA(DISPERSAO); }

"dados"                 { PALAVRA(DADOS); }
"x"                     { return X; }
"y"                     { return Y; }
"valor"                 { PALAVRA(VALOR); }
"filtro"                { PALAVRA(FILTRO); }
"ordenar"               { PALAVRA(ORDENAR); }
"limite"                { PALAVRA(LIMITE); }
"titulo_x"              { PALAVRA(TITULO_X); }
"titulo_y"              { PALAVRA(TITULO_Y); }
"prefixo"               { PALAVRA(PREFIXO); }
"sufixo"                { PALAVRA(SUFIXO); }
"largura"               { PALAVRA(LARGURA); }
"altura"                { PALAVRA(ALTURA); }
"decimais"              { PALAVRA(DECIMAIS); }
"empilhado"             { PALAVRA(EMPILHADO); }
"cores"                 { PALAVRA(CORES); }

"soma"                  { return SOMA; }
"media"|"média"         { return MEDIA; }
"minimo"|"mínimo"       { return MINIMO; }
"maximo"|"máximo"       { return MAXIMO; }
"contagem"              { return CONTAGEM; }
"como"                  { return COMO; }
"asc"                   { return ASC; }
"desc"                  { return DESC; }
"sim"                   { return SIM; }

"e"|"&&"                { return E; }
"ou"|"||"               { return OU; }
"nao"|"não"|"!"         { return NAO; }

"=="                    { return IGUAL; }
"!="                    { return DIFERENTE; }
"<="                    { return MENOR_IGUAL; }
">="                    { return MAIOR_IGUAL; }
"<"                     { return '<'; }
">"                     { return '>'; }
[-+*/(){}:;,=]          { return yytext[0]; }

{DIGITO}+("."{DIGITO}+)? {
                          yylval.num = strtod(yytext, NULL);
                          return NUM;
                        }

\"([^"\\\n]|\\.)*\"     {
                          yylval.str = texto_string(yytext + 1, yyleng - 2);
                          return STRING;
                        }
\"([^"\\\n]|\\.)*       {
                          fprintf(stderr, "%s:%d:%d: erro léxico: string não terminada\n",
                                  arquivo_fonte, yylloc.first_line, yylloc.first_column);
                          erros++;
                          yylval.str = texto_string(yytext + 1, yyleng - 1);
                          return STRING;
                        }

{LETRA}({LETRA}|{DIGITO})* {
                          yylval.str = xstrdup(yytext);
                          return ID;
                        }

"["[^\]\n]+"]"          {
                          /* identificador entre colchetes: permite espaços,
                             acentos e palavras reservadas como nome de coluna */
                          yylval.str = xstrdup(yytext + 1);
                          yylval.str[yyleng - 2] = '\0';
                          return ID;
                        }

.                       {
                          fprintf(stderr, "%s:%d:%d: erro léxico: caractere inesperado '%s'\n",
                                  arquivo_fonte, yylloc.first_line, yylloc.first_column, yytext);
                          erros++;
                        }

%%

/* copia o conteúdo de uma string resolvendo as sequências de escape */
static char *texto_string(const char *s, int n)
{
    char *r = xmalloc(n + 1), *d = r;
    int i;
    for (i = 0; i < n; i++) {
        if (s[i] == '\\' && i + 1 < n) {
            i++;
            switch (s[i]) {
            case 'n': *d++ = '\n'; break;
            case 't': *d++ = '\t'; break;
            default:  *d++ = s[i]; break;
            }
        } else {
            *d++ = s[i];
        }
    }
    *d = '\0';
    return r;
}
