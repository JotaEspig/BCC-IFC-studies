/* gerador.c — geração de código: produz o HTML com os gráficos Highcharts */
#define _GNU_SOURCE
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerador.h"
#include "semantico.h"

#define HIGHCHARTS_URL "https://cdn.jsdelivr.net/npm/highcharts@11.4.8"

static Dashboard *dash;
static FILE *html;       /* saída principal */
static FILE *js;         /* buffer com as chamadas Highcharts.chart(...) */
static int prox_id = 1;

/* ====================================================================== */
/* escrita com escape                                                     */
/* ====================================================================== */

static void html_esc(FILE *f, const char *s)
{
    for (; *s; s++) {
        switch (*s) {
        case '&': fputs("&amp;", f); break;
        case '<': fputs("&lt;", f); break;
        case '>': fputs("&gt;", f); break;
        case '"': fputs("&quot;", f); break;
        case '\n': fputs("<br>", f); break;
        default: fputc(*s, f);
        }
    }
}

/* String JavaScript; '<', '>' e '&' viram \uXXXX para não fechar o <script>. */
static void js_str(FILE *f, const char *s)
{
    fputc('"', f);
    for (; *s; s++) {
        unsigned char c = (unsigned char)*s;
        if (c == '"' || c == '\\') { fputc('\\', f); fputc(c, f); }
        else if (c < 0x20 || c == '<' || c == '>' || c == '&') fprintf(f, "\\u%04x", c);
        else fputc(c, f);
    }
    fputc('"', f);
}

static void js_num(FILE *f, Valor v)
{
    if (v.tipo == V_NUM && isfinite(v.num)) fprintf(f, "%.12g", v.num);
    else fputs("null", f);
}

/* Formata um número no padrão brasileiro: 1.234.567,89 */
static void formata_br(FILE *f, double v, int decimais)
{
    char buf[64], *ponto;
    int inteiros, i;

    if (decimais < 0) decimais = (fabs(v - round(v)) < 1e-9) ? 0 : 2;
    snprintf(buf, sizeof buf, "%.*f", decimais, fabs(v));
    if (v < 0 && strspn(buf, "0.") != strlen(buf)) fputc('-', f);
    ponto = strchr(buf, '.');
    inteiros = ponto ? (int)(ponto - buf) : (int)strlen(buf);
    for (i = 0; i < inteiros; i++) {
        if (i > 0 && (inteiros - i) % 3 == 0) fputc('.', f);
        fputc(buf[i], f);
    }
    if (ponto) fprintf(f, ",%s", ponto + 1);
}

/* ====================================================================== */
/* processamento dos dados: filtro -> agrupamento -> ordenação -> limite  */
/* ====================================================================== */

typedef struct {
    double soma, min, max;
    long n;
} Acum;

typedef struct {
    Valor x;        /* valor da coluna de categorias */
    Acum *ac;       /* um acumulador por série (+1 para a chave de ordenação) */
    Valor chave;    /* chave de ordenação */
    int idx;        /* ordem original, para ordenação estável */
} Ponto;

static void acumula(Acum *a, const Serie *s, const Valor *linha)
{
    Valor v;
    if (!s->expr) { a->n++; return; }               /* contagem() */
    v = avalia(s->expr, linha);
    if (s->ag == AG_CONTAGEM) { if (v.tipo != V_NULO) a->n++; return; }
    if (v.tipo != V_NUM) return;
    if (a->n == 0 || v.num < a->min) a->min = v.num;
    if (a->n == 0 || v.num > a->max) a->max = v.num;
    a->soma += v.num;
    a->n++;
}

static Valor resultado(const Acum *a, Agregacao ag)
{
    Valor v = { V_NUM, 0, NULL }, nulo = { V_NULO, 0, NULL };
    switch (ag) {
    case AG_CONTAGEM: v.num = (double)a->n; return v;
    case AG_SOMA:     v.num = a->soma; return v;
    case AG_NENHUMA:  if (!a->n) return nulo; v.num = a->soma; return v;
    case AG_MEDIA:    if (!a->n) return nulo; v.num = a->soma / (double)a->n; return v;
    case AG_MIN:      if (!a->n) return nulo; v.num = a->min; return v;
    case AG_MAX:      if (!a->n) return nulo; v.num = a->max; return v;
    }
    return nulo;
}

static int valores_iguais(Valor a, Valor b)
{
    if (a.tipo != b.tipo) return 0;
    if (a.tipo == V_NUM) return a.num == b.num;
    if (a.tipo == V_STR) return strcmp(a.str, b.str) == 0;
    return 1;
}

static int ordem_desc;

