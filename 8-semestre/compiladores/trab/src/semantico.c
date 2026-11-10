/* semantico.c — análise semântica e avaliação de expressões */
#define _GNU_SOURCE
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantico.h"

extern int erros;
extern const char *arquivo_fonte;

static Dashboard *dash;
static const char *dir_base;

/* ====================================================================== */
/* diagnósticos                                                           */
/* ====================================================================== */

void erro_em(int linha, const char *fmt, ...)
{
    va_list ap;
    fprintf(stderr, "%s:%d: erro: ", arquivo_fonte, linha);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    erros++;
}

void aviso_em(int linha, const char *fmt, ...)
{
    va_list ap;
    fprintf(stderr, "%s:%d: aviso: ", arquivo_fonte, linha);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
}

/* ====================================================================== */
/* avaliação de expressões                                                */
/* ====================================================================== */

int verdadeiro(Valor v)
{
    if (v.tipo == V_NUM) return v.num != 0;
    if (v.tipo == V_STR) return v.str[0] != '\0';
    return 0;
}

static Valor numero(double n)
{
    Valor v = { V_NUM, 0, NULL };
    v.num = n;
    return v;
}

Valor avalia(const Expr *e, const Valor *linha)
{
    Valor nulo = { V_NULO, 0, NULL }, a, b;
    int cmp;

    switch (e->tipo) {
    case E_NUM: return numero(e->num);
    case E_STR: a.tipo = V_STR; a.num = 0; a.str = e->str; return a;
    case E_COL: return linha[e->col];
    case E_UN:
        a = avalia(e->esq, linha);
        if (e->op == OP_NAO) return numero(!verdadeiro(a));
        return a.tipo == V_NUM ? numero(-a.num) : nulo;
    case E_BIN:
        break;
    }

    a = avalia(e->esq, linha);
    if (e->op == OP_E)  return numero(verdadeiro(a) && verdadeiro(avalia(e->dir, linha)));
    if (e->op == OP_OU) return numero(verdadeiro(a) || verdadeiro(avalia(e->dir, linha)));
    b = avalia(e->dir, linha);

    switch (e->op) {
    case OP_SOMA: case OP_SUB: case OP_MUL: case OP_DIV:
        if (a.tipo != V_NUM || b.tipo != V_NUM) return nulo;
        if (e->op == OP_SOMA) return numero(a.num + b.num);
        if (e->op == OP_SUB)  return numero(a.num - b.num);
        if (e->op == OP_MUL)  return numero(a.num * b.num);
        return b.num == 0 ? nulo : numero(a.num / b.num);
    default:
        break;
    }

    /* comparações: só entre valores do mesmo tipo */
    if (a.tipo != b.tipo || a.tipo == V_NULO)
        return numero(e->op == OP_DIF && a.tipo != b.tipo);
    if (a.tipo == V_NUM) cmp = (a.num > b.num) - (a.num < b.num);
    else cmp = strcmp(a.str, b.str);

    switch (e->op) {
    case OP_IGUAL:   return numero(cmp == 0);
    case OP_DIF:     return numero(cmp != 0);
    case OP_MENOR:   return numero(cmp < 0);
    case OP_MENORIG: return numero(cmp <= 0);
    case OP_MAIOR:   return numero(cmp > 0);
    case OP_MAIORIG: return numero(cmp >= 0);
    default:         return nulo;
    }
}

/* ====================================================================== */
/* fontes de dados                                                        */
/* ====================================================================== */

static Fonte *busca_fonte(const char *nome)
{
    Fonte *f;
    for (f = dash->fontes; f; f = f->prox)
        if (strcmp(f->nome, nome) == 0) return f;
    return NULL;
}

/* Carrega a tabela da fonte na primeira vez em que ela é usada. */
static int carrega_fonte(Fonte *f, int linha)
{
    char msg[512], *caminho = f->caminho;

    if (f->usada) return f->tabela != NULL;
    f->usada = 1;

    if (!f->da_cli && caminho[0] != '/' && dir_base && *dir_base)
        asprintf(&caminho, "%s/%s", dir_base, f->caminho);

    f->tabela = (f->formato == F_CSV)
        ? carrega_csv(caminho, msg, sizeof msg)
        : carrega_json(caminho, f->subcaminho, msg, sizeof msg);

    if (!f->tabela) {
        erro_em(f->da_cli ? linha : f->linha, "fonte '%s': %s", f->nome, msg);
        return 0;
    }
    if (f->tabela->nlin == 0)
        aviso_em(f->linha ? f->linha : linha, "fonte '%s' não tem nenhuma linha de dados", f->nome);
    return 1;
}

static char *lista_colunas(const Tabela *t)
{
    char *buf;
    size_t tam;
    FILE *m = open_memstream(&buf, &tam);
    int i;
    for (i = 0; i < t->ncol; i++)
        fprintf(m, "%s%s", i ? ", " : "", t->colunas[i]);
    fclose(m);
    return buf;
}

