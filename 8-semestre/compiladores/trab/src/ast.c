/* ast.c — construtores e utilitários da AST */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

void *xmalloc(unsigned long n)
{
    void *p = calloc(1, n ? n : 1);
    if (!p) { fprintf(stderr, "erro: memória insuficiente\n"); exit(2); }
    return p;
}

char *xstrdup(const char *s)
{
    char *d = xmalloc(strlen(s) + 1);
    strcpy(d, s);
    return d;
}

Expr *expr_num(double n, int linha)
{
    Expr *e = xmalloc(sizeof *e);
    e->tipo = E_NUM; e->num = n; e->linha = linha;
    return e;
}

Expr *expr_str(char *s, int linha)
{
    Expr *e = xmalloc(sizeof *e);
    e->tipo = E_STR; e->str = s; e->linha = linha;
    return e;
}

Expr *expr_col(char *nome, int linha)
{
    Expr *e = xmalloc(sizeof *e);
    e->tipo = E_COL; e->str = nome; e->col = -1; e->linha = linha;
    return e;
}

Expr *expr_bin(Operador op, Expr *esq, Expr *dir, int linha)
{
    Expr *e = xmalloc(sizeof *e);
    e->tipo = E_BIN; e->op = op; e->esq = esq; e->dir = dir; e->linha = linha;
    return e;
}

Expr *expr_un(Operador op, Expr *esq, int linha)
{
    Expr *e = xmalloc(sizeof *e);
    e->tipo = E_UN; e->op = op; e->esq = esq; e->linha = linha;
    return e;
}

Serie *serie_nova(Agregacao ag, Expr *expr, int linha)
{
    Serie *s = xmalloc(sizeof *s);
    s->ag = ag; s->expr = expr; s->linha = linha;
    return s;
}

Serie *serie_anexa(Serie *lista, Serie *s)
{
    Serie *p = lista;
    if (!lista) return s;
    while (p->prox) p = p->prox;
    p->prox = s;
    return lista;
}

Prop *prop_nova(TipoProp tipo, int linha)
{
    Prop *p = xmalloc(sizeof *p);
    p->tipo = tipo; p->linha = linha;
    return p;
}

Prop *prop_anexa(Prop *lista, Prop *n)
{
    Prop *p = lista;
    if (!n) return lista;
    if (!lista) return n;
    while (p->prox) p = p->prox;
    p->prox = n;
    return lista;
}

ListaStr *lista_anexa(ListaStr *lista, char *s)
{
    ListaStr *n = xmalloc(sizeof *n), *p = lista;
    n->str = s;
    if (!lista) return n;
    while (p->prox) p = p->prox;
    p->prox = n;
    return lista;
}

Elem *elem_novo(TipoElem tipo, char *titulo, int linha)
{
    Elem *e = xmalloc(sizeof *e);
    e->tipo = tipo; e->titulo = titulo; e->linha = linha;
    return e;
}

Elem *elem_anexa(Elem *lista, Elem *n)
{
    Elem *p = lista;
    if (!n) return lista;
    if (!lista) return n;
    while (p->prox) p = p->prox;
    p->prox = n;
    return lista;
}

Fonte *fonte_nova(char *nome, Formato f, char *caminho, char *sub, int linha)
{
    Fonte *x = xmalloc(sizeof *x);
    x->nome = nome; x->formato = f; x->caminho = caminho;
    x->subcaminho = sub; x->linha = linha;
    return x;
}

const char *nome_prop(TipoProp p)
{
    static const char *nomes[P_TOTAL] = {
        "dados", "x", "y", "valor", "filtro", "ordenar", "limite",
        "titulo_x", "titulo_y", "prefixo", "sufixo",
        "largura", "altura", "decimais", "empilhado", "cores"
    };
    return nomes[p];
}

const char *nome_agregacao(Agregacao a)
{
    static const char *nomes[] = { "", "soma", "media", "minimo", "maximo", "contagem" };
    return nomes[a];
}

static const char *simbolo(Operador op)
{
    switch (op) {
    case OP_SOMA: return "+";   case OP_SUB: return "-";
    case OP_MUL: return "*";    case OP_DIV: return "/";
    case OP_IGUAL: return "=="; case OP_DIF: return "!=";
    case OP_MENOR: return "<";  case OP_MENORIG: return "<=";
    case OP_MAIOR: return ">";  case OP_MAIORIG: return ">=";
    case OP_E: return "e";      case OP_OU: return "ou";
    case OP_NAO: return "nao "; case OP_NEG: return "-";
    }
    return "?";
}

char *expr_texto(const Expr *e)
{
    char *r = NULL, *a, *b;
    switch (e->tipo) {
    case E_NUM: asprintf(&r, "%g", e->num); break;
    case E_STR: asprintf(&r, "\"%s\"", e->str); break;
    case E_COL: r = xstrdup(e->str); break;
    case E_UN:
        a = expr_texto(e->esq);
        asprintf(&r, "%s%s", simbolo(e->op), a);
        break;
    case E_BIN:
        a = expr_texto(e->esq);
        b = expr_texto(e->dir);
        asprintf(&r, "%s%s%s %s %s%s%s",
                 e->esq->tipo == E_BIN ? "(" : "", a, e->esq->tipo == E_BIN ? ")" : "",
                 simbolo(e->op),
                 e->dir->tipo == E_BIN ? "(" : "", b, e->dir->tipo == E_BIN ? ")" : "");
        break;
    }
    return r ? r : xstrdup("?");
}

char *serie_texto(const Serie *s)
{
    char *r = NULL, *a;
    if (s->ag == AG_NENHUMA) return expr_texto(s->expr);
    if (!s->expr) return xstrdup("contagem");
    a = expr_texto(s->expr);
    asprintf(&r, "%s(%s)", nome_agregacao(s->ag), a);
    return r ? r : xstrdup("?");
}
