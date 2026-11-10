/* dados.c — leitores de CSV e JSON */
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"

/* ====================================================================== */
/* utilitários                                                            */
/* ====================================================================== */

static char *le_arquivo(const char *caminho, size_t *tam, char *erro, int n)
{
    FILE *f = fopen(caminho, "rb");
    char *buf;
    size_t cap = 1 << 16, len = 0, lidos;

    if (!f) {
        snprintf(erro, n, "não foi possível abrir '%s': %s", caminho, strerror(errno));
        return NULL;
    }
    buf = xmalloc(cap + 1);
    while ((lidos = fread(buf + len, 1, cap - len, f)) > 0) {
        len += lidos;
        if (len == cap) {
            cap *= 2;
            buf = realloc(buf, cap + 1);
            if (!buf) { fprintf(stderr, "erro: memória insuficiente\n"); exit(2); }
        }
    }
    fclose(f);
    buf[len] = '\0';
    *tam = len;
    return buf;
}

int tabela_coluna(const Tabela *t, const char *nome)
{
    int i;
    for (i = 0; i < t->ncol; i++)
        if (strcmp(t->colunas[i], nome) == 0) return i;
    return -1;
}

static void tabela_adiciona_linha(Tabela *t, Valor *linha)
{
    if ((t->nlin & (t->nlin + 1)) == 0) {   /* cresce em potências de 2 */
        t->linhas = realloc(t->linhas, (size_t)(t->nlin + 1) * 2 * sizeof *t->linhas);
        if (!t->linhas) { fprintf(stderr, "erro: memória insuficiente\n"); exit(2); }
    }
    t->linhas[t->nlin++] = linha;
}

static char *apara(char *s)
{
    char *fim;
    while (*s == ' ' || *s == '\t') s++;
    fim = s + strlen(s);
    while (fim > s && (fim[-1] == ' ' || fim[-1] == '\t')) fim--;
    *fim = '\0';
    return s;
}

/* Converte o texto de uma célula CSV em valor: número, texto ou nulo. */
static Valor valor_de_texto(char *s, int virgula_decimal)
{
    Valor v = { V_NULO, 0, NULL };
    char *fim, *p;
    int so_numerico = 1, digitos = 0, virgulas = 0;

    s = apara(s);
    if (!*s) return v;

    for (p = s; *p; p++) {
        if (isdigit((unsigned char)*p)) digitos++;
        else if (*p == ',') virgulas++;
        else if (!strchr("+-.eE", *p)) so_numerico = 0;
    }
    if (so_numerico && digitos > 0) {
        if (virgulas == 0) {
            v.num = strtod(s, &fim);
            if (!*fim && isfinite(v.num)) { v.tipo = V_NUM; return v; }
        } else if (virgulas == 1 && virgula_decimal) {
            /* formato brasileiro: 1.234,56 */
            char *tmp = xmalloc(strlen(s) + 1), *d = tmp;
            for (p = s; *p; p++) {
                if (*p == '.') continue;
                *d++ = (*p == ',') ? '.' : *p;
            }
            *d = '\0';
            v.num = strtod(tmp, &fim);
            if (!*fim && isfinite(v.num)) { free(tmp); v.tipo = V_NUM; return v; }
            free(tmp);
        }
    }
    v.tipo = V_STR;
    v.str = xstrdup(s);
    return v;
}

/* ====================================================================== */
/* CSV                                                                    */
/* ====================================================================== */

typedef struct {
    char **campos;
    int n, cap;
} Registro;

static void registro_add(Registro *r, const char *s, size_t len)
{
    if (r->n == r->cap) {
        r->cap = r->cap ? r->cap * 2 : 16;
        r->campos = realloc(r->campos, (size_t)r->cap * sizeof *r->campos);
        if (!r->campos) { fprintf(stderr, "erro: memória insuficiente\n"); exit(2); }
    }
    r->campos[r->n] = xmalloc(len + 1);
    memcpy(r->campos[r->n], s, len);
    r->campos[r->n][len] = '\0';
    r->n++;
}

static char detecta_separador(const char *p)
{
    int virg = 0, pv = 0, tab = 0, aspas = 0;
    for (; *p && (aspas || *p != '\n'); p++) {
        if (*p == '"') aspas = !aspas;
        else if (!aspas) {
            if (*p == ',') virg++;
            else if (*p == ';') pv++;
            else if (*p == '\t') tab++;
        }
    }
    if (pv > virg && pv >= tab) return ';';
    if (tab > virg && tab > pv) return '\t';
    return ',';
}