static int resolve_coluna(const Fonte *f, const char *nome, int linha)
{
    int i = tabela_coluna(f->tabela, nome);
    if (i < 0)
        erro_em(linha, "coluna '%s' não existe na fonte '%s' (colunas: %s)",
                nome, f->nome, lista_colunas(f->tabela));
    return i;
}

static void resolve_expr(Expr *e, const Fonte *f)
{
    if (!e) return;
    if (e->tipo == E_COL) {
        e->col = resolve_coluna(f, e->str, e->linha);
        if (e->col < 0) e->col = 0;     /* já reportado; evita índice inválido */
    }
    resolve_expr(e->esq, f);
    resolve_expr(e->dir, f);
}

/* ====================================================================== */
/* elementos                                                              */
/* ====================================================================== */

static const char *nome_grafico(TipoGrafico g)
{
    static const char *n[] = { "linha", "barra", "coluna", "area", "pizza", "rosca", "dispersao" };
    return n[g];
}

static int inteiro_entre(const Prop *p, int min, int max)
{
    if (p->num != (int)p->num || p->num < min || p->num > max) {
        erro_em(p->linha, "'%s' deve ser um inteiro entre %d e %d", nome_prop(p->tipo), min, max);
        return 0;
    }
    return 1;
}

static int cor_valida(const char *s)
{
    size_t n = strlen(s), i;
    if (s[0] == '#') {
        if (n != 4 && n != 7) return 0;
        for (i = 1; i < n; i++) if (!isxdigit((unsigned char)s[i])) return 0;
        return 1;
    }
    if (n == 0) return 0;
    for (i = 0; i < n; i++) if (!isalpha((unsigned char)s[i])) return 0;
    return 1;
}

