/* main.c — dashc: compilador da linguagem de dashboards para HTML + Highcharts
 *
 * Fases: léxica (flex) -> sintática (bison) -> semântica -> geração de código
 */
#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ast.h"
#include "gerador.h"
#include "semantico.h"

extern FILE *yyin;
extern Dashboard *raiz;
int yyparse(void);

int erros = 0;
const char *arquivo_fonte = "";

/* fontes informadas na linha de comando: nome=arquivo */
typedef struct {
    const char *nome, *caminho;
} FonteCli;

static void uso(const char *prog)
{
    fprintf(stderr,
        "uso: %s <dashboard.dash> [nome=arquivo.csv|json ...] [-o saida.html] [--nao-abrir]\n"
        "\n"
        "  <dashboard.dash>   definição do dashboard\n"
        "  nome=arquivo       define (ou substitui) o arquivo da fonte de dados 'nome';\n"
        "                     o formato é deduzido da extensão (.csv ou .json)\n"
        "  -o saida.html      arquivo de saída (padrão: mesmo nome da entrada, com .html)\n"
        "  --nao-abrir        não abre o HTML gerado no navegador padrão\n",
        prog);
}

static int termina_com(const char *s, const char *sufixo)
{
    size_t n = strlen(s), m = strlen(sufixo);
    return n >= m && strcmp(s + n - m, sufixo) == 0;
}

/* Aplica uma fonte da linha de comando sobre as declaradas no arquivo. */
static int aplica_fonte_cli(Dashboard *d, const FonteCli *fc)
{
    Fonte *f, *ult = NULL;
    Formato fmt;

    if (termina_com(fc->caminho, ".csv")) fmt = F_CSV;
    else if (termina_com(fc->caminho, ".json")) fmt = F_JSON;
    else {
        fprintf(stderr, "erro: fonte '%s': não sei o formato de '%s' (use .csv ou .json)\n",
                fc->nome, fc->caminho);
        return 0;
    }
    for (f = d->fontes; f; ult = f, f = f->prox) {
        if (strcmp(f->nome, fc->nome) == 0) {
            if (f->formato != fmt) f->subcaminho = NULL;
            f->formato = fmt;
            f->caminho = xstrdup(fc->caminho);
            f->da_cli = 1;
            return 1;
        }
    }
    f = fonte_nova(xstrdup(fc->nome), fmt, xstrdup(fc->caminho), NULL, 0);
    f->da_cli = 1;
    if (ult) ult->prox = f; else d->fontes = f;
    return 1;
}

/* Abre o arquivo no navegador padrão do usuário, sem bloquear o compilador. */
static void abre_no_navegador(const char *caminho)
{
#ifdef __APPLE__
    const char *abridor = "open";
#else
    const char *abridor = "xdg-open";
#endif
    char *absoluto = realpath(caminho, NULL);
    pid_t pid;

    fflush(NULL);
    pid = fork();
    if (pid < 0) {
        perror("aviso: não foi possível abrir o navegador");
    } else if (pid == 0) {
        /* filho: desvincula do terminal e silencia a saída do navegador,
           guardando o stderr original para avisar se o exec falhar */
        int erro = fcntl(STDERR_FILENO, F_DUPFD_CLOEXEC, 3);
        int nulo = open("/dev/null", O_RDWR);
        setsid();
        if (nulo >= 0) {
            dup2(nulo, STDIN_FILENO);
            dup2(nulo, STDOUT_FILENO);
            dup2(nulo, STDERR_FILENO);
        }
        execlp(abridor, abridor, absoluto ? absoluto : caminho, (char *)NULL);
        if (erro >= 0)
            dprintf(erro, "aviso: não foi possível abrir o navegador ('%s' não encontrado); "
                          "abra o arquivo manualmente\n", abridor);
        _exit(127);
    }
    free(absoluto);
}

int main(int argc, char **argv)
{
    const char *entrada = NULL, *saida = NULL;
    char *saida_padrao, *dir_base, *barra, *ponto;
    FonteCli *cli = xmalloc((size_t)argc * sizeof *cli);
    int ncli = 0, abrir = 1, i;
    FILE *f;

    for (i = 1; i < argc; i++) {
        char *igual;
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            uso(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--nao-abrir") == 0) {
            abrir = 0;
        } else if (strcmp(argv[i], "-o") == 0) {
            if (++i >= argc) { uso(argv[0]); return 2; }
            saida = argv[i];
        } else if (!entrada) {
            entrada = argv[i];
        } else if ((igual = strchr(argv[i], '=')) && igual != argv[i] && igual[1]) {
            *igual = '\0';
            cli[ncli].nome = argv[i];
            cli[ncli].caminho = igual + 1;
            ncli++;
        } else {
            fprintf(stderr, "erro: argumento inválido '%s'\n\n", argv[i]);
            uso(argv[0]);
            return 2;
        }
    }
    if (!entrada) { uso(argv[0]); return 2; }

    /* --- análise léxica e sintática --- */
    yyin = fopen(entrada, "r");
    if (!yyin) { perror(entrada); return 2; }
    arquivo_fonte = entrada;
    yyparse();
    fclose(yyin);
    if (erros || !raiz) {
        fprintf(stderr, "%d erro(s); nenhum arquivo gerado.\n", erros ? erros : 1);
        return 1;
    }

    /* --- análise semântica --- */
    for (i = 0; i < ncli; i++)
        if (!aplica_fonte_cli(raiz, &cli[i])) erros++;

    dir_base = xstrdup(entrada);
    barra = strrchr(dir_base, '/');
    if (barra) *barra = '\0'; else dir_base[0] = '\0';

    analisa(raiz, dir_base);
    if (erros) {
        fprintf(stderr, "%d erro(s); nenhum arquivo gerado.\n", erros);
        return 1;
    }

    /* --- geração de código --- */
    if (!saida) {
        saida_padrao = xmalloc(strlen(entrada) + 6);
        strcpy(saida_padrao, entrada);
        ponto = strrchr(saida_padrao, '.');
        barra = strrchr(saida_padrao, '/');
        if (ponto && (!barra || ponto > barra)) *ponto = '\0';
        strcat(saida_padrao, ".html");
        saida = saida_padrao;
    }
    f = fopen(saida, "w");
    if (!f) { perror(saida); return 2; }
    if (!gera_html(raiz, f) || fclose(f) != 0) {
        fprintf(stderr, "erro: falha ao escrever '%s'\n", saida);
        return 2;
    }
    printf("gerado: %s\n", saida);
    if (abrir) abre_no_navegador(saida);
    return 0;
}