static int compara_pontos(const void *pa, const void *pb)
{
    const Ponto *a = pa, *b = pb;
    Valor x = a->chave, y = b->chave;
    int cmp = 0;

    /* nulos sempre no fim; números antes de textos */
    if (x.tipo == V_NULO || y.tipo == V_NULO) {
        if (x.tipo != y.tipo) return x.tipo == V_NULO ? 1 : -1;
    } else if (x.tipo != y.tipo) {
        cmp = x.tipo == V_NUM ? -1 : 1;
    } else if (x.tipo == V_NUM) {
        cmp = (x.num > y.num) - (x.num < y.num);
    } else {
        cmp = strcmp(x.str, y.str);
    }
    if (cmp) return ordem_desc ? -cmp : cmp;
    return (a->idx > b->idx) - (a->idx < b->idx);
}

/* Calcula os pontos de um gráfico. Devolve o vetor e a quantidade em *n. */
static Ponto *calcula_pontos(const Config *c, int *n)
{
    const Tabela *t = c->fonte->tabela;
    int nac = c->ny + (c->ordem ? 1 : 0);
    Ponto *pts = NULL;
    int np = 0, cap = 0, i, k;
    const Serie *s;

    for (i = 0; i < t->nlin; i++) {
        const Valor *linha = t->linhas[i];
        Ponto *p = NULL;

        if (c->filtro && !verdadeiro(avalia(c->filtro, linha))) continue;

        if (c->agregado)                       /* procura o grupo da categoria */
            for (k = 0; k < np && !p; k++)
                if (valores_iguais(pts[k].x, linha[c->col_x])) p = &pts[k];

        if (!p) {
            if (np == cap) {
                cap = cap ? cap * 2 : 64;
                pts = realloc(pts, (size_t)cap * sizeof *pts);
                if (!pts) { fprintf(stderr, "erro: memória insuficiente\n"); exit(2); }
            }
            p = &pts[np];
            p->x = linha[c->col_x];
            p->ac = xmalloc((size_t)nac * sizeof *p->ac);
            p->idx = np++;
            p->chave.tipo = V_NULO;
            if (c->ordem && c->ordem->ag == AG_NENHUMA)
                p->chave = avalia(c->ordem->expr, linha);
        }

        for (s = c->y, k = 0; s; s = s->prox, k++) acumula(&p->ac[k], s, linha);
        if (c->ordem && c->ordem->ag != AG_NENHUMA) acumula(&p->ac[c->ny], c->ordem, linha);
    }

    if (c->ordem) {
        if (c->ordem->ag != AG_NENHUMA)
            for (i = 0; i < np; i++) pts[i].chave = resultado(&pts[i].ac[c->ny], c->ordem->ag);
        ordem_desc = c->desc;
        qsort(pts, (size_t)np, sizeof *pts, compara_pontos);
    }
    if (c->limite >= 0 && np > c->limite) np = c->limite;

    *n = np;
    return pts;
}

static char *rotulo(Valor v)
{
    char *r = NULL;
    if (v.tipo == V_STR) return xstrdup(v.str);
    if (v.tipo == V_NUM && asprintf(&r, "%.12g", v.num) >= 0) return r;
    return xstrdup("(vazio)");
}

static char *nome_serie(const Serie *s)
{
    return s->nome ? s->nome : serie_texto(s);
}

/* ====================================================================== */
/* gráficos                                                               */
/* ====================================================================== */

static const char *tipo_highcharts(TipoGrafico g)
{
    switch (g) {
    case G_LINHA:     return "line";
    case G_BARRA:     return "bar";
    case G_COLUNA:    return "column";
    case G_AREA:      return "area";
    case G_PIZZA:
    case G_ROSCA:     return "pie";
    case G_DISPERSAO: return "scatter";
    }
    return "line";
}

static void js_titulo_eixo(const char *eixo, const char *titulo)
{
    fprintf(js, "%s:{title:{text:", eixo);
    if (titulo) js_str(js, titulo); else fputs("null", js);
    fputc('}', js);
}

