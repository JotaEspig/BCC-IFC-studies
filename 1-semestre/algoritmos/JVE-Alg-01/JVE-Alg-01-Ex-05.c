/*
Retorno de recicláveis. Alguns estabelecimentos retornam créditos em troca de reciclagem
de recipientes. Em um estabelecimento em particular, vasilhames de um litro ou menos geram
crédito de 10 centavos e vasilhames de mais de um litro geram créditos de 25 centavos.
Escreva um programa que leia do teclado a quantidade destes dois tipos de vasilhames a
serem reciclados. A seguir o programa deve calcular e exibir o valor total dos créditos
referentes ao retorno dos vasilhames. Pesquise sobre como formatar a saída para que a
resposta seja exibida com sinal de reais R$ e exatamente duas casas decimais.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *read_input(int strlength) {
    char *str = (char *) calloc(strlength, sizeof(char));
    if (fgets(str, strlength, stdin) == NULL)
        return NULL;

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    
    return str;
}

int main() {
    printf("Quantos vasilhames de 1 litro ou menos?\n");
    // le = less than , gt = greater than
    char *str_vasilhame_le1 = read_input(10);
    int vasilhame_le1 = atoi(str_vasilhame_le1);
    printf("Quantos vasilhames de mais de 1 litro?\n");
    char *str_vasilhame_gt1 = read_input(10);
    int vasilhame_gt1 = atoi(str_vasilhame_gt1);
    
    // It calculates in cents to avoid precision errors
    // when doing math with floats
    int result_in_cents = vasilhame_le1 * 10 + vasilhame_gt1 * 25;
    float result_in_reais = (float) result_in_cents / 100;
    printf("Valor total: R$%.2f\n", result_in_reais);
}