/* Lê um registro (linha lógica) a partir de *pp; retorna 0 no fim do arquivo. */
static int le_registro(const char **pp, char sep, Registro *r)
{
    const char *p = *pp;
    char *campo;
    size_t len = 0, cap = 64;

    r->n = 0;
    if (!*p) return 0;
    campo = xmalloc(cap);

    for (;;) {
        len = 0;
        if (*p == '"') {                    /* campo entre aspas */
            p++;
            while (*p) {
                if (*p == '"') {
                    if (p[1] == '"') p++;   /* "" = aspas literal */
                    else { p++; break; }
                }
                if (len + 1 >= cap) { cap *= 2; campo = realloc(campo, cap); }
                campo[len++] = *p++;
            }
            while (*p && *p != sep && *p != '\n') p++;   /* lixo após as aspas */
        } else {
            while (*p && *p != sep && *p != '\n') {
                if (len + 1 >= cap) { cap *= 2; campo = realloc(campo, cap); }
                campo[len++] = *p++;
            }
            if (len > 0 && campo[len - 1] == '\r') len--;
        }
        registro_add(r, campo, len);
        if (*p == sep) { p++; continue; }
        if (*p == '\n') p++;
        break;
    }
    free(campo);
    *pp = p;
    return 1;
}

Tabela *carrega_csv(const char *caminho, char *erro, int n)
{
    size_t tam;
    char *buf = le_arquivo(caminho, &tam, erro, n);
    const char *p;
    char sep;
    Registro r = { NULL, 0, 0 };
    Tabela *t;
    int i;

    if (!buf) return NULL;
    if (strlen(buf) != tam) {
        snprintf(erro, n, "'%s' contém bytes nulos (não é um arquivo de texto)", caminho);
        return NULL;
    }
    p = buf;
    if (strncmp(p, "\xEF\xBB\xBF", 3) == 0) p += 3;     /* BOM UTF-8 */
    sep = detecta_separador(p);

    /* cabeçalho: primeira linha não vazia */
    for (;;) {
        if (!le_registro(&p, sep, &r)) {
            snprintf(erro, n, "'%s' está vazio (sem linha de cabeçalho)", caminho);
            return NULL;
        }
        if (!(r.n == 1 && !*apara(r.campos[0]))) break;
    }
    t = xmalloc(sizeof *t);
    t->ncol = r.n;
    t->colunas = xmalloc((size_t)r.n * sizeof *t->colunas);
    for (i = 0; i < r.n; i++) t->colunas[i] = xstrdup(apara(r.campos[i]));

    while (le_registro(&p, sep, &r)) {
        Valor *linha;
        if (r.n == 1 && !*apara(r.campos[0])) continue;  /* linha em branco */
        linha = xmalloc((size_t)t->ncol * sizeof *linha);
        for (i = 0; i < t->ncol && i < r.n; i++)
            linha[i] = valor_de_texto(r.campos[i], sep != ',');
        for (i = 0; i < r.n; i++) free(r.campos[i]);
        tabela_adiciona_linha(t, linha);
    }
    free(buf);
    return t;
}

/* ====================================================================== */
/* JSON                                                                   */
/* ====================================================================== */

typedef enum { J_NULL, J_BOOL, J_NUM, J_STR, J_ARR, J_OBJ } TipoJson;

typedef struct Json {
    TipoJson tipo;
    double num;              /* J_NUM, J_BOOL */
    char *str;               /* J_STR */
    struct Json **itens;     /* J_ARR, J_OBJ */
    char **chaves;           /* J_OBJ */
    int n;
} Json;

typedef struct {
    const char *ini, *p;
    char *erro;
    int nerro;
    int falhou;
    int prof;
} Leitor;

static Json *json_valor(Leitor *l);

static void json_falha(Leitor *l, const char *fmt, ...)
{
    va_list ap;
    const char *q;
    int linha = 1, k;
    if (l->falhou) return;
    l->falhou = 1;
    for (q = l->ini; q < l->p; q++) if (*q == '\n') linha++;
    k = snprintf(l->erro, l->nerro, "JSON inválido na linha %d: ", linha);
    va_start(ap, fmt);
    if (k >= 0 && k < l->nerro) vsnprintf(l->erro + k, l->nerro - k, fmt, ap);
    va_end(ap);
}

static void json_brancos(Leitor *l)
{
    while (*l->p == ' ' || *l->p == '\t' || *l->p == '\n' || *l->p == '\r') l->p++;
}

static int hex4(const char *p)
{
    int i, v = 0;
    for (i = 0; i < 4; i++) {
        int c = (unsigned char)p[i];
        if (!isxdigit(c)) return -1;
        v = v * 16 + (isdigit(c) ? c - '0' : tolower(c) - 'a' + 10);
    }
    return v;
}

