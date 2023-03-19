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
