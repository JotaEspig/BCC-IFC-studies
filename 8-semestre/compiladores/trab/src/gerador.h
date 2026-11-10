/* gerador.h — geração do HTML final */
#ifndef GERADOR_H
#define GERADOR_H

#include <stdio.h>
#include "ast.h"

/* Escreve o dashboard em `saida`. Retorna 1 em caso de sucesso. */
int gera_html(Dashboard *d, FILE *saida);

#endif