static void emite_grafico(const Elem *el)
{
    const Config *c = el->cfg;
    int id = prox_id++, np, i, k, descartados = 0;
    Ponto *pts = calcula_pontos(c, &np);
    int circular = el->grafico == G_PIZZA || el->grafico == G_ROSCA;
    int continuo = el->grafico == G_LINHA || el->grafico == G_AREA;
    const Serie *s;
    const ListaStr *cor;

    if (np == 0)
        aviso_em(el->linha, "gráfico \"%s\" não tem nenhum dado (verifique o filtro)", el->titulo);

    /* --- HTML: o cartão que recebe o gráfico --- */
    fprintf(html, "<figure class=\"cartao\" style=\"grid-column:span %d\">\n<figcaption>", c->largura);
    html_esc(html, el->titulo);
    fprintf(html, "</figcaption>\n<div id=\"g%d\" class=\"grafico\" style=\"height:%dpx\"></div>\n</figure>\n",
            id, c->altura);

    /* --- JavaScript: a configuração do Highcharts --- */
    fprintf(js, "Highcharts.chart('g%d',{chart:{type:'%s'},title:{text:null},",
            id, tipo_highcharts(el->grafico));
    fputs("accessibility:{description:", js);
    js_str(js, el->titulo);
    fputs("},", js);

    if (!circular) {
        js_titulo_eixo("xAxis", c->titulo_x);
        if (el->grafico != G_DISPERSAO) {
            fputs(",categories:[", js);
            for (i = 0; i < np; i++) {
                if (i) fputc(',', js);
                js_str(js, rotulo(pts[i].x));
            }
            fputc(']', js);
            if (continuo) fputs(",crosshair:true,tickmarkPlacement:'on'", js);
        }
        fputs("},", js);
        js_titulo_eixo("yAxis", c->titulo_y);
        fputs("},", js);
    }

    fprintf(js, "legend:{enabled:%s},", (!circular && c->ny > 1) ? "true" : "false");

    fputs("tooltip:{", js);
    if (continuo || (c->ny > 1 && el->grafico != G_DISPERSAO)) fputs("shared:true,", js);
    if (c->decimais >= 0) fprintf(js, "valueDecimals:%d,", c->decimais);
    if (c->prefixo) { fputs("valuePrefix:", js); js_str(js, c->prefixo); fputc(',', js); }
    if (c->sufixo) { fputs("valueSuffix:", js); js_str(js, c->sufixo); fputc(',', js); }
    if (el->grafico == G_DISPERSAO) {
        fputs("headerFormat:'',pointFormat:", js);
        js_str(js, c->titulo_x ? c->titulo_x : c->x);
        fputs("+': <b>{point.x}</b><br>{series.name}: <b>{point.y}</b>'", js);
    }
    fputs("},", js);

    if (c->empilhado) fputs("plotOptions:{series:{stacking:'normal'}},", js);

    if (c->cores) {
        fputs("colors:[", js);
        for (cor = c->cores; cor; cor = cor->prox) {
            js_str(js, cor->str);
            if (cor->prox) fputc(',', js);
        }
        fputs("],", js);
    }

    fputs("series:[", js);
    for (s = c->y, k = 0; s; s = s->prox, k++) {
        int primeiro = 1;
        if (k) fputc(',', js);
        fputs("{name:", js);
        js_str(js, nome_serie(s));
        if (el->grafico == G_ROSCA) fputs(",innerSize:'55%'", js);
        fputs(",data:[", js);
        for (i = 0; i < np; i++) {
            Valor v = resultado(&pts[i].ac[k], s->ag);
            if (el->grafico == G_DISPERSAO) {
                /* pontos sem x ou y numérico não podem ser posicionados */
                if (pts[i].x.tipo != V_NUM || v.tipo != V_NUM) { descartados++; continue; }
                if (!primeiro) fputc(',', js);
                fprintf(js, "[%.12g,%.12g]", pts[i].x.num, v.num);
            } else if (circular) {
                if (!primeiro) fputc(',', js);
                fputs("{name:", js);
                js_str(js, rotulo(pts[i].x));
                fputs(",y:", js);
                js_num(js, v);
                fputc('}', js);
            } else {
                if (!primeiro) fputc(',', js);
                js_num(js, v);
            }
            primeiro = 0;
        }
        fputs("]}", js);
    }
    fputs("]});\n", js);

    if (descartados)
        aviso_em(el->linha, "gráfico \"%s\": %d ponto(s) descartado(s) por não terem x e y numéricos",
                 el->titulo, descartados);
}

/* ====================================================================== */
/* indicadores (KPIs)                                                     */
/* ====================================================================== */

static void emite_indicador(const Elem *el)
{
    const Config *c = el->cfg;
    const Tabela *t = c->fonte->tabela;
    Acum a = { 0, 0, 0, 0 };
    Valor v;
    int i;

    for (i = 0; i < t->nlin; i++) {
        if (c->filtro && !verdadeiro(avalia(c->filtro, t->linhas[i]))) continue;
        acumula(&a, c->valor, t->linhas[i]);
    }
    v = resultado(&a, c->valor->ag);

    fputs("<div class=\"indicador\">\n<div class=\"indicador-rotulo\">", html);
    html_esc(html, el->titulo);
    fputs("</div>\n<div class=\"indicador-valor\">", html);
    if (v.tipo == V_NUM) {
        if (c->prefixo) html_esc(html, c->prefixo);
        formata_br(html, v.num, c->decimais);
        if (c->sufixo) html_esc(html, c->sufixo);
    } else {
        fputs("&mdash;", html);
        aviso_em(el->linha, "indicador \"%s\" não tem nenhum valor numérico para agregar", el->titulo);
    }
    fputs("</div>\n</div>\n", html);
}