static char *utf8(char *d, unsigned cp)
{
    if (cp < 0x80) *d++ = (char)cp;
    else if (cp < 0x800) {
        *d++ = (char)(0xC0 | (cp >> 6));
        *d++ = (char)(0x80 | (cp & 0x3F));
    } else if (cp < 0x10000) {
        *d++ = (char)(0xE0 | (cp >> 12));
        *d++ = (char)(0x80 | ((cp >> 6) & 0x3F));
        *d++ = (char)(0x80 | (cp & 0x3F));
    } else {
        *d++ = (char)(0xF0 | (cp >> 18));
        *d++ = (char)(0x80 | ((cp >> 12) & 0x3F));
        *d++ = (char)(0x80 | ((cp >> 6) & 0x3F));
        *d++ = (char)(0x80 | (cp & 0x3F));
    }
    return d;
}

static char *json_string(Leitor *l)
{
    const char *q;
    char *r, *d;

    if (*l->p != '"') { json_falha(l, "esperava uma string"); return NULL; }
    l->p++;
    for (q = l->p; *q && *q != '"'; q++)
        if (*q == '\\' && q[1]) q++;
    if (!*q) { json_falha(l, "string não terminada"); return NULL; }

    r = d = xmalloc((size_t)(q - l->p) + 1);   /* escapes nunca aumentam o texto */
    while (l->p < q) {
        if (*l->p != '\\') { *d++ = *l->p++; continue; }
        l->p++;
        switch (*l->p++) {
        case 'n': *d++ = '\n'; break;
        case 't': *d++ = '\t'; break;
        case 'r': *d++ = '\r'; break;
        case 'b': *d++ = '\b'; break;
        case 'f': *d++ = '\f'; break;
        case '/': *d++ = '/'; break;
        case '\\': *d++ = '\\'; break;
        case '"': *d++ = '"'; break;
        case 'u': {
            int cp = (q - l->p >= 4) ? hex4(l->p) : -1, baixo;
            if (cp < 0) { json_falha(l, "escape \\u inválido"); return NULL; }
            l->p += 4;
            if (cp >= 0xD800 && cp <= 0xDBFF && q - l->p >= 6 &&
                l->p[0] == '\\' && l->p[1] == 'u' &&
                (baixo = hex4(l->p + 2)) >= 0xDC00 && baixo <= 0xDFFF) {
                cp = 0x10000 + ((cp - 0xD800) << 10) + (baixo - 0xDC00);
                l->p += 6;
            }
            if (cp == 0 || (cp >= 0xD800 && cp <= 0xDFFF)) cp = 0xFFFD;
            d = utf8(d, (unsigned)cp);
            break;
        }
        default:
            json_falha(l, "sequência de escape inválida");
            return NULL;
        }
    }
    *d = '\0';
    l->p = q + 1;
    return r;
}

static void json_add(Json *j, char *chave, Json *item)
{
    if ((j->n & (j->n + 1)) == 0) {
        size_t cap = (size_t)(j->n + 1) * 2;
        j->itens = realloc(j->itens, cap * sizeof *j->itens);
        if (j->tipo == J_OBJ) j->chaves = realloc(j->chaves, cap * sizeof *j->chaves);
        if (!j->itens || (j->tipo == J_OBJ && !j->chaves)) {
            fprintf(stderr, "erro: memória insuficiente\n");
            exit(2);
        }
    }
    if (j->tipo == J_OBJ) j->chaves[j->n] = chave;
    j->itens[j->n++] = item;
}

static Json *json_valor(Leitor *l)
{
    Json *j = xmalloc(sizeof *j);

    json_brancos(l);
    if (++l->prof > 200) { json_falha(l, "estrutura aninhada demais"); return NULL; }

    if (*l->p == '{' || *l->p == '[') {
        char fecha = (*l->p == '{') ? '}' : ']';
        j->tipo = (*l->p == '{') ? J_OBJ : J_ARR;
        l->p++;
        json_brancos(l);
        if (*l->p == fecha) { l->p++; l->prof--; return j; }
        for (;;) {
            char *chave = NULL;
            Json *item;
            json_brancos(l);
            if (j->tipo == J_OBJ) {
                chave = json_string(l);
                if (!chave) return NULL;
                json_brancos(l);
                if (*l->p != ':') { json_falha(l, "esperava ':'"); return NULL; }
                l->p++;
            }
            item = json_valor(l);
            if (!item) return NULL;
            json_add(j, chave, item);
            json_brancos(l);
            if (*l->p == ',') { l->p++; continue; }
            if (*l->p == fecha) { l->p++; break; }
            json_falha(l, "esperava ',' ou '%c'", fecha);
            return NULL;
        }
    } else if (*l->p == '"') {
        j->tipo = J_STR;
        j->str = json_string(l);
        if (!j->str) return NULL;
    } else if (strncmp(l->p, "true", 4) == 0) {
        j->tipo = J_BOOL; j->num = 1; l->p += 4;
    } else if (strncmp(l->p, "false", 5) == 0) {
        j->tipo = J_BOOL; j->num = 0; l->p += 5;
    } else if (strncmp(l->p, "null", 4) == 0) {
        j->tipo = J_NULL; l->p += 4;
    } else if (*l->p == '-' || isdigit((unsigned char)*l->p)) {
        char *fim;
        j->tipo = J_NUM;
        j->num = strtod(l->p, &fim);
        if (fim == l->p || !isfinite(j->num)) { json_falha(l, "número inválido"); return NULL; }
        l->p = fim;
    } else if (!*l->p) {
        json_falha(l, "fim inesperado do arquivo");
        return NULL;
    } else {
        json_falha(l, "caractere inesperado '%c'", *l->p);
        return NULL;
    }
    l->prof--;
    return j;
}