static void analisa_elemento(Elem *el)
{
    static const TipoProp so_grafico[] = {
        P_X, P_Y, P_ORDENAR, P_LIMITE, P_TITULO_X, P_TITULO_Y,
        P_LARGURA, P_ALTURA, P_EMPILHADO, P_CORES
    };
    Prop *vistas[P_TOTAL] = { 0 }, *p;
    Config *c = xmalloc(sizeof *c);
    const char *oque = el->tipo == EL_GRAFICO ? "gráfico" : "indicador";
    int circular = el->tipo == EL_GRAFICO && (el->grafico == G_PIZZA || el->grafico == G_ROSCA);
    Serie *s;
    ListaStr *cor;
    size_t i;

    c->limite = -1;
    c->decimais = -1;
    c->largura = 1;
    c->altura = 320;

    /* propriedades repetidas */
    for (p = el->props; p; p = p->prox) {
        if (vistas[p->tipo])
            erro_em(p->linha, "propriedade '%s' repetida (já definida na linha %d)",
                    nome_prop(p->tipo), vistas[p->tipo]->linha);
        else
            vistas[p->tipo] = p;
    }

    /* propriedades que não se aplicam ao tipo do elemento */
    if (el->tipo == EL_INDICADOR) {
        for (i = 0; i < sizeof so_grafico / sizeof *so_grafico; i++) {
            if ((p = vistas[so_grafico[i]])) {
                erro_em(p->linha, "propriedade '%s' não se aplica a indicador", nome_prop(p->tipo));
                vistas[so_grafico[i]] = NULL;
            }
        }
    } else if ((p = vistas[P_VALOR])) {
        erro_em(p->linha, "propriedade 'valor' só se aplica a indicador (em gráficos use 'y')");
        vistas[P_VALOR] = NULL;
    }

    /* fonte de dados */
    if (!(p = vistas[P_DADOS])) {
        erro_em(el->linha, "%s \"%s\" sem a propriedade obrigatória 'dados'", oque, el->titulo);
        return;
    }
    c->fonte = busca_fonte(p->str);
    if (!c->fonte) {
        erro_em(p->linha, "fonte '%s' não declarada", p->str);
        return;
    }
    if (!carrega_fonte(c->fonte, p->linha)) return;

    /* obrigatórias */
    if (el->tipo == EL_GRAFICO) {
        if (!vistas[P_X])
            erro_em(el->linha, "gráfico \"%s\" sem a propriedade obrigatória 'x'", el->titulo);
        if (!vistas[P_Y])
            erro_em(el->linha, "gráfico \"%s\" sem a propriedade obrigatória 'y'", el->titulo);
        if (!vistas[P_X] || !vistas[P_Y]) return;
    } else if (!vistas[P_VALOR]) {
        erro_em(el->linha, "indicador \"%s\" sem a propriedade obrigatória 'valor'", el->titulo);
        return;
    }

    if ((p = vistas[P_X])) {
        c->x = p->str;
        c->col_x = resolve_coluna(c->fonte, p->str, p->linha);
    }

    if ((p = vistas[P_Y])) {
        int agregadas = 0;
        c->y = p->series;
        for (s = c->y; s; s = s->prox) {
            c->ny++;
            if (s->ag != AG_NENHUMA) agregadas++;
            resolve_expr(s->expr, c->fonte);
        }
        if (agregadas && agregadas != c->ny)
            erro_em(p->linha, "'y' mistura séries agregadas e não agregadas; "
                              "use agregação em todas ou em nenhuma");
        c->agregado = agregadas > 0;
        if (circular && c->ny != 1)
            erro_em(p->linha, "gráfico de %s aceita exatamente uma série em 'y' (recebeu %d)",
                    nome_grafico(el->grafico), c->ny);
    }

    if ((p = vistas[P_VALOR])) {
        c->valor = p->series;
        c->agregado = 1;
        if (c->valor->ag == AG_NENHUMA)
            erro_em(p->linha, "'valor' de indicador exige uma agregação: "
                              "soma, media, minimo, maximo ou contagem");
        resolve_expr(c->valor->expr, c->fonte);
    }

    if ((p = vistas[P_FILTRO])) {
        c->filtro = p->expr;
        resolve_expr(c->filtro, c->fonte);
    }

    if ((p = vistas[P_ORDENAR])) {
        c->ordem = p->series;
        c->desc = p->desc;
        resolve_expr(c->ordem->expr, c->fonte);
        if (c->agregado && c->ordem->ag == AG_NENHUMA &&
            !(c->ordem->expr->tipo == E_COL && c->x && strcmp(c->ordem->expr->str, c->x) == 0))
            erro_em(p->linha, "em gráfico agregado, 'ordenar' aceita apenas a coluna de 'x' "
                              "ou uma agregação, ex.: ordenar: soma(valor) desc;");
        if (!c->agregado && c->ordem->ag != AG_NENHUMA)
            erro_em(p->linha, "'ordenar' usa agregação, mas as séries de 'y' não são agregadas");
    }

    if ((p = vistas[P_LIMITE]) && inteiro_entre(p, 1, 1000000)) c->limite = (int)p->num;
    if ((p = vistas[P_ALTURA]) && inteiro_entre(p, 120, 2000)) c->altura = (int)p->num;
    if ((p = vistas[P_DECIMAIS]) && inteiro_entre(p, 0, 6)) c->decimais = (int)p->num;
    if ((p = vistas[P_LARGURA]) && inteiro_entre(p, 1, 6)) {
        c->largura = (int)p->num;
        if (c->largura > dash->colunas) {
            aviso_em(p->linha, "largura %d maior que o número de colunas do dashboard (%d); "
                               "usando %d", c->largura, dash->colunas, dash->colunas);
            c->largura = dash->colunas;
        }
    }

    if ((p = vistas[P_TITULO_X])) c->titulo_x = p->str;
    if ((p = vistas[P_TITULO_Y])) c->titulo_y = p->str;
    if ((p = vistas[P_PREFIXO])) c->prefixo = p->str;
    if ((p = vistas[P_SUFIXO])) c->sufixo = p->str;
    if (circular && (vistas[P_TITULO_X] || vistas[P_TITULO_Y]))
        aviso_em(el->linha, "títulos de eixo são ignorados em gráfico de %s", nome_grafico(el->grafico));

    if ((p = vistas[P_EMPILHADO])) {
        c->empilhado = (int)p->num;
        if (c->empilhado && el->grafico != G_BARRA && el->grafico != G_COLUNA && el->grafico != G_AREA) {
            aviso_em(p->linha, "'empilhado' só tem efeito em gráficos de barra, coluna e area");
            c->empilhado = 0;
        }
    }

    if ((p = vistas[P_CORES])) {
        c->cores = p->lista;
        for (cor = c->cores; cor; cor = cor->prox)
            if (!cor_valida(cor->str))
                erro_em(p->linha, "cor inválida \"%s\" (use \"#rgb\", \"#rrggbb\" ou um nome CSS)", cor->str);
    }

    el->cfg = c;
}

static void analisa_lista(Elem *lista)
{
    Elem *el;
    for (el = lista; el; el = el->prox) {
        if (el->tipo == EL_SECAO) {
            if (!el->filhos) aviso_em(el->linha, "seção \"%s\" está vazia", el->titulo);
            analisa_lista(el->filhos);
        } else if (el->tipo != EL_TEXTO) {
            analisa_elemento(el);
        }
    }
}

void analisa(Dashboard *d, const char *base)
{
    Fonte *f;
    dash = d;
    dir_base = base;

    if (!d->elementos)
        aviso_em(1, "o dashboard não tem nenhum elemento");
    analisa_lista(d->elementos);

    for (f = d->fontes; f; f = f->prox)
        if (!f->usada)
            aviso_em(f->linha ? f->linha : 1, "fonte '%s' declarada mas não utilizada", f->nome);
}