/* ====================================================================== */
/* estrutura da página                                                    */
/* ====================================================================== */

static void emite_lista(const Elem *lista)
{
    const Elem *el;
    int em_indicadores = 0;

    fputs("<div class=\"grade\">\n", html);
    for (el = lista; el; el = el->prox) {
        /* indicadores consecutivos formam uma faixa única */
        if (el->tipo == EL_INDICADOR && !em_indicadores) {
            fputs("<div class=\"indicadores\">\n", html);
            em_indicadores = 1;
        } else if (el->tipo != EL_INDICADOR && em_indicadores) {
            fputs("</div>\n", html);
            em_indicadores = 0;
        }
        switch (el->tipo) {
        case EL_GRAFICO:
            emite_grafico(el);
            break;
        case EL_INDICADOR:
            emite_indicador(el);
            break;
        case EL_TEXTO:
            fputs("<p class=\"texto\">", html);
            html_esc(html, el->titulo);
            fputs("</p>\n", html);
            break;
        case EL_SECAO:
            fputs("<section class=\"secao\">\n<h2>", html);
            html_esc(html, el->titulo);
            fputs("</h2>\n", html);
            emite_lista(el->filhos);
            fputs("</section>\n", html);
            break;
        }
    }
    if (em_indicadores) fputs("</div>\n", html);
    fputs("</div>\n", html);
}

static const char *CSS =
":root{color-scheme:light;--pagina:#f3f2ef;--cartao:#fcfcfb;--texto:#0b0b0b;--texto2:#52514e;\n"
"--grade:#e4e3df;--borda:#dddcd7;\n"
"--s1:#2a78d6;--s2:#eb6834;--s3:#1baf7a;--s4:#eda100;--s5:#e87ba4;--s6:#008300;--s7:#6250d6;--s8:#e34948}\n"
"%s"
"*{box-sizing:border-box}\n"
"body{margin:0;background:var(--pagina);color:var(--texto);\n"
"font-family:system-ui,-apple-system,'Segoe UI',Roboto,sans-serif;line-height:1.45}\n"
"main{max-width:1280px;margin:0 auto;padding:24px 16px 48px}\n"
"h1{font-size:26px;margin:0 0 20px;font-weight:650;letter-spacing:-.01em}\n"
"h2{font-size:18px;margin:8px 0 12px;font-weight:600}\n"
".grade{display:grid;grid-template-columns:repeat(%d,minmax(0,1fr));gap:16px}\n"
".grade>*{min-width:0}\n"
".secao,.texto,.indicadores,.aviso{grid-column:1/-1}\n"
".secao{margin-top:8px}\n"
".texto{margin:0;color:var(--texto2);max-width:75ch}\n"
".indicadores{display:grid;grid-template-columns:repeat(auto-fit,minmax(180px,1fr));gap:16px}\n"
".cartao,.indicador{background:var(--cartao);border:1px solid var(--borda);border-radius:10px;margin:0}\n"
".cartao{padding:14px 14px 8px}\n"
".cartao figcaption{font-size:15px;font-weight:600;margin-bottom:8px}\n"
".indicador{padding:14px 16px}\n"
".indicador-rotulo{font-size:13px;color:var(--texto2)}\n"
".indicador-valor{font-size:28px;font-weight:650;margin-top:2px;font-variant-numeric:tabular-nums;\n"
"overflow-wrap:anywhere}\n"
".aviso{padding:12px 16px;border:1px solid var(--borda);border-radius:10px;margin-bottom:16px}\n"
"@media (max-width:760px){.grade{grid-template-columns:minmax(0,1fr)}\n"
".cartao{grid-column:1/-1 !important}}\n";

static const char *CSS_ESCURO =
"{color-scheme:dark;--pagina:#111110;--cartao:#1a1a19;--texto:#f0efec;--texto2:#c3c2b7;\n"
"--grade:#33332f;--borda:#2e2e2b;\n"
"--s1:#3987e5;--s2:#d95926;--s3:#199e70;--s4:#c98500;--s5:#d55181;--s6:#008300;--s7:#9085e9;--s8:#e66767}\n";