static Json *json_membro(const Json *obj, const char *chave, size_t len)
{
    int i;
    if (obj->tipo != J_OBJ) return NULL;
    for (i = 0; i < obj->n; i++)
        if (strlen(obj->chaves[i]) == len && strncmp(obj->chaves[i], chave, len) == 0)
            return obj->itens[i];
    return NULL;
}

static int coluna_ou_cria(Tabela *t, const char *nome)
{
    int i = tabela_coluna(t, nome);
    if (i >= 0) return i;
    t->colunas = realloc(t->colunas, (size_t)(t->ncol + 1) * sizeof *t->colunas);
    if (!t->colunas) { fprintf(stderr, "erro: memória insuficiente\n"); exit(2); }
    t->colunas[t->ncol] = xstrdup(nome);
    return t->ncol++;
}

Tabela *carrega_json(const char *caminho, const char *subcaminho, char *erro, int n)
{
    size_t tam;
    char *buf = le_arquivo(caminho, &tam, erro, n);
    Leitor l;
    Json *raiz, *arr;
    Tabela *t;
    int i, k;

    if (!buf) return NULL;
    l.ini = l.p = buf;
    l.erro = erro; l.nerro = n; l.falhou = 0; l.prof = 0;
    if (strncmp(l.p, "\xEF\xBB\xBF", 3) == 0) l.p += 3;

    raiz = json_valor(&l);
    if (raiz) {
        json_brancos(&l);
        if ((size_t)(l.p - buf) != tam) { json_falha(&l, "conteúdo extra após o valor"); raiz = NULL; }
    }
    if (!raiz) return NULL;

    /* localiza o array de registros */
    arr = raiz;
    if (subcaminho && *subcaminho) {
        const char *s = subcaminho;
        while (*s) {
            size_t len = strcspn(s, ".");
            arr = json_membro(arr, s, len);
            if (!arr) {
                snprintf(erro, n, "caminho \"%s\" não encontrado em '%s'", subcaminho, caminho);
                return NULL;
            }
            s += len;
            if (*s == '.') s++;
        }
    } else if (raiz->tipo == J_OBJ) {
        /* objeto na raiz: usa o primeiro membro que seja um array */
        arr = NULL;
        for (i = 0; i < raiz->n && !arr; i++)
            if (raiz->itens[i]->tipo == J_ARR) arr = raiz->itens[i];
    }
    if (!arr || arr->tipo != J_ARR) {
        snprintf(erro, n, "'%s': esperava um array de objetos%s", caminho,
                 subcaminho ? " no caminho indicado" : " (indique o caminho: json(\"arq\", \"a.b\"))");
        return NULL;
    }

    /* 1ª passada: colunas = união das chaves, na ordem em que aparecem */
    t = xmalloc(sizeof *t);
    for (i = 0; i < arr->n; i++) {
        Json *o = arr->itens[i];
        if (o->tipo != J_OBJ) {
            snprintf(erro, n, "'%s': o item %d do array não é um objeto", caminho, i + 1);
            return NULL;
        }
        for (k = 0; k < o->n; k++) coluna_ou_cria(t, o->chaves[k]);
    }
    /* 2ª passada: valores */
    for (i = 0; i < arr->n; i++) {
        Json *o = arr->itens[i];
        Valor *linha = xmalloc((size_t)t->ncol * sizeof *linha);
        for (k = 0; k < o->n; k++) {
            Json *v = o->itens[k];
            Valor *c = &linha[tabela_coluna(t, o->chaves[k])];
            switch (v->tipo) {
            case J_NUM:  c->tipo = V_NUM; c->num = v->num; break;
            case J_STR:  c->tipo = V_STR; c->str = v->str; break;
            case J_BOOL: c->tipo = V_STR; c->str = v->num ? "true" : "false"; break;
            default:     c->tipo = V_NULO; break;   /* null, objetos e arrays aninhados */
            }
        }
        tabela_adiciona_linha(t, linha);
    }
    free(buf);
    return t;
}