/* Tema global do Highcharts, lido das variáveis CSS da página. */
static const char *JS_TEMA =
"var cs=getComputedStyle(document.documentElement);\n"
"function v(n){return cs.getPropertyValue(n).trim();}\n"
"var texto=v('--texto'),texto2=v('--texto2'),grade=v('--grade'),cartao=v('--cartao');\n"
"Highcharts.setOptions({\n"
"lang:{decimalPoint:',',thousandsSep:'.',numericSymbols:[' mil',' mi',' bi',' tri']},\n"
"colors:[1,2,3,4,5,6,7,8].map(function(i){return v('--s'+i);}),\n"
"credits:{enabled:false},\n"
"chart:{backgroundColor:'transparent',style:{fontFamily:'inherit'},spacing:[6,24,6,4]},\n"
"xAxis:{lineColor:grade,tickColor:grade,gridLineColor:grade,\n"
"labels:{style:{color:texto2}},title:{style:{color:texto2}}},\n"
"yAxis:{gridLineColor:grade,lineColor:grade,reversedStacks:false,\n"
"labels:{overflow:'allow',style:{color:texto2,textOverflow:'none',whiteSpace:'nowrap'}},title:{style:{color:texto2}}},\n"
"legend:{itemStyle:{color:texto,fontWeight:'normal'},itemHoverStyle:{color:texto},\n"
"itemHiddenStyle:{color:texto2}},\n"
"tooltip:{backgroundColor:cartao,borderColor:grade,style:{color:texto}},\n"
"plotOptions:{\n"
"series:{borderColor:cartao,animation:{duration:400}},\n"
"line:{lineWidth:2,marker:{radius:4,symbol:'circle'}},\n"
"area:{lineWidth:2,fillOpacity:.25,marker:{radius:3,symbol:'circle'}},\n"
"column:{borderRadius:4,borderWidth:1,maxPointWidth:56},\n"
"bar:{borderRadius:4,borderWidth:1,maxPointWidth:32},\n"
"scatter:{marker:{radius:4,symbol:'circle'}},\n"
"pie:{borderWidth:2,dataLabels:{format:'{point.name}: {point.percentage:.1f}%',\n"
"style:{color:texto,fontWeight:'normal',textOutline:'none'}}}}\n"
"});\n";

int gera_html(Dashboard *d, FILE *saida)
{
    char *buf_js = NULL, *css_escuro = NULL;
    size_t tam_js = 0;

    dash = d;
    html = saida;
    js = open_memstream(&buf_js, &tam_js);
    if (!js) return 0;

    /* tema: claro = só :root; escuro = força; auto = segue o sistema */
    if (d->tema == TEMA_ESCURO)
        asprintf(&css_escuro, ":root%s", CSS_ESCURO);
    else if (d->tema == TEMA_AUTO)
        asprintf(&css_escuro, "@media (prefers-color-scheme:dark){:root%s}\n", CSS_ESCURO);

    fputs("<!DOCTYPE html>\n<html lang=\"pt-BR\">\n<head>\n<meta charset=\"utf-8\">\n"
          "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\n<title>", html);
    html_esc(html, d->titulo);
    fputs("</title>\n<style>\n", html);
    fprintf(html, CSS, css_escuro ? css_escuro : "", d->colunas);
    fputs("</style>\n</head>\n<body>\n<main>\n<h1>", html);
    html_esc(html, d->titulo);
    fputs("</h1>\n", html);

    emite_lista(d->elementos);

    fputs("</main>\n", html);
    fclose(js);
    if (prox_id > 1) {      /* há pelo menos um gráfico */
        fputs("<script src=\"" HIGHCHARTS_URL "/highcharts.js\"></script>\n"
              "<script src=\"" HIGHCHARTS_URL "/modules/accessibility.js\"></script>\n"
              "<script>\n(function(){\n"
              "if(!window.Highcharts){\n"
              "var a=document.createElement('p');a.className='aviso';\n"
              "a.textContent='Não foi possível carregar a biblioteca Highcharts "
              "(verifique a conexão com a internet).';\n"
              "var g=document.querySelector('.grade');g.insertBefore(a,g.firstChild);return;}\n", html);
        fputs(JS_TEMA, html);
        fwrite(buf_js, 1, tam_js, html);
        if (d->tema == TEMA_AUTO)
            fputs("matchMedia('(prefers-color-scheme:dark)').addEventListener('change',"
                  "function(){location.reload();});\n", html);
        fputs("})();\n</script>\n", html);
    }
    fputs("</body>\n</html>\n", html);
    free(buf_js);
    return !ferror(html);
}
